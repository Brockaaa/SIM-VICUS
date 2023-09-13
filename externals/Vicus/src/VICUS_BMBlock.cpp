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

#include "VICUS_BMBlock.h"

#include <QXmlStreamWriter>
#include <QStringList>
#include <QPixmap>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <cmath>

#include "tinyxml.h"

#include "VICUS_BMGlobals.h"
#include "VICUS_NetworkComponent.h"

namespace VICUS {

BMBlock::BMBlock(const QString & name) :
	m_name(name),
	m_pos(0,0),
	m_connectionHelperBlock(false)
{
}

BMBlock::BMBlock(const QString & name, double x, double y) :
	m_name(name),
	m_pos(x,y),
	m_connectionHelperBlock(false)
{
}


QLineF BMBlock::socketStartLine(const BMSocket * socket) const {
	// special handling for "invisible" blocks

	if (m_mode == VICUS::BMBlockType::InvisibleBlock) {
		QPointF startPoint(socket->m_pos);
		startPoint += m_pos;
		return QLineF(startPoint, startPoint);
	}
	// first determine the direction: top, left, right, bottom
	QPointF otherPoint = socket->m_pos;
	switch (socket->direction()) {
		case BMSocket::Left	: otherPoint += QPointF(-2*BMGlobals::GridSpacing, 0); break;
		case BMSocket::Right	: otherPoint += QPointF(+2*BMGlobals::GridSpacing, 0); break;
		case BMSocket::Top	: otherPoint += QPointF(0, -2*BMGlobals::GridSpacing); break;
		case BMSocket::Bottom	: otherPoint += QPointF(0, +2*BMGlobals::GridSpacing); break;
	}
	QPointF startPoint(socket->m_pos);
	// shift both points by block position
	startPoint += m_pos;
	otherPoint += m_pos;
	return QLineF(startPoint, otherPoint);
}

TiXmlElement * BMBlock::writeXML(TiXmlElement *parent) const
{
	TiXmlElement * e = new TiXmlElement("Block");
	parent->LinkEndChild(e);
	bool ok = false;
	m_name.toInt(&ok);
	if (ok){
		e->SetAttribute("networkElementid", std::to_string(m_name.toInt()));
	}
	else{
		e->SetAttribute("networkElementid", std::to_string(-1));
		e->SetAttribute("name", m_name.toStdString());
	}
	int x = (int)m_pos.x();
	int y = (int)m_pos.y();
	e->SetAttribute("position", std::to_string(x) + ", " +std::to_string(y));
	return e;
}

void BMBlock::readXML(const TiXmlElement * element)
{
	m_displayName = INVALIDXMLREAD;
	m_name = QString(element->Attribute("networkElementid"));
	if (m_name == "-1"){
		m_name = QString(element->Attribute("name"));
	}
	QString pos = QString(element->Attribute("position"));
	QStringList posList = pos.split(", ");
	if (posList.count() == 2) {
		m_pos.setX(posList[0].toInt());
		m_pos.setY(posList[1].toInt());
	}
}


QList<const BMSocket*> BMBlock::filterSockets(bool inletSocket) const {
	QList<const BMSocket*> socketList;
	for (const BMSocket & s : m_sockets) {
		if (inletSocket && s.m_inlet)
			socketList.append(&s);
		else if (!inletSocket && !s.m_inlet)
			socketList.append(&s);
	}
	return socketList;
}

} // namespace VICUS



