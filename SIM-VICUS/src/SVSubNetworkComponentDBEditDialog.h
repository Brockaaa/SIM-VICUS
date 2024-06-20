#ifndef SVSUBNETWORKCOMPONENTDBEDITDIALOG_H
#define SVSUBNETWORKCOMPONENTDBEDITDIALOG_H

#include "SVAbstractDatabaseEditDialog.h"

class QToolButton;

class SVSubNetworkComponentDBEditDialog : public SVAbstractDatabaseEditDialog
{
	Q_OBJECT

public:
	SVSubNetworkComponentDBEditDialog(QWidget *parent, SVAbstractDatabaseTableModel * tableModel,
									  SVAbstractDatabaseEditWidget * editWidget,
									  const QString & title, const QString & editWidgetTitle,
									  bool horizontalLayout);

private slots:
	void on_toolButtonRemove_clicked();

	void onCurrentIndexChanged(const QModelIndex &current, const QModelIndex &previous);

private:
	QToolButton						*toolButtonRemove = nullptr;

};

#endif // SVSUBNETWORKCOMPONENTDBEDITDIALOG_H
