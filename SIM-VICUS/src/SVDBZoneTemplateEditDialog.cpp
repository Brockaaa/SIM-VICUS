#include "SVDBZoneTemplateEditDialog.h"
#include "ui_SVDBZoneTemplateEditDialog.h"

#include <QItemSelectionModel>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QGroupBox>

#include "SVSettings.h"
#include "SVStyle.h"
#include "SVConstants.h"
#include "SVDBModelDelegate.h"

#include "SVDBZoneTemplateEditWidget.h"
#include "SVDBZoneTemplateTreeModel.h"

SVDBZoneTemplateEditDialog::SVDBZoneTemplateEditDialog(QWidget *parent) :
	QDialog(parent),
	m_ui(new Ui::SVDBZoneTemplateEditDialog)
{
	// dialog most only be created by main window
	m_ui->setupUi(this);
	m_ui->gridLayoutTableView->setMargin(4);

	m_dbModel = new SVDBZoneTemplateTreeModel(this, SVSettings::instance().m_db);
	m_editWidget = new SVDBZoneTemplateEditWidget(this);

	SVStyle::formatDatabaseTreeView(m_ui->treeView);

	m_proxyModel = new QSortFilterProxyModel(this);
	m_proxyModel->setSourceModel(m_dbModel);
	m_ui->treeView->setModel(m_proxyModel);

	// create groupbox and adjust layout for edit widget
	m_groupBox = new QGroupBox(this);
	m_groupBox->setTitle(tr("Zone template properties"));
	m_ui->gridLayoutMaster->addWidget(m_groupBox, 0, 1);
	m_ui->horizontalLayout->setParent(nullptr);
	m_ui->gridLayoutMaster->addLayout(m_ui->horizontalLayout, 1, 0, 1, 2);

	QVBoxLayout * verticalLay = new QVBoxLayout(m_groupBox);
	verticalLay->addWidget(m_editWidget);
	m_groupBox->setLayout(verticalLay);
	verticalLay->setMargin(0);
	m_editWidget->setup(&SVSettings::instance().m_db, m_dbModel);

	// specific setup for DB table view
	m_ui->treeView->header()->setSectionResizeMode(SVDBZoneTemplateTreeModel::ColCheck, QHeaderView::Fixed);
	m_ui->treeView->header()->setSectionResizeMode(SVDBZoneTemplateTreeModel::ColColor, QHeaderView::Fixed);

	connect(m_editWidget, &SVDBZoneTemplateEditWidget::selectSubTemplate,
			this, &SVDBZoneTemplateEditDialog::onSelectSubTemplate);

	connect(m_ui->treeView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
			this, SLOT(onCurrentIndexChanged(const QModelIndex &, const QModelIndex &)) );

	// set item delegate for coloring built-ins
	SVDBModelDelegate * dg = new SVDBModelDelegate(this, Role_BuiltIn);
	m_ui->treeView->setItemDelegate(dg);
}


SVDBZoneTemplateEditDialog::~SVDBZoneTemplateEditDialog() {
	delete m_ui;
}


void SVDBZoneTemplateEditDialog::edit(unsigned int initialId) {

	// hide select/cancel buttons, and show "close" button
	m_ui->pushButtonClose->setVisible(true);
	m_ui->pushButtonSelect->setVisible(false);
	m_ui->pushButtonCancel->setVisible(false);

	// ask database model to update its content
	m_dbModel->resetModel(); // ensure we use up-to-date data (in case the database data has changed elsewhere)
	selectItemById(initialId);
	onCurrentIndexChanged(m_ui->treeView->currentIndex(), QModelIndex()); // select nothing

	m_ui->treeView->expandAll();
	m_ui->treeView->resizeColumnToContents(0);
	m_ui->treeView->resizeColumnToContents(1);
	m_ui->treeView->resizeColumnToContents(2);

	exec();
}


