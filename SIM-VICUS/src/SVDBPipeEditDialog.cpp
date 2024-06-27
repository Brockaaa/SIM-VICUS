#include "SVDBPipeEditDialog.h"
#include "ui_SVAbstractDatabaseEditDialog.h"

#include <QToolButton>
#include <QDebug>
#include <QItemSelectionModel>

#include "SVDBPipeTableModel.h"
#include "SVDBPipeEditWidget.h"
#include "SVDatabaseSortFilterProxyModel.h"
#include "SVDBPipeDelegate.h"

#include "SVSettings.h"
#include "SVProjectHandler.h"
#include "SVConstants.h"

SVDBPipeEditDialog::SVDBPipeEditDialog(QWidget *parent, SVAbstractDatabaseTableModel * tableModel,
									   SVAbstractDatabaseEditWidget * editWidget,
									   const QString & title, const QString & editWidgetTitle,
									   bool horizontalLayout)
		: SVAbstractDatabaseEditDialog(parent, tableModel, editWidget, title, editWidgetTitle, horizontalLayout)
	{
	m_ui->tableView->setColumnWidth(3, 21);
	m_ui->tableView->setColumnWidth(1, 30);

	// set a selection mode to enable multiple marked elements in the table view
	m_ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);

	// create ToolButton for selecting and deselecting multiple marked pipes
	m_toolButtonSelect = new QToolButton(this);
	m_toolButtonSelect->setText(tr("Select"));
	QIcon iconPlus;
	iconPlus.addFile(QString::fromUtf8(":/gfx/actions/24x24/plus.png"), QSize(), QIcon::Normal, QIcon::Off);
	m_toolButtonSelect->setIcon(iconPlus);
	m_toolButtonSelect->setIconSize(QSize(24, 24));
	m_toolButtonSelect->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

	m_ui->gridLayoutTableView->addWidget(m_toolButtonSelect, 3, 0, 1, 1);

	m_toolButtonDeselect = new QToolButton(this);
	m_toolButtonDeselect->setText(tr("Deselect"));
	QIcon iconMinus;
	iconMinus.addFile(QString::fromUtf8(":/gfx/actions/24x24/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
	m_toolButtonDeselect->setIcon(iconMinus);
	m_toolButtonDeselect->setIconSize(QSize(24, 24));
	m_toolButtonDeselect->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

	m_ui->gridLayoutTableView->addWidget(m_toolButtonDeselect, 3, 1, 1, 1);

	connect(m_toolButtonSelect, &QToolButton::clicked, this, &SVDBPipeEditDialog::on_m_toolButtonSelect_clicked);
	connect(m_toolButtonDeselect, &QToolButton::clicked, this, &SVDBPipeEditDialog::on_m_toolButtonDeselect_clicked);
}

void SVDBPipeEditDialog::selectPipes(unsigned int initialId, std::vector<unsigned int> & vectorPipes)
{
	m_ui->pushButtonClose->setVisible(false);
	m_ui->pushButtonSelect->setVisible(true);
	m_ui->pushButtonCancel->setVisible(true);

	m_dbModel->resetModel(); // ensure we use up-to-date data (in case the database data has changed elsewhere)
	selectItemById(initialId);
	onCurrentIndexChanged(m_ui->tableView->currentIndex(), QModelIndex()); // select nothing

	for (int i = 0; i < SVDBPipeTableModel::NumColumns; i++) {
		void resizeColumnToContents(int i);
	}

	// update "isRferenced" property of all elements
	if (SVProjectHandler::instance().isValid()){
		SVSettings::instance().m_db.updateReferencedElements(project());
	}

	for (auto& pipe : SVSettings::instance().m_db.m_pipes){
		pipe.second.m_selected = false;
	}

	for (unsigned int id : vectorPipes){
		VICUS::NetworkPipe* pipe = SVSettings::instance().m_db.m_pipes[id];
		Q_ASSERT(pipe);
		pipe->m_selected = true;
	}

	// create delegate for checkbox and assign it to column 3
	if(m_delegate != nullptr) delete m_delegate;
	m_delegate = new SVDBPipeDelegate(this, m_dbModel);
	m_ui->tableView->setItemDelegateForColumn(3, m_delegate);

	int res = exec();
	m_proxyModel->setFilterWildcard("");
	m_currentFilter = ""; // Reset filter

	if(QDialog::Accepted == res){
		vectorPipes.clear();
		for (auto pipe : SVSettings::instance().m_db.m_pipes){
			if (pipe.second.m_selected == true) {
				vectorPipes.push_back(pipe.second.m_id);
			}
		}
	}
}

void SVDBPipeEditDialog::setSelected(unsigned int id)
{
	VICUS::NetworkPipe* selectedPipe = SVSettings::instance().m_db.m_pipes[id];
	Q_ASSERT(selectedPipe);
	selectedPipe->m_selected = !selectedPipe->m_selected;
}


void SVDBPipeEditDialog::on_m_toolButtonSelect_clicked()
{
	setMarkedElements(true);
}

void SVDBPipeEditDialog::on_m_toolButtonDeselect_clicked()
{
	setMarkedElements(false);
}

void SVDBPipeEditDialog::setMarkedElements(bool selected)
{
	// get all marked elements
	QItemSelectionModel* selectionModel = m_ui->tableView->selectionModel();
	QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

	// set them selected
	for (auto index : selectedIndexes) {
		unsigned int id = index.data(Role_Id).toUInt();
		SVSettings::instance().m_db.m_pipes[id]->m_selected = selected;
	}
	//update table view
	m_dbModel->resetModel();
}
