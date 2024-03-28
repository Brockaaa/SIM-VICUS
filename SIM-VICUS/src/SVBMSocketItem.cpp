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

#include "SVBMSocketItem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QFontMetrics>
#include <QDebug>
#include <QGraphicsView>
#include <QApplication>

#include "VICUS_BMSocket.h"
#include "SVBMBlockItem.h"
#include "VICUS_BMBlock.h"
#include "VICUS_BMGlobals.h"
#include "SVBMSceneManager.h"


SVBMSocketItem::SVBMSocketItem(SVBMBlockItem * parent, VICUS::BMSocket * socket, VICUS::NetworkComponent::ModelType modelType) :
	QGraphicsItem (parent),
	m_block(parent->block()),
	m_socket(socket),
	m_hovered(false),
	m_componentModelType(modelType)
{
	updateSocketItem();
	setZValue(12);
	setAcceptHoverEvents(true);
}


void SVBMSocketItem::updateSocketItem() {
	switch(m_componentModelType){
		case VICUS::NetworkComponent::MT_PressureLossElement:
		case VICUS::NetworkComponent::MT_ControlledValve:
		case VICUS::NetworkComponent::MT_ConstantPressureLossValve:
		{
			if (m_socket->m_isInlet) {
				switch (m_socket->direction()) {
					case VICUS::BMSocket::Left		: m_symbolRect = QRectF(-4, m_socket->m_pos.y()+8, 8, 8); break;
					case VICUS::BMSocket::Right		: break;
					case VICUS::BMSocket::Top		: break;
					case VICUS::BMSocket::Bottom	: break;
				}
			}
			else {
				switch (m_socket->direction()) {
					case VICUS::BMSocket::Left		: break;
					case VICUS::BMSocket::Right		: m_symbolRect = QRectF(m_socket->m_pos.x(), m_socket->m_pos.y()+8, 8, 8); break;
					case VICUS::BMSocket::Top		: break;
					case VICUS::BMSocket::Bottom	: break;
				}
			}
			break;
		}
		case VICUS::NetworkComponent::MT_HeatPumpOnOffSourceSide:
		case VICUS::NetworkComponent::MT_HeatPumpVariableIdealCarnotSupplySide:
		case VICUS::NetworkComponent::MT_HeatPumpVariableSourceSide:
		case VICUS::NetworkComponent::MT_HeatPumpVariableIdealCarnotSourceSide:
		{
			if (m_socket->m_isInlet) {
				switch (m_socket->direction()) {
					case VICUS::BMSocket::Left		: m_symbolRect = QRectF(-4, m_socket->m_pos.y()+16, 8, 8); break;
					case VICUS::BMSocket::Right		: break;
					case VICUS::BMSocket::Top		: break;
					case VICUS::BMSocket::Bottom	: break;
				}
			}
			else {
				switch (m_socket->direction()) {
					case VICUS::BMSocket::Left		: break;
					case VICUS::BMSocket::Right		: m_symbolRect = QRectF(m_socket->m_pos.x(), m_socket->m_pos.y()+16, 8, 8); break;
					case VICUS::BMSocket::Top		: break;
					case VICUS::BMSocket::Bottom	: break;
				}
			}
			break;
		}

		case VICUS::NetworkComponent::ModelType::MT_HeatExchanger:
		case VICUS::NetworkComponent::ModelType::MT_IdealHeaterCooler:
		{
			if (m_socket->m_isInlet) {
				switch (m_socket->direction()) {
					case VICUS::BMSocket::Left		: m_symbolRect = QRectF(-4, m_socket->m_pos.y()+7, 8, 8); break;
					case VICUS::BMSocket::Right		: break;
					case VICUS::BMSocket::Top		: break;
					case VICUS::BMSocket::Bottom	: break;
				}
			}
			else {
				switch (m_socket->direction()) {
					case VICUS::BMSocket::Left		: break;
					case VICUS::BMSocket::Right		: m_symbolRect = QRectF(m_socket->m_pos.x(), m_socket->m_pos.y()+7, 8, 8); break;
					case VICUS::BMSocket::Top		: break;
					case VICUS::BMSocket::Bottom	: break;
				}
			}
			break;
		}
		default:
		{
			if (m_socket->m_isInlet) {
				switch (m_socket->direction()) {
					case VICUS::BMSocket::Left		: m_symbolRect = QRectF(-4, m_socket->m_pos.y()-4, 8, 8); break;
					case VICUS::BMSocket::Right		: m_symbolRect = QRectF(m_socket->m_pos.x()-4, m_socket->m_pos.y()-4, 8, 8); break;
					case VICUS::BMSocket::Top		: break;
					case VICUS::BMSocket::Bottom	: break;
				}
			}
			else {
				switch (m_socket->direction()) {
					case VICUS::BMSocket::Left		: m_symbolRect = QRectF(-8, m_socket->m_pos.y()-4, 8, 8); break;
					case VICUS::BMSocket::Right		: m_symbolRect = QRectF(m_socket->m_pos.x(), m_socket->m_pos.y()-4, 8, 8); break;
					case VICUS::BMSocket::Top		: break;
					case VICUS::BMSocket::Bottom	: break;
				}
			}
			break;
		}
	}
}


