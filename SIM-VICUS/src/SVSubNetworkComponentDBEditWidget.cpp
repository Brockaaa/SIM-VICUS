#include "SVSubNetworkComponentDBEditWidget.h"
#include "ui_SVSubNetworkComponentDBEditWidget.h"

#include "SVNetworkComponentEditWidget.h"

SVSubNetworkComponentDBEditWidget::SVSubNetworkComponentDBEditWidget(QWidget *parent)
	: SVAbstractDatabaseEditWidget(parent)
	, m_ui(new Ui::SVSubNetworkComponentDBEditWidget)
{
	m_ui->setupUi(this);
	m_ui->verticalLayout->addWidget( new SVNetworkComponentEditWidget(this, true));
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
