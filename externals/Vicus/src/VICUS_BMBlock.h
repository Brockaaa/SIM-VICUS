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

#ifndef BM_BlockH
#define BM_BlockH

#include <QList>
#include <QString>
#include <QPointF>
#include <QSizeF>
#include <QLineF>
#include <QVariant>
#include <QMap>

#include "VICUS_BMSocket.h"
#include "VICUS_BMGlobals.h"
#include "VICUS_CodeGenMacros.h"
#include "VICUS_Constants.h"

class TiXmlElement;

namespace VICUS {

/*! Stores properties of a block.
	* appearance properties of block
	* position of block
	* sockets
	* custom properties in the property map
*/
class BMBlock {
public:

	BMBlock() : m_connectionHelperBlock(false) {}

	BMBlock(const QString & name);
	BMBlock(const QString & name, double x, double y);

	/*! Generate connection line between socket and point, where first connector segment starts.
		Returned coordinates are in scene-coordinates.
	*/
	QLineF socketStartLine(const BMSocket * socket) const;

	TiXmlElement * writeXML(TiXmlElement * parent) const;

	void readXML(const TiXmlElement * element);


	/*! Returns a list of socket pointers with either inlet or outlet sockets. */
	QList<const BMSocket*>	filterSockets(bool inletSocket) const;

	/*! Unique identification name of this block instance. */
	QString						m_name;

	/*! Name to be displayed in Scene */
	QString                     m_displayName;


	/*! Position (top left corner) of block. */
	QPointF						m_pos;


	/*! Sockets that belong to this block. */
	QList<BMSocket>				m_sockets;

	/*! Size of block. */
	QSizeF						m_size;

	/*! Custom properties. */
	QMap<QString, QVariant>		m_properties;

	/*! VICUS::NetworkComponent::ModelType of Block */
	unsigned int				m_componentId;


	/*! If true, this block is only a virtual block with a single socket, that is invisible (not painted)
		and only exists, until the connected has been attached to a socket of another block.
	*/
	bool						m_connectionHelperBlock;

	/* VICUS::NetworkController ID */
	unsigned int                m_controllerID = VICUS::INVALID_ID;

	VICUS::BMBlockType			m_mode;


};

} // namespace VICUS


#endif // BM_BlockH
