/*	SIM-VICUS - Building and District Energy Simulation Tool.

	Copyright (c) 2020-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Dirk Weiss  <dirk.weiss -[at]- tu-dresden.de>
	  Stephan Hirth  <stephan.hirth -[at]- tu-dresden.de>
	  Hauke Hirsch  <hauke.hirsch -[at]- tu-dresden.de>

	  ... all the others from the SIM-VICUS team ... :-)

	This program is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#include "SVNavigationTreeItemDelegate.h"

#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

#include "SVUndoTreeNodeState.h"

SVNavigationTreeItemDelegate::SVNavigationTreeItemDelegate(QWidget * parent) :
	QItemDelegate(parent)
{
	m_lightBulbOn = QImage("://gfx/actions/16x16/help-hint.png");
	m_lightBulbOff = QImage("://gfx/actions/16x16/help-hint_gray.png");
	m_selectedOn = QImage("://gfx/actions/16x16/checkbox-full.png");
	m_selectedOff = QImage("://gfx/actions/16x16/checkbox-empty.png");
}


void SVNavigationTreeItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
	// get rectangle of area to paint into
	QRect targetRect(option.rect);

	// Note: the first part of the widget (the branch indicator) is not drawn by us, but rather by the tree view itself
	//       to change that, we would need to derive from QTreeView and overload/re-implement drawRow().
	//       --> later

	unsigned int uniqueObjectId = index.data(NodeID).toUInt();

	if (index.parent() == QModelIndex() || uniqueObjectId == 0) {
		// check if item is selected/current
		bool isSelected = option.state & QStyle::State_Selected;
		QFont f = painter->font();
		f.setBold(isSelected);
		painter->setFont(f);
		// TODO  : change text color in case of invalid properties
//		painter->setPen( option.palette.color(QPalette::Text));
//		painter->setPen( Qt::green);
		painter->drawText(targetRect, Qt::AlignLeft | Qt::AlignVCenter, index.data(Qt::DisplayRole).toString());
		return;
	}

	// TODO : find out if the element we are painting is visible or not
	bool visible = index.data(VisibleFlag).toBool();

	const QImage * bulbImg = nullptr;
	if (visible)
		bulbImg = &m_lightBulbOn;
	else
		bulbImg = &m_lightBulbOff;

	QRect iconRect(targetRect.x(), targetRect.y(), 16, 16);
	painter->drawImage(iconRect, *bulbImg, QRect(0,0,16,16));

	bool selected = index.data(SelectedFlag).toBool();
	const QImage * selectedImg = nullptr;
	if (selected)
		selectedImg = &m_selectedOn;
	else
		selectedImg = &m_selectedOff;
	iconRect.setX(iconRect.x()+18);
	painter->drawImage(iconRect, *selectedImg, QRect(0,0,16,16));

	// adjust text rectangle
	targetRect.setX(targetRect.x()+36);

	// check if item is selected/current
	bool isSelected = option.state & QStyle::State_Selected;
	QFont f = painter->font();
	f.setBold(isSelected);
	painter->setFont(f);

	painter->drawText(targetRect, Qt::AlignLeft | Qt::AlignVCenter, index.data(Qt::DisplayRole).toString());
}


bool SVNavigationTreeItemDelegate::editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index) {
	// top-level index does not have any attributes
	if (index.parent() == QModelIndex()) {
		return QItemDelegate::editorEvent(event, model, option, index);
	}
	if (event->type() == QEvent::MouseButtonRelease) {
		QMouseEvent * mouseEvent = dynamic_cast<QMouseEvent*>(event);
		if (mouseEvent != nullptr && (mouseEvent->button() & Qt::LeftButton)) {
			QRect targetRect(option.rect);
			QRect iconRect(targetRect.x(), targetRect.y(), 16, 16);
			if (iconRect.contains(mouseEvent->x(), mouseEvent->y())) {
				// turn visibility of item on/off
				bool visible = index.data(VisibleFlag).toBool();
				bool withoutChildren = mouseEvent->modifiers() & Qt::ShiftModifier;
				unsigned int nodeID = index.data(NodeID).toUInt();
				if (nodeID != 0) {
					// compose an undo action that shows/hides objects
					SVUndoTreeNodeState * action = SVUndoTreeNodeState::createUndoAction(tr("Visibility changed"),
																		   SVUndoTreeNodeState::VisibilityState,
																		   nodeID,
																		   !withoutChildren,
																		   !visible);
					action->push();
				}
			}
			iconRect = QRect(targetRect.x() + 18, targetRect.y(), 16, 16);
			if (iconRect.contains(mouseEvent->x(), mouseEvent->y())) {
				// turn visibility of item on/off
				bool selected = index.data(SelectedFlag).toBool();
				bool withoutChildren = mouseEvent->modifiers() & Qt::ShiftModifier;
				unsigned int nodeID = index.data(NodeID).toUInt();
				if (nodeID != 0) {
					// compose an undo action that selects/de-selects objects
					SVUndoTreeNodeState * action = SVUndoTreeNodeState::createUndoAction(tr("Selection changed"),
																		   SVUndoTreeNodeState::SelectedState,
																		   nodeID,
																		   !withoutChildren,
																		   !selected);
					action->push();
				}
			}
		}

	}

	return QItemDelegate::editorEvent(event, model, option, index);
}
