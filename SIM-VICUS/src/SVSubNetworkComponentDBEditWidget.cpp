#include "SVSubNetworkComponentDBEditWidget.h"
#include "ui_SVSubNetworkComponentDBEditWidget.h"

#include "SVNetworkComponentEditWidget.h"

#include <VICUS_NetworkComponent.h>

SVSubNetworkComponentDBEditWidget::SVSubNetworkComponentDBEditWidget(QWidget *parent)
	: SVAbstractDatabaseEditWidget(parent)
	, m_ui(new Ui::SVSubNetworkComponentDBEditWidget)
{
	m_ui->setupUi(this);
	m_networkComponentEditWidget = new SVNetworkComponentEditWidget(this, true);
	m_networkComponentEditWidget->setMinimumWidth(475);
	m_ui->verticalLayout->addWidget(m_networkComponentEditWidget);
}

SVSubNetworkComponentDBEditWidget::~SVSubNetworkComponentDBEditWidget()
{
	delete m_ui;
}

void SVSubNetworkComponentDBEditWidget::updateInput(int id)
{
	if(id == -1) return;
	Q_ASSERT(m_db->m_networkComponents[id] != nullptr);
	VICUS::NetworkComponent *component = m_db->m_networkComponents[id];
	m_networkComponentEditWidget->updateInput(component);

}

void SVSubNetworkComponentDBEditWidget::setup(SVDatabase * db, SVAbstractDatabaseTableModel * dbModel)
{
	m_db = db;
	m_dbModel = dbModel;
}