unsigned int SVDBZoneTemplateEditDialog::select(unsigned int initialId) {

	m_ui->pushButtonClose->setVisible(false);
	m_ui->pushButtonSelect->setVisible(true);
	m_ui->pushButtonCancel->setVisible(true);

	m_dbModel->resetModel(); // ensure we use up-to-date data (in case the database data has changed elsewhere)
	selectItemById(initialId);
	onCurrentIndexChanged(m_ui->treeView->currentIndex(), QModelIndex()); // select nothing

	m_ui->treeView->expandAll();
	m_ui->treeView->resizeColumnToContents(0);
	m_ui->treeView->resizeColumnToContents(1);
	m_ui->treeView->resizeColumnToContents(2);

	int res = exec();
	if (res == QDialog::Accepted) {
		// determine current item
		QModelIndex currentProxyIndex = m_ui->treeView->currentIndex();
		Q_ASSERT(currentProxyIndex.isValid());
		QModelIndex sourceIndex = m_proxyModel->mapToSource(currentProxyIndex);

		// if this is a child index, get the index of the parent
		if (sourceIndex.internalPointer() != nullptr)
			sourceIndex = sourceIndex.parent();

		// return ID
		return sourceIndex.data(Role_Id).toUInt();
	}

	// nothing selected/dialog aborted
	return VICUS::INVALID_ID;
}


void SVDBZoneTemplateEditDialog::on_pushButtonSelect_clicked() {
	accept();
}


void SVDBZoneTemplateEditDialog::on_pushButtonCancel_clicked() {
	reject();
}


void SVDBZoneTemplateEditDialog::on_pushButtonClose_clicked() {
	accept();
}


void SVDBZoneTemplateEditDialog::on_toolButtonAdd_clicked() {
	// add new item
	QModelIndex sourceIndex = m_dbModel->addNewItem();
	QModelIndex proxyIndex = m_proxyModel->mapFromSource(sourceIndex);
	m_ui->treeView->selectionModel()->setCurrentIndex(proxyIndex, QItemSelectionModel::SelectCurrent);
	// resize ID column
	sourceIndex = m_dbModel->index(0, SVDBZoneTemplateTreeModel::ColId, QModelIndex());
	proxyIndex = m_proxyModel->mapFromSource(sourceIndex);
	if (proxyIndex.isValid())
		m_ui->treeView->resizeColumnToContents(proxyIndex.column());
}


void SVDBZoneTemplateEditDialog::on_toolButtonCopy_clicked() {
	// determine current item
	QModelIndex currentProxyIndex = m_ui->treeView->currentIndex();
	Q_ASSERT(currentProxyIndex.isValid());
	QModelIndex sourceIndex = m_proxyModel->mapToSource(currentProxyIndex);
	// if this is a child index, get the index of the parent
	if (sourceIndex.internalPointer() != nullptr)
		sourceIndex = sourceIndex.parent();
	sourceIndex = m_dbModel->copyItem(sourceIndex);
	QModelIndex proxyIndex = m_proxyModel->mapFromSource(sourceIndex);
	m_ui->treeView->selectionModel()->setCurrentIndex(proxyIndex, QItemSelectionModel::SelectCurrent);
}


void SVDBZoneTemplateEditDialog::on_toolButtonRemove_clicked() {
	QModelIndex currentProxyIndex = m_ui->treeView->currentIndex();
	Q_ASSERT(currentProxyIndex.isValid());
	QModelIndex sourceIndex = m_proxyModel->mapToSource(currentProxyIndex);
	// if this is a child index, get the index of the parent
	if (sourceIndex.internalPointer() != nullptr)
		sourceIndex = sourceIndex.parent();
	m_dbModel->deleteItem(sourceIndex);
	// last construction removed? clear input widget
	if (m_dbModel->rowCount() == 0)
		onCurrentIndexChanged(QModelIndex(), QModelIndex());
}


