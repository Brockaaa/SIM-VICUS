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

#include "SVBMBlockItem.h"

#include <cmath>
#include <iostream>

#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QFontMetrics>
#include <QApplication>

#include "NANDRAD_HydraulicNetworkControlElement.h"
#include "NANDRAD_HydraulicNetworkComponent.h"

#include "VICUS_BMBlock.h"
#include "VICUS_BMGlobals.h"
#include "VICUS_NetworkComponent.h"
#include "VICUS_KeywordListQt.h"
#include "SVBMSocketItem.h"
#include "SVBMSceneManager.h"


SVBMBlockItem::SVBMBlockItem(VICUS::BMBlock * b, VICUS::NetworkComponent::ModelType modelType) :
	QGraphicsRectItem(),
	m_block(b),
	m_componentModelType(modelType)
{
	setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);
	setZValue(10);
	setAcceptHoverEvents(true);
	createSocketItems();
}

bool SVBMBlockItem::acceptingConnection(const QPointF & scenePos){
	if(this->m_block->m_mode == VICUS::InvisibleBlock || this->m_block->m_mode == VICUS::GlobalInlet) return false;

	if(this->boundingRect().contains(scenePos - this->pos())){
		return true;
	}
	return false;
}


SVBMSocketItem * SVBMBlockItem::inletSocketAcceptingConnection(const QPointF & scenePos) {
	for (SVBMSocketItem * si : m_socketItems) {
		QPointF socketScenePos = si->mapToScene(si->socket()->m_pos);

		socketScenePos -= scenePos;
		double d = socketScenePos.manhattanLength();
		if (d < 11) { // half grid spacing snapping tolerance

			return si;
		}
	}
	return nullptr;
}


QRectF SVBMBlockItem::boundingRect() const {
	QRectF r = QGraphicsRectItem::boundingRect();
	return r;
}


// *** protected functions ***


void SVBMBlockItem::createSocketItems() {
	Q_ASSERT(m_socketItems.isEmpty());

	// the socket items are children of the block item and are added/removed together with the
	// parent block item
	for (VICUS::BMSocket & s : m_block->m_sockets) {
		// create a socket item
		SVBMSocketItem * item = new SVBMSocketItem(this, &s, m_componentModelType);
		// enable hover-highlight on outlet nodes
		if (!s.m_isInlet) {
			item->setZValue(20); // outlet nodes are drawn over lines
		}

		QPointF position = s.m_pos;
		position.setY(item->boundingRect().y()+4);
		s.m_pos = position;

		m_socketItems.append(item);
	}
}


void SVBMBlockItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget */*widget*/) {
	// special handling for invisible blocks
	if (m_block->m_mode == VICUS::BMBlockType::InvisibleBlock)
		return; // nothing to be drawn

	// implemented drawing function for a ConnectorBlock
	if(m_block->m_mode == VICUS::BMBlockType::ConnectorBlock){
		painter->save();
		painter->setRenderHint(QPainter::Antialiasing, true);

		bool selected = (option->state & QStyle::State_Selected);

		QPen p;

		if(selected) {
			painter->setPen(QPen(QBrush(QColor(0,128,0)), 1.5));
			p.setColor(QColor(192,0,0));
			p.setStyle(Qt::DashLine);
		}
		else {
			p.setStyle(Qt::SolidLine);
			p.setColor(Qt::black);
		}

		if(m_isHighlighted) {
			p.setWidthF(1.6);
		}

		// Set brush to solid black
		painter->setBrush(QColor(Qt::black));

		painter->setPen(p);
		painter->drawEllipse(rect());
		painter->restore();
		return;
	}


	painter->save();
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
	bool selected = option->state & QStyle::State_Selected;

	QPen p;
	if(m_block->m_mode == VICUS::BMBlockType::NetworkComponentBlock)
	{
		if (m_block->m_properties.contains("ShowPixmap") &&
			m_block->m_properties["ShowPixmap"].toBool() &&
			m_block->m_properties.contains("Pixmap"))
		{
			// fill entire background with white
			QRectF r = rect();
			painter->setBrush(Qt::white);

			QPixmap p = m_block->m_properties["Pixmap"].value<QPixmap>();
			painter->drawPixmap(r, p, p.rect());
			painter->setBrush(Qt::NoBrush);
		}
		else {
			QLinearGradient grad(QPointF(0,0), QPointF(rect().width(),0));
			if (selected) {
				painter->setPen(QPen(QBrush(QColor(0,128,0)), 1.5));
				grad.setColorAt(0, QColor(230,255,230));
				grad.setColorAt(1, QColor(200,240,180));
			}
			else {
				grad.setColorAt(0, QColor(196,196,255));
				grad.setColorAt(1, QColor(220,220,255));
			}
			painter->setBrush(grad);
			painter->fillRect(rect(), grad);
		}

		if(!selected){
			p.setStyle(Qt::SolidLine);
			p.setColor(Qt::black);
			painter->setPen( p );
		} else
		{
			p.setColor(QColor(192,0,0));
			p.setStyle(Qt::DashLine);
			painter->setPen(p);
		}
	}
	else {
		QPainterPath bigPath;
		QPainterPath smallPath;

		if(m_block->m_mode == VICUS::BMBlockType::GlobalOutlet){
			QRectF bigEllipse(-7, 0, 50, 50);
			QRectF smallEllipse(-25, (50-33)/2, 33, 33);
			bigPath.addEllipse(bigEllipse);
			smallPath.addEllipse(smallEllipse);
		} else {
			QRectF bigEllipse(7, 0, 50, 50);
			QRectF smallEllipse(43, (50-33)/2, 33, 33);
			bigPath.addEllipse(bigEllipse);
			smallPath.addEllipse(smallEllipse);
		}

		// Subtract the smaller ellipse from the bigger one to form the crescent shape
		QPainterPath crescentPath = bigPath.subtracted(smallPath);

		QLinearGradient grad(QPointF(0,0), QPointF(rect().width(),0));
		if (selected) {
			painter->setPen(QPen(QBrush(QColor(0,128,0)), 1.5));
			grad.setColorAt(0, QColor(230,255,230));
			grad.setColorAt(1, QColor(200,240,180));
		}
		else {
			grad.setColorAt(0, QColor(196,196,255));
			grad.setColorAt(1, QColor(220,220,255));
		}

		painter->fillPath(crescentPath, grad);

		if(!selected){
			p.setStyle(Qt::SolidLine);
			p.setColor(Qt::black);
			painter->setPen( p );
		} else
		{
			p.setColor(QColor(192,0,0));
			p.setStyle(Qt::DashLine);
			painter->setPen(p);
		}
		painter->drawPath(crescentPath);
	}
	QFontMetrics fm(painter->font());
	QRectF r = fm.boundingRect(m_block->m_displayName);
	r.moveTo((m_block->m_size.width() - r.width())/2, r.top() - 15);
	painter->drawText(r, Qt::AlignCenter | Qt::AlignHCenter, m_block->m_displayName);

	if(!m_controllerName.isEmpty()){
		QFontMetrics fm(painter->font());

		// Check length and insert line break if necessary
		int maxTextWidth = 200; // max width before we need to break the line
		QString elidedText = fm.elidedText(m_controllerName, Qt::ElideRight, maxTextWidth);

		// Calculate text rectangle
		QRectF textRect = fm.boundingRect(elidedText);
		//textRect.setWidth(std::max((int)textRect.width(), maxTextWidth)); // ensure at least maxTextWidth

		// Compute position of the second rectangle
		QRectF secondRect(-(textRect.width() - rect().height()) / 2, rect().height(), textRect.width(), textRect.height());

		// Set color and draw the second rectangle
		QLinearGradient grad2(QPointF(0, 0), QPointF(secondRect.width(), 0));
		grad2.setColorAt(0, QColor(255,255,255));
		grad2.setColorAt(1, QColor(255,255,255));
		painter->setBrush(grad2);
		painter->fillRect(secondRect, grad2);
		painter->setPen(p);
		painter->drawRect(secondRect);

		// Draw the text centered
		textRect.moveTo(-(textRect.width() - rect().height()) / 2, rect().height());
		painter->drawText(textRect, Qt::AlignCenter | Qt::AlignHCenter, elidedText);
	}


	painter->restore();
}


void SVBMBlockItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	if (event->button() == Qt::LeftButton && event->modifiers().testFlag(Qt::ControlModifier)) {
		setSelected(true);
		event->accept();
		return;
	}
	if (event->button() == Qt::LeftButton && !m_moved) {
	}
	QGraphicsRectItem::mouseReleaseEvent(event);
	m_moved = false;
}

void SVBMBlockItem::hoverEnterEvent (QGraphicsSceneHoverEvent *event){
	QGraphicsItem::hoverEnterEvent(event);
	if(m_block->m_mode == VICUS::BMBlockType::ConnectorBlock){
		SVBMSceneManager * sceneManager = qobject_cast<SVBMSceneManager *>(scene());
		sceneManager->setHighlightallConnectorsOfBlock(block(), true);
		m_isHighlighted = true;
	}
}

void SVBMBlockItem::hoverLeaveEvent (QGraphicsSceneHoverEvent *event){
	QGraphicsItem::hoverLeaveEvent(event);
	if(m_block->m_mode == VICUS::BMBlockType::ConnectorBlock){
		SVBMSceneManager * sceneManager = qobject_cast<SVBMSceneManager *>(scene());
		sceneManager->setHighlightallConnectorsOfBlock(block(), false);
		m_isHighlighted = false;
	}
}

void SVBMBlockItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
	if(m_block->m_mode == VICUS::InvisibleBlock || m_block->m_mode == VICUS::GlobalOutlet){
		QGraphicsItem::mouseDoubleClickEvent(event);
		return;
	}

	SVBMSceneManager * sceneManager = qobject_cast<SVBMSceneManager *>(scene());
	if(sceneManager) {
		QPointF p = event->lastScenePos();
		SVBMSocketItem *socketItem = (this->block()->m_mode == VICUS::GlobalInlet) ? m_socketItems[0] : m_socketItems[1];
		sceneManager->startSocketConnection(*socketItem, p);
		if (QApplication::overrideCursor() == nullptr)
			QApplication::setOverrideCursor(Qt::CrossCursor);
		event->accept();
	}
}


QVariant SVBMBlockItem::itemChange(GraphicsItemChange change, const QVariant & value) {
	switch (change) {
	case QGraphicsItem::ItemPositionChange : {
		SVBMSceneManager * sceneManager = qobject_cast<SVBMSceneManager *>(scene());

		// snap to grid
		QPointF pos = value.toPointF();

		// apply true rounding
		pos.setX( std::floor((pos.x()+0.5)));
		pos.setY( std::floor((pos.y()+0.5)));
		if (m_block->m_pos != pos.toPoint()) {
			m_moved = true;
			QPointF oldPos = m_block->m_pos;
			m_block->m_pos = pos.toPoint();
			// inform network to update connectors
			if (sceneManager != nullptr)
				sceneManager->blockMoved(m_block, oldPos);
		}
		return pos;
	}

	case QGraphicsItem::ItemSelectedHasChanged : {
		SVBMSceneManager * sceneManager = qobject_cast<SVBMSceneManager *>(scene());
		if (value.toBool())
			sceneManager->blockSelected(m_block);
	} break;
	default :;
	}
	return QGraphicsRectItem::itemChange(change, value);
}

QPainterPath SVBMBlockItem::shape() const
{
	QPainterPath path;
	path.addRect(SVBMBlockItem::boundingRect());
	return path;
}
