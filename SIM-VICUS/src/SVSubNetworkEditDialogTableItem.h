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
	explicit SVSubNetworkEditDialogTableItem(QString filename, QString typeName, QString tooltip, int height, QWidget *parent = nullptr);
	~SVSubNetworkEditDialogTableItem();

private:
	Ui::SVSubNetworkEditDialogTableItem *m_ui;
};

#endif // SVSUBNETWORKEDITDIALOGTABLEITEM_H