void SVDBZoneTemplateEditDialog::onCurrentIndexChanged(const QModelIndex &current, const QModelIndex & /*previous*/) {
	// if there is no selection, deactivate all buttons that need a selection
	if (!current.isValid()) {
		m_ui->pushButtonSelect->setEnabled(false);
		m_ui->toolButtonRemove->setEnabled(false);
		m_ui->toolButtonCopy->setEnabled(false);
		m_groupBox->setEnabled(false);
		m_editWidget->updateInput(-1, -1, 0); // nothing selected
	}
	else {
		m_groupBox->setEnabled(true);
		m_ui->pushButtonSelect->setEnabled(true);
		// remove is not allowed for built-ins
		QModelIndex sourceIndex = m_proxyModel->mapToSource(current);
		m_ui->toolButtonRemove->setEnabled(!sourceIndex.data(Role_BuiltIn).toBool());

		m_ui->toolButtonCopy->setEnabled(true);
		m_ui->treeView->setCurrentIndex(current);
		// retrieve current ID
		int id = sourceIndex.data(Role_Id).toInt();
		int subTemplateID = -1;
		int subTemplateType = 0;
		// sub-template selected?
		if (sourceIndex.internalPointer() != nullptr) {
			subTemplateID = id;
			QModelIndex parentIndex = sourceIndex.parent();
			id = parentIndex.data(Role_Id).toInt();
			subTemplateType = sourceIndex.data(Qt::UserRole + 20).toInt();
		}
		m_editWidget->updateInput(id, subTemplateID, subTemplateType);
	}
}


void SVDBZoneTemplateEditDialog::on_pushButtonReloadUserDB_clicked() {
	if (QMessageBox::question(this, QString(), tr("Reloading the user database from file will revert all changes "
												  "made in this dialog since the program was started. Continue?"),
							  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		// tell db to drop all user-defined items and re-read the DB
		SVSettings::instance().m_db.m_materials.removeUserElements();
		SVSettings::instance().m_db.readDatabases(SVDatabase::DT_ZoneTemplates);
		// tell model to reset completely
		m_dbModel->resetModel();
		onCurrentIndexChanged(QModelIndex(), QModelIndex());
		m_ui->treeView->expandAll();
		m_editWidget->updateInput(-1, -1, 0);
	}
}


void SVDBZoneTemplateEditDialog::selectItemById(unsigned int id) {
	// select top-level item with given id
	for (int i=0, count = m_dbModel->rowCount(); i<count; ++i) {
		QModelIndex sourceIndex = m_dbModel->index(i,0, QModelIndex());
		if (m_dbModel->data(sourceIndex, Role_Id).toUInt() == id) {
			// get proxy index
			QModelIndex proxyIndex = m_proxyModel->mapFromSource(sourceIndex);
			if (proxyIndex.isValid()) {
				m_ui->treeView->blockSignals(true);
				m_ui->treeView->setCurrentIndex(proxyIndex);
				m_ui->treeView->blockSignals(false);
			}
			break;
		}
	}
}


void SVDBZoneTemplateEditDialog::on_treeView_doubleClicked(const QModelIndex &index) {
	if (m_ui->pushButtonSelect->isVisible() && index.isValid()) {
		QModelIndex sourceIndex = m_proxyModel->mapToSource(index);
		if (sourceIndex.internalPointer() == nullptr)
			accept();
	}
}


void SVDBZoneTemplateEditDialog::onSelectSubTemplate(unsigned int zoneTemplateID, int subTemplateType) {
	// if subTemplateType is NUM_ST, select only the top item
	if (subTemplateType == VICUS::ZoneTemplate::NUM_ST) {
		selectItemById((unsigned int)zoneTemplateID);
		m_editWidget->updateInput((int)zoneTemplateID, -1, 0);
	}
	else {
		// first find the zone template index, then search its children for matching subTemplateType
		for (int i=0, count = m_dbModel->rowCount(); i<count; ++i) {
			QModelIndex sourceIndex = m_dbModel->index(i,0, QModelIndex());
			if (sourceIndex.data(Role_Id).toUInt() == zoneTemplateID) {
				// now loop over all children and pick the one with the correct subTemplateType
				for (int j=0, count = m_dbModel->rowCount(sourceIndex); j<count; ++j) {
					QModelIndex subTemplateSourceIndex = m_dbModel->index(j,0,sourceIndex);
					if (subTemplateSourceIndex.data(Qt::UserRole + 20).toInt() == subTemplateType) {
						QModelIndex proxyIndex = m_proxyModel->mapFromSource(subTemplateSourceIndex);
						if (proxyIndex.isValid()) {
							m_ui->treeView->blockSignals(true);
							m_ui->treeView->setCurrentIndex(proxyIndex);
							m_ui->treeView->blockSignals(false);
						}
						m_editWidget->updateInput((int)zoneTemplateID, subTemplateSourceIndex.data(Role_Id).toInt(), subTemplateType);
						return;
					}
				}

			}
		}

	}

}
