#ifndef SVSUBNETWORKCOMPONENTDBEDITWIDGET_H
#define SVSUBNETWORKCOMPONENTDBEDITWIDGET_H

#include "SVAbstractDatabaseEditWidget.h"

namespace Ui {
class SVSubNetworkComponentDBEditWidget;
}

class SVSubNetworkComponentDBEditWidget : public SVAbstractDatabaseEditWidget
{
	Q_OBJECT

public:
	explicit SVSubNetworkComponentDBEditWidget(QWidget *parent = nullptr);
	~SVSubNetworkComponentDBEditWidget();

private:
	Ui::SVSubNetworkComponentDBEditWidget *m_ui;

	// SVAbstractDatabaseEditWidget interface
public:
	void updateInput(int id);
	void setup(SVDatabase * db, SVAbstractDatabaseTableModel * dbModel);
};

#endif // SVSUBNETWORKCOMPONENTDBEDITWIDGET_H
