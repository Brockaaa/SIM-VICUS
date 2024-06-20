#include "SVSubNetworkComponentDBEditDialog.h"
#include "ui_SVAbstractDatabaseEditDialog.h"

#include "SVAbstractDatabaseEditDialog.h"
#include "SVDatabaseSortFilterProxyModel.h"
#include "SVAbstractDatabaseEditWidget.h"

#include "SVConstants.h"

#include <QToolButton>
#include <QTableView>
#include <QDebug>

SVSubNetworkComponentDBEditDialog::SVSubNetworkComponentDBEditDialog(QWidget *parent, SVAbstractDatabaseTableModel * tableModel,
																	 SVAbstractDatabaseEditWidget * editWidget,
																	 const QString & title, const QString & editWidgetTitle,
																	 bool horizontalLayout)
	: SVAbstractDatabaseEditDialog(parent, tableModel, editWidget, title, editWidgetTitle, horizontalLayout)
{
	toolButtonRemove = new QToolButton(m_ui->groupBoxTableView);
	toolButtonRemove->setObjectName(QString::fromUtf8("toolButtonRemove"));
	QIcon icon4;
	icon4.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
	toolButtonRemove->setIcon(icon4);
	toolButtonRemove->setIconSize(QSize(24, 24));
	m_ui->gridLayoutTableView->addWidget(toolButtonRemove, 3, 0, 1, 1);

	m_ui->label_3->setVisible(false);
	m_ui->frameProject->setVisible(false);

	connect(toolButtonRemove, &QToolButton::clicked, this, &SVSubNetworkComponentDBEditDialog::on_toolButtonRemove_clicked);
	connect(m_ui->tableView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
			this, SLOT(onCurrentIndexChanged(const QModelIndex &, const QModelIndex &)) );
}

void SVSubNetworkComponentDBEditDialog::on_toolButtonRemove_clicked()
{
	toolButtonRemove->setFocus(); // move focus to trigger "leave" events in line edits
	QModelIndex currentProxyIndex = m_ui->tableView->currentIndex();
	Q_ASSERT(currentProxyIndex.isValid());
	QModelIndex sourceIndex = m_proxyModel->mapToSource(currentProxyIndex);
	m_dbModel->deleteItem(sourceIndex);
	// last construction removed? clear input widget
	if (m_dbModel->rowCount() == 0)
		onCurrentIndexChanged(QModelIndex(), QModelIndex());
	// in case index has not changed after action: we trigger the slot manually to ensure an update of the editing widget
	if (currentProxyIndex == m_ui->tableView->currentIndex())
		onCurrentIndexChanged(m_ui->tableView->currentIndex(), QModelIndex());
}

void SVSubNetworkComponentDBEditDialog::onCurrentIndexChanged(const QModelIndex & current, const QModelIndex &previous){
	// if there is no selection, deactivate all buttons that need a selection
	if (!current.isValid()) {
		toolButtonRemove->setEnabled(false);
	}
	else {
		// remove is not allowed for built-ins
		QModelIndex sourceIndex = m_proxyModel->mapToSource(current);
		bool builtIn = sourceIndex.data(Role_BuiltIn).toBool();
		toolButtonRemove->setEnabled(!builtIn);
	}
}
