#include "SVSubNetworkComponentDBEditWidget.h"
#include "ui_SVSubNetworkComponentDBEditWidget.h"

SVSubNetworkComponentDBEditWidget::SVSubNetworkComponentDBEditWidget(QWidget *parent)
	: SVAbstractDatabaseEditWidget(parent)
	, m_ui(new Ui::SVSubNetworkComponentDBEditDialog)
{
	m_ui->setupUi(this);
}

SVSubNetworkComponentDBEditWidget::~SVSubNetworkComponentDBEditWidget()
{
	delete m_ui;
}

void SVSubNetworkComponentDBEditWidget::updateInput(int id)
{

}

void SVSubNetworkComponentDBEditWidget::setup(SVDatabase * db, SVAbstractDatabaseTableModel * dbModel)
{

}