QRectF SVBMSocketItem::boundingRect() const {
	QRectF r = m_symbolRect;
	// add space for text
	QFont f;
	f.setPointSizeF(VICUS::BMGlobals::LabelFontSize);
	QFontMetricsF metrics(f);
	QRectF textBoundingRect = metrics.boundingRect(m_socket->m_name);
	textBoundingRect.setWidth(textBoundingRect.width()+6); // add some space to avoid clipping of italic fonts to the right

	switch (m_socket->direction()) {
		case VICUS::BMSocket::Left		:
			// left side - expand rect to left
			r.moveLeft(r.left()-textBoundingRect.width()-6);
		break;
		case VICUS::BMSocket::Right		:
			// right side - expand rect to right
			r.setWidth(r.width()+textBoundingRect.width()+6);
		break;
		case VICUS::BMSocket::Top		:
			// top side - move top
			r.moveTop(r.top()-textBoundingRect.width()-6);
		break;
		case VICUS::BMSocket::Bottom		:
			r.setHeight(r.height() + textBoundingRect.width()+6);
		break;
	}
	return r;
}

QPointF SVBMSocketItem::pos(){
	return QPointF(m_block->m_pos.x() + m_socket->m_pos.x(),m_block->m_pos.y() + m_socket->m_pos.y());
}


// *** protected functions ***

void SVBMSocketItem::hoverEnterEvent (QGraphicsSceneHoverEvent *event) {
	if(m_socket->m_isSocketOfConnector) return;
	SVBMSceneManager * sceneManager = qobject_cast<SVBMSceneManager *>(scene());
	// for outlet sockets, we allow hovering if:
	// - scene is not currently in connecting mode

	// for inlet sockets, we only allow hovering if:
	// - scene is in connecting mode
	// - socket is not yet occupied

	if (sceneManager) {
		if ( (!m_socket->m_isInlet && !sceneManager->isCurrentlyConnecting()) ||
			(m_socket->m_isInlet && sceneManager->isCurrentlyConnecting() ))
		{
			if (QApplication::overrideCursor() == nullptr)
				QApplication::setOverrideCursor(Qt::CrossCursor);
			m_hovered = true;
		}
	 }
	QGraphicsItem::hoverEnterEvent(event);
}


void SVBMSocketItem::hoverLeaveEvent (QGraphicsSceneHoverEvent *event) {
	if(m_socket->m_isSocketOfConnector) return;
	if (m_hovered)
		QApplication::restoreOverrideCursor();
	m_hovered = false;
	QGraphicsItem::hoverLeaveEvent(event);
}


void SVBMSocketItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/ ) {
	if(m_socket->m_isSocketOfConnector) return;
	// special handling for invisible blocks
	SVBMBlockItem * bi = dynamic_cast<SVBMBlockItem*>(parentItem());
	if (bi->block()->m_mode == VICUS::BMBlockType::InvisibleBlock)
		return; // nothing to be drawn
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing, true);
	// Socket items are children of the blocks.
	// Coordinates are hence defined with respect to the parent item's coordinate system.
	// 0,0 is the top-left corner of the parent block.

	// distinguish between inlet and outlet sockets
	QRectF r = m_symbolRect;
	if (m_socket->m_isInlet) {
		painter->setBrush(Qt::white);
		switch (m_socket->direction()) {
			case VICUS::BMSocket::Left		:
				// left side
				painter->setPen(Qt::white);
				painter->drawPie(r, 90*16, -180*16);
				painter->setPen(Qt::black);
				painter->drawArc(r, 90*16, -180*16);
			break;
			case VICUS::BMSocket::Right		:
				// right side
				painter->setPen(Qt::white);
				painter->drawPie(r, 90*16, 180*16);
				painter->setPen(Qt::black);
				painter->drawArc(r, 90*16, 180*16);
			break;
			case VICUS::BMSocket::Top		:
				// top side
				painter->setPen(Qt::white);
				painter->drawPie(r, 0*16, -180*16);
				painter->setPen(Qt::black);
				painter->drawArc(r, 0*16, -180*16);
			break;
			case VICUS::BMSocket::Bottom		:
				// bottom side
				painter->setPen(Qt::white);
				painter->drawPie(r, 0*16, 180*16);
				painter->setPen(Qt::black);
				painter->drawArc(r, 0*16, 180*16);
			break;
		}
		// if socket is connected, paint a circle
		SVBMSceneManager * sceneManager = qobject_cast<SVBMSceneManager *>(scene());
		SVBMBlockItem * blockItem = dynamic_cast<SVBMBlockItem *>(parentItem());
		if (sceneManager != nullptr && blockItem != nullptr && sceneManager->isConnectedSocket(blockItem->block(), m_socket)) {
			painter->save();
			painter->setPen(Qt::NoPen);
			painter->setBrush(Qt::black);
			QRectF r2(r.x()+2, r.y()+2, r.width() - 4, r.height() - 4);
			painter->drawEllipse(r2);
			painter->restore();
		}

		if (m_hovered) {
			painter->save();
			QPen p(QColor(192,0,0), 0.8);
			painter->setPen(p);
			painter->setBrush(QBrush(QColor(96,0,0)));
			QRectF r2(r.x()-1, r.y()-1, r.width() + 2, r.height() + 2);
			painter->drawEllipse(r2);
			painter->restore();
		}
	}
	else {
		QPainterPath p;
		switch (m_socket->direction()) {
			case VICUS::BMSocket::Left		:
				// left side
				p.moveTo(m_symbolRect.right(), m_symbolRect.y());
				p.lineTo(m_symbolRect.left(), 0.5*(m_symbolRect.top() + m_symbolRect.bottom()));
				p.lineTo(m_symbolRect.right(), m_symbolRect.bottom());
				p.lineTo(m_symbolRect.right(), m_symbolRect.y()); // Close the triangle
				break;

			case VICUS::BMSocket::Right		:
				// right side
				p.moveTo(m_symbolRect.left(), m_symbolRect.y());
				p.lineTo(m_symbolRect.right(), 0.5*(m_symbolRect.top() + m_symbolRect.bottom()));
				p.lineTo(m_symbolRect.left(), m_symbolRect.bottom());
				p.lineTo(m_symbolRect.left(), m_symbolRect.y()); // Close the triangle
				break;

			case VICUS::BMSocket::Top		:
				// top side
				p.moveTo(m_symbolRect.left(), m_symbolRect.bottom());
				p.lineTo(0.5*(m_symbolRect.left() + m_symbolRect.right()), m_symbolRect.top());
				p.lineTo(m_symbolRect.right(), m_symbolRect.bottom());
				p.lineTo(m_symbolRect.left(), m_symbolRect.bottom()); // Close the triangle
				break;

			case VICUS::BMSocket::Bottom		:
				// bottom side
				p.moveTo(m_symbolRect.left(), m_symbolRect.top());
				p.lineTo(0.5*(m_symbolRect.left() + m_symbolRect.right()), m_symbolRect.bottom());
				p.lineTo(m_symbolRect.right(), m_symbolRect.top());
				p.lineTo(m_symbolRect.left(), m_symbolRect.top()); // Close the triangle
				break;
		}
		QPen pen(Qt::black);
		pen.setCapStyle(Qt::RoundCap);
		painter->setPen(pen);
		if (m_hovered)
			painter->fillPath(p, Qt::white);
		else
			painter->setBrush(QColor(0,0,196));
		painter->drawPath(p);
	}

	painter->restore();
}


void SVBMSocketItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	// if the socket belongs to a ConnectorBlock, we let the click pass through
	if(m_socket->m_isSocketOfConnector){
		QGraphicsItem::mousePressEvent(event);
		return;
	}

	// starting a connection?
	// ignore clicks on inlet sockets
	if (!m_socket->m_isInlet) {
		if (event->button() == Qt::LeftButton && event->modifiers() == Qt::NoModifier) {
			SVBMSceneManager * sceneManager = qobject_cast<SVBMSceneManager *>(scene());
			if (sceneManager) {
				QPointF p = event->pos(); // this is the position of the socket relative to the parent block
				p = mapToScene(p); // this is the global scene coordinate
				sceneManager->startSocketConnection(*this, p);
				event->accept(); // needed or fall through?
			}
		}
	}
}



