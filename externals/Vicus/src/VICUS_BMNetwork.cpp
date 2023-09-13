/*	BSD 3-Clause License

	This file is part of the BlockMod Library.

	Copyright (c) 2019, Andreas Nicolai
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	   contributors may be used to endorse or promote products derived from
	   this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "VICUS_BMNetwork.h"

#include <QFile>
#include <QSet>
#include <QDebug>
#include <QPixmap>

#include <stdexcept>
#include <iostream>
#include <cmath>

#include "VICUS_BMBlock.h"
#include "VICUS_BMConnector.h"
#include "VICUS_AbstractDBElement.h"
#include "VICUS_BMGlobals.h"
#include "VICUS_BMGlobals.h"
#include <VICUS_NetworkComponent.h>

#include "IBK_Exception.h"




namespace VICUS {


void BMNetwork::swap(BMNetwork & other) {
	other.m_blocks.swap(m_blocks);
	other.m_connectors.swap(m_connectors);
}

void VICUS::BMNetwork::BMNetwork::readXML(const TiXmlElement *element) {
	FUNCID(BMNetwork::readXML);
	try {
		// search for mandatory elements
		// reading elements
		const TiXmlElement * c = element->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "Blocks"){
				qDebug() << "Blocks found!";
				const TiXmlElement * b = c->FirstChildElement();
				while (b) {
					const std::string & bName = b->ValueStr();
					if (bName == "Block"){
						qDebug() << "Block found!";
						BMBlock * block = new BMBlock();
						block->readXML(b);
						m_blocks.push_back(*block);
					}
					b = b->NextSiblingElement();
				}
			}
			else if(cName == "Connectors"){
				qDebug() << "Connectors found!";
				const TiXmlElement * con = c->FirstChildElement();
				while (con) {
					const std::string & conName = con->ValueStr();
					if (conName == "Connector"){
						qDebug() << "Connector found!";
						BMConnector * connector = new BMConnector();
						connector->readXML(con);
						m_connectors.push_back(*connector);
					}
					con = con->NextSiblingElement();
				}
			}
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'BMNetwork' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'BMNetwork' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement *VICUS::BMNetwork::BMNetwork::writeXML(TiXmlElement *parent) const {
	TiXmlElement * e = new TiXmlElement("Connectors");
	parent->LinkEndChild(e);
	TiXmlElement * blockE = new TiXmlElement("Blocks");
	e->LinkEndChild(blockE);
	for(auto block : m_blocks) {
		block.writeXML(blockE);
	}
	TiXmlElement * connectorE = new TiXmlElement("Connectors");
	e->LinkEndChild(connectorE);
	for(auto connector : m_connectors) {
		connector.writeXML(connectorE);
	}
	return e;
}

void BMNetwork::checkNames(bool printNames) const {
	QSet<QString> blockNames;
	for (const BMBlock & b : m_blocks) {
		QString bName = b.m_name;
		if (bName.indexOf(".") != -1)
			throw std::runtime_error("Invalid Block ID name '"+bName.toStdString()+"'");
		if (blockNames.contains(bName))
			throw std::runtime_error("Duplicate Block ID name '"+bName.toStdString()+"'");
		blockNames.insert(bName);
		if (printNames)
			qDebug() << bName;
		// now all sockets
		QSet<QString> socketNames;
		for (const BMSocket & s : b.m_sockets) {
			QString sName = s.m_name;
			// check if such a name already exists
			if (socketNames.contains(sName))
				throw std::runtime_error("Duplicate Socket ID name '"+sName.toStdString()+"' within block '"+bName.toStdString()+"'");
			socketNames.insert(sName);
			if (printNames)
				qDebug() << sName;
		}
	}
	// check all connections for valid socket names
	QSet<QString> connectedSockets;
	for (const BMConnector & con : m_connectors) {
		// first check, that indeed the source/target connectors are valid
		const BMBlock * b1, * b2;
		const BMSocket * s1, * s2;
		qDebug() << "checkNames";
		for(BMBlock block : m_blocks) {
			qDebug() << "block: " << block.m_name;
			for(BMSocket socket : block.m_sockets) {
				qDebug() << "   socket: " << socket.m_name << socket.m_inlet;
			}
		}
		qDebug() << "addConnector" << con.m_name << con.m_sourceSocket << con.m_targetSocket;
		try {
			lookupBlockAndSocket(con.m_sourceSocket, b1, s1);
		} catch (...) {
			throw std::runtime_error("Invalid source socket identifyer '"+con.m_sourceSocket.toStdString()+"'.");
		}
		try {
			lookupBlockAndSocket(con.m_targetSocket, b2, s2);
		} catch (...) {
			throw std::runtime_error("Invalid target socket identifyer '"+con.m_targetSocket.toStdString()+"'.");
		}
		if (s1->m_inlet)
			throw std::runtime_error("Invalid source socket '"+con.m_sourceSocket.toStdString()+"'(must be an outlet socket).");
		if (!s2->m_inlet)
			throw std::runtime_error("Invalid target socket '"+con.m_targetSocket.toStdString()+"' (must be an inlet socket).");
		/*if (connectedSockets.contains(con.m_targetSocket))
			throw std::runtime_error("Target socket '"+con.m_targetSocket.toStdString()+"' connected twice!");*/
		connectedSockets.insert(con.m_targetSocket);
	}
}


bool BMNetwork::haveSocket(const QString & socketVariableName, bool inletSocket) const {
	QString blockName, socketName;
	splitFlatName(socketVariableName, blockName, socketName);
	for (const VICUS::BMBlock & b : m_blocks) {
		if (b.m_name == blockName) {
			for (const VICUS::BMSocket & s : b.m_sockets) {
				if (s.m_name == socketName && (s.m_inlet == inletSocket)) {
					return true;
				}
			}
		}
	}
	return false;
}


