#ifndef SVSUBNETWORKCOMPONENTDBEDITWIDGET_H
#define SVSUBNETWORKCOMPONENTDBEDITWIDGET_H

#include "SVAbstractDatabaseEditWidget.h"

namespace Ui {
class SVSubNetworkComponentDBEditWidget;
}

class SVNetworkComponentEditWidget;

class SVSubNetworkComponentDBEditWidget : public SVAbstractDatabaseEditWidget
{
	Q_OBJECT

public:
	explicit SVSubNetworkComponentDBEditWidget(QWidget *parent = nullptr);
	~SVSubNetworkComponentDBEditWidget();

	// SVAbstractDatabaseEditWidget interface
	void updateInput(int id);
	void setup(SVDatabase * db, SVAbstractDatabaseTableModel * dbModel);

private:
	Ui::SVSubNetworkComponentDBEditWidget	*m_ui;
	SVDatabase								*m_db;
	SVAbstractDatabaseTableModel			*m_dbModel;

	SVNetworkComponentEditWidget			*m_networkComponentEditWidget;

};

#endif // SVSUBNETWORKCOMPONENTDBEDITWIDGET_H
