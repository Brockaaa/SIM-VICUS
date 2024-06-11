#ifndef SVSUBNETWORKEDITDIALOGTABLEITEM_H
#define SVSUBNETWORKEDITDIALOGTABLEITEM_H

#include <QWidget>

namespace Ui {
class SVSubNetworkEditDialogTableItem;
}

class SVSubNetworkEditDialogTableItem : public QWidget
{
	Q_OBJECT

public:
	explicit SVSubNetworkEditDialogTableItem(QString filename, QString typeName, QString tooltip, int height, QWidget *parent = nullptr, bool modelType = false);
	~SVSubNetworkEditDialogTableItem();

	// true if the item related to this Table Item is an builtIn database element
	bool m_builtIn = false;

	bool m_local = false;

private:
	Ui::SVSubNetworkEditDialogTableItem *m_ui;
};

#endif // SVSUBNETWORKEDITDIALOGTABLEITEM_H