void BMNetwork::adjustConnectors() {
	for (BMConnector & c : m_connectors) {
		try {
			adjustConnector(c);
		}
		catch (std::runtime_error & e) {
			std::cerr << "Error adjusting connector " << c.m_name.toStdString() << std::endl;
			throw e;
		}
	}
}


void BMNetwork::adjustConnector(BMConnector & con) {
	// split socket name into block and socket
	const BMSocket * socket;
	const BMBlock * block;
	lookupBlockAndSocket(con.m_sourceSocket, block, socket);
	// get start coordinates: first point is the socket's center, second point is the connection point outside the socket
	QLineF startLine = block->socketStartLine(socket);
	lookupBlockAndSocket(con.m_targetSocket, block, socket);
	// get start coordinates: first point is the socket's center, second point is the connection point outside the socket
	QLineF endLine = block->socketStartLine(socket);

	// compute dx and dy between connection points
	double dx = endLine.p2().x() - startLine.p2().x();
	double dy = endLine.p2().y() - startLine.p2().y();

	// now subtract the distance already covered by existing segments
	for (int i=0;i<con.m_segments.count(); ++i) {
		if (con.m_segments[i].m_direction == Qt::Horizontal)
			dx -= con.m_segments[i].m_offset;
		else
			dy -= con.m_segments[i].m_offset;
	}

	// remaining distance must be distributed to segments
	if (!BMGlobals::nearZero(dy)) {
		// now search for first connector segment that is vertical
		int i;
		for (i=0;i<con.m_segments.count(); ++i) {
			if (con.m_segments[i].m_direction == Qt::Vertical) {
				con.m_segments[i].m_offset += dy;
				break;
			}
		}
		if (i == con.m_segments.count()) {
			// add a new segment with proper size
			BMConnector::Segment s;
			s.m_direction = Qt::Vertical;
			s.m_offset = dy;
			con.m_segments.append(s);
		}
	}
	if (!BMGlobals::nearZero(dx)) {
		// now search for first connector segment that is horizontal
		int i;
		for (i=0;i<con.m_segments.count(); ++i) {
			if (con.m_segments[i].m_direction == Qt::Horizontal) {
				con.m_segments[i].m_offset += dx;
				break;
			}
		}
		if (i == con.m_segments.count()) {
			// add a new segment with proper size
			BMConnector::Segment s;
			s.m_direction = Qt::Horizontal;
			s.m_offset = dx;
			con.m_segments.append(s);
		}
	}
}


void BMNetwork::lookupBlockAndSocket(const QString & flatName, const BMBlock *& block, const BMSocket * &socket) const {
	QString blockName, socketName;
	splitFlatName(flatName, blockName, socketName);
	// search block by name
	auto blockIt = std::find_if(m_blocks.begin(), m_blocks.end(),
								[&] (const BMBlock& b) { return b.m_name == blockName; } );

	if (blockIt == m_blocks.end()){
		block == nullptr;
		socket == nullptr;
		return;
	}

	const BMBlock & b = *blockIt;
	block = &b;


	// search socket by name
	auto socketIt = std::find_if(b.m_sockets.constBegin(), b.m_sockets.constEnd(),
								[&] (const BMSocket& s) { return s.m_name == socketName; } );


	if (socketIt == b.m_sockets.constEnd())
		socket == nullptr;
	else{
		const BMSocket & s = *socketIt;
		socket = &s;
	}


}


void BMNetwork::removeBlock(unsigned int blockIdx) {
	Q_ASSERT(blockIdx < static_cast<unsigned int>(m_blocks.size()));

	// get block ID name
	auto bit = m_blocks.begin(); std::advance(bit, blockIdx);
	QString bName = bit->m_name;

	// erase all connectors that refer to this block
	auto cit = m_connectors.begin();
	while (cit != m_connectors.end()) {
		QString blockName, socketName;
		splitFlatName(cit->m_sourceSocket, blockName, socketName);
		if (blockName == bName) {
			auto cit2 = cit;
			++cit2;
			m_connectors.erase(cit);
			cit = cit2;
			continue;
		}
		splitFlatName(cit->m_targetSocket, blockName, socketName);
		if (blockName == bName) {
			auto cit2 = cit;
			++cit2;
			m_connectors.erase(cit);
			cit = cit2;
			continue;
		}
		++cit;
	}
	m_blocks.erase(bit);
}


void BMNetwork::renameBlock(unsigned int blockIdx, const QString &newName) {
	auto bit = m_blocks.begin(); std::advance(bit, blockIdx);
	QString oldName = bit->m_name;
	bit->m_name = newName;

	for (BMConnector & c : m_connectors) {
		QString blockName, socketName;
		splitFlatName(c.m_sourceSocket, blockName, socketName);
		if (blockName == oldName) {
			c.m_sourceSocket = newName + "." + socketName;
		}
		splitFlatName(c.m_targetSocket, blockName, socketName);
		if (blockName == oldName) {
			c.m_targetSocket = newName + "." + socketName;
		}
	}
}


void BMNetwork::splitFlatName(const QString & flatVariableName, QString & blockName, QString & socketName) {
	int pos = flatVariableName.indexOf('.');
	if (pos == -1)
		throw std::runtime_error("Bad flat name, missing . character");
	blockName = flatVariableName.left(pos).trimmed();
	socketName = flatVariableName.right(flatVariableName.length() - pos - 1).trimmed();
}


} // namespace VICUS
