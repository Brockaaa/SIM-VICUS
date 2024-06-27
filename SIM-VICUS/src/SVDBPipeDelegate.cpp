#include "SVDBPipeDelegate.h"
#include "SVSettings.h"
#include "SVConstants.h"
#include "SVDBPipeEditDialog.h"
#include "SVDBPipeSelectionTableModel.h"

#include <QPainter>
#include <QMouseEvent>

SVDBPipeDelegate::SVDBPipeDelegate(QWidget * parent, SVAbstractDatabaseTableModel* dbModel) :
	QStyledItemDelegate(parent),
	m_dbModel(static_cast<SVDBPipeSelectionTableModel*>(dbModel))
{
	onStyleChanged();
}

void SVDBPipeDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	// get rectangle of area to paint into
	QRect targetRect(option.rect);
	targetRect.setWidth(20);
	targetRect.setHeight(20);
	QRect iconRect(targetRect.x(), targetRect.y() + 2, 20, 20);
	QRect iconSourceRect(0, 0, 256, 256);

	// decide if element is selected, draw checkbox accordingly
	bool selected = index.data(Role_PreselectedForProject).toBool();
	const QPixmap * selectedImg = nullptr;
	if (selected)
		selectedImg = &m_selectedOn;
	else
		selectedImg = &m_selectedOff;
	const_cast<QPixmap*>(selectedImg)->setDevicePixelRatio(SVSettings::instance().m_ratio);
	painter->drawPixmap(targetRect, *selectedImg, iconSourceRect);
}

bool SVDBPipeDelegate::editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index)
{
	if (event->type() == QEvent::MouseButtonRelease) {
		QMouseEvent * mouseEvent = dynamic_cast<QMouseEvent*>(event);
		if (mouseEvent != nullptr && (mouseEvent->button() & Qt::LeftButton)) {
			// calculate if user clicked on icon
			QRect targetRect(option.rect);
			QRect iconRect(targetRect.x(), targetRect.y() + 2, 20, 20);
			// if user clicked on icon, set m_selected to true and update table view
			if (iconRect.contains(mouseEvent->x(), mouseEvent->y())) {
				VICUS::NetworkPipe* selectedPipe = SVSettings::instance().m_db.m_pipes[index.data(Role_Id).toUInt()];
				Q_ASSERT(selectedPipe);
				selectedPipe->m_selected = !selectedPipe->m_selected;
				m_dbModel->resetModel();
				return false; // handled
			}
		}
	}
	return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void SVDBPipeDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

QSize SVDBPipeDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	QSize sh = QStyledItemDelegate::sizeHint(option, index);
	sh.setHeight(20); // enough space for 16x16 icon
	sh.setWidth(20);
	return sh;
}

void SVDBPipeDelegate::onStyleChanged()
{
	QIcon checked = QIcon::fromTheme("checkbox_checked");
	m_selectedOn = QPixmap(checked.pixmap(256));
	QIcon unchecked = QIcon::fromTheme("checkbox_unchecked");
	m_selectedOff = QPixmap(unchecked.pixmap(256));
}
