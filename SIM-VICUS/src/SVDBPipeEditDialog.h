#ifndef SVDBPIPEEDITDIALOG_H
#define SVDBPIPEEDITDIALOG_H

#include "SVAbstractDatabaseEditDialog.h"

class QToolButton;
class SVDBPipeDelegate;

class SVDBPipeEditDialog : public SVAbstractDatabaseEditDialog
{
	Q_OBJECT
public:
	SVDBPipeEditDialog(QWidget *parent, SVAbstractDatabaseTableModel * tableModel,
					   SVAbstractDatabaseEditWidget * editWidget,
					   const QString & title, const QString & editWidgetTitle,
					   bool horizontalLayout);

	void selectPipes(unsigned int initialId, std::vector<unsigned int>& vectorPipes);

	void setSelected(unsigned int id);

private slots:
	void					on_m_toolButtonSelect_clicked();

	void					on_m_toolButtonDeselect_clicked();

private:

	void					setMarkedElements(bool selected = true);

	QToolButton				*m_toolButtonSelect = nullptr;
	QToolButton				*m_toolButtonDeselect = nullptr;
	SVDBPipeDelegate		*m_delegate = nullptr;
};

#endif // SVDBPIPEEDITDIALOG_H
