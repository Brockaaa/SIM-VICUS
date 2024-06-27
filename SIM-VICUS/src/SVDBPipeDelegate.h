#ifndef SVDBPIPEDELEGATE_H
#define SVDBPIPEDELEGATE_H

#include <QStyledItemDelegate>

class SVAbstractDatabaseTableModel;
class SVDBPipeSelectionTableModel;

class SVDBPipeDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	SVDBPipeDelegate(QWidget * parent, SVAbstractDatabaseTableModel* dbModel);

	// QAbstractItemDelegate interface

	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
	bool editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index) override;
	void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
	QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const override;

	/*! Updates icons */
	void onStyleChanged();

private:
	QPixmap		m_selectedOn;
	QPixmap		m_selectedOff;

	SVDBPipeSelectionTableModel*	m_dbModel;

};

#endif // SVDBPIPEDELEGATE_H
