#include "SVAbstractDatabaseEditDialog.h"
#include "SVPreferencesDialog.h"
#include "ui_SVAbstractDatabaseEditDialog.h"

#include <QSplitter>
#include <QScreen>

#include "SVStyle.h"
#include "SVPreferencesPageStyle.h"
#include "SVConstants.h"
#include "SVDBModelDelegate.h"
#include "SVMainWindow.h"
#include "SVDatabaseSortFilterProxyModel.h"
#include "SVAbstractDatabaseEditWidget.h"
#include "SVViewStateHandler.h"

SVAbstractDatabaseEditDialog::SVAbstractDatabaseEditDialog(QWidget *parent, SVAbstractDatabaseTableModel * tableModel,
														   SVAbstractDatabaseEditWidget * editWidget,
														   const QString & title, const QString & editWidgetTitle,
														   bool horizontalLayout)
	: 	QDialog(parent
#ifdef Q_OS_LINUX
			  , Qt::Window | Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint /*| Qt::WindowSystemMenuHint*/
#endif
			  ),
	m_ui(new Ui::SVAbstractDatabaseEditDialog),
	m_dbModel(tableModel),
	m_editWidget(editWidget)
{
	m_ui->setupUi(this);
	m_ui->gridLayoutTableView->setMargin(4);

	setWindowTitle(title);

	// set initial screen size
	QScreen *screen = QGuiApplication::primaryScreen();
	Q_ASSERT(screen!=nullptr);
	m_screenSize = screen->size();

	SVStyle::formatDatabaseTableView(m_ui->tableView);
	m_ui->tableView->horizontalHeader()->setVisible(true);

	m_proxyModel = new SVDatabaseSortFilterProxyModel(this);
	m_proxyModel->setSourceModel(dynamic_cast<QAbstractTableModel*>(m_dbModel));
	m_ui->tableView->setModel(m_proxyModel);

	// create groupbox and adjust layout for edit widget
	if (!editWidgetTitle.isEmpty()) {
		QGroupBox * groupBox = new QGroupBox(this);
		groupBox->setTitle(editWidgetTitle);
		m_editWidgetContainerWidget = groupBox;
	}
	else {
		QWidget * wg = new QWidget(this);
		m_editWidgetContainerWidget = wg;
	}

	// splitter contains group box and custom edit widget
	QSplitter * split = new QSplitter(this);
	split->setOrientation(horizontalLayout ? Qt::Horizontal : Qt::Vertical);
	split->addWidget(m_ui->groupBoxTableView);
	split->addWidget(m_editWidgetContainerWidget);
	split->setCollapsible(0, false);
	split->setCollapsible(1, false);
	m_ui->verticalLayout->insertWidget(0, split);

	QVBoxLayout * verticalLay = new QVBoxLayout(m_editWidgetContainerWidget);
	verticalLay->addWidget(editWidget);
	m_editWidgetContainerWidget->setLayout(verticalLay);
	verticalLay->setMargin(0);
	editWidget->setup(&SVSettings::instance().m_db, m_dbModel);

	// specific setup for DB table view
	m_dbModel->setColumnResizeModes(m_ui->tableView);

	connect(m_ui->tableView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
			this, SLOT(onCurrentIndexChanged(const QModelIndex &, const QModelIndex &)) );

	// set item delegate for coloring built-ins
	SVDBModelDelegate * dg = new SVDBModelDelegate(this, Role_BuiltIn, Role_Local, Role_Referenced);
	m_ui->tableView->setItemDelegate(dg);

	m_ui->tableView->installEventFilter(this);

	// modify frames and update colors
	m_ui->frameBuildInDB->setFrameShape(QFrame::NoFrame);
	m_ui->frameUserDB->setFrameShape(QFrame::NoFrame);
	// this update colors of frames but also the table view selection color
	onStyleChanged();

	for (int i=0; i<m_dbModel->columnCount(); ++i){
		QString name = m_dbModel->headerData(i, Qt::Horizontal).toString();
		if (name == "") continue; // Skip valid column
		m_ui->comboBoxColumn->addItem(name, i);
	}

	connect(SVMainWindow::instance().preferencesDialog()->pageStyle(), &SVPreferencesPageStyle::styleChanged, this, &SVAbstractDatabaseEditDialog::onStyleChanged);
}

SVAbstractDatabaseEditDialog::~SVAbstractDatabaseEditDialog()
{
	delete m_ui;
}

void SVAbstractDatabaseEditDialog::edit(unsigned int initialId)
{
	// hide select/cancel buttons, and show "close" button
	m_ui->pushButtonClose->setVisible(true);
	m_ui->pushButtonSelect->setVisible(false);
	m_ui->pushButtonCancel->setVisible(false);

	// ask database model to update its content
	m_dbModel->resetModel(); // ensure we use up-to-date data (in case the database data has changed elsewhere)
	selectItemById(initialId);
	onCurrentIndexChanged(m_ui->tableView->currentIndex(), QModelIndex()); // select nothing

	m_ui->tableView->resizeColumnsToContents();

	// update "isRferenced" property of all elements
	if (SVProjectHandler::instance().isValid()){
		SVSettings::instance().m_db.updateReferencedElements(project());
	}

	exec();
	QTimer::singleShot(0, &SVViewStateHandler::instance(), &SVViewStateHandler::refreshColors);
}

unsigned int SVAbstractDatabaseEditDialog::select(unsigned int initialId, bool resetModel, QString filterText, int filterColumn)
{
	m_ui->pushButtonClose->setVisible(false);
	m_ui->pushButtonSelect->setVisible(true);
	m_ui->pushButtonCancel->setVisible(true);

	if(resetModel)
		m_dbModel->resetModel(); // ensure we use up-to-date data (in case the database data has changed elsewhere)
	selectItemById(initialId);
	onCurrentIndexChanged(m_ui->tableView->currentIndex(), QModelIndex()); // select nothing

	m_ui->tableView->resizeColumnsToContents();

	m_proxyModel->setPersistentFilter(filterText, filterColumn);

	if(filterColumn > 1 && !filterText.isEmpty()) {
		m_currentFilter = filterText;
		m_proxyModel->setFilterKeyColumn(filterColumn);
		m_proxyModel->setFilterWildcard(filterText);
	}

	// update "isRferenced" property of all elements
	if (SVProjectHandler::instance().isValid()){
		SVSettings::instance().m_db.updateReferencedElements(project());
	}

	int res = exec();
	QTimer::singleShot(0, &SVViewStateHandler::instance(), &SVViewStateHandler::refreshColors);
	if (res == QDialog::Accepted) {

		// determine current item
		QModelIndex currentProxyIndex = m_ui->tableView->currentIndex();
		Q_ASSERT(currentProxyIndex.isValid());
		QModelIndex sourceIndex = m_proxyModel->mapToSource(currentProxyIndex);

		// return ID
		return sourceIndex.data(Role_Id).toUInt();
	}

	m_proxyModel->setFilterWildcard("");
	m_currentFilter = ""; // Reset filter

	// nothing selected/dialog aborted
	return initialId;
}

void SVAbstractDatabaseEditDialog::on_pushButtonSelect_clicked()
{
	accept();
}

void SVAbstractDatabaseEditDialog::on_pushButtonCancel_clicked()
{
	reject();
}

void SVAbstractDatabaseEditDialog::on_pushButtonClose_clicked()
{
	accept();
}

void SVAbstractDatabaseEditDialog::onCurrentIndexChanged(const QModelIndex & current, const QModelIndex &)
{
	// retrieve current ID
	int id = current.data(Role_Id).toInt();
	m_editWidget->updateInput(id);
}

void SVAbstractDatabaseEditDialog::onStyleChanged() {
	m_ui->frameBuildInDB->setStyleSheet(QString(".QFrame { background-color: %1; }").arg(SVStyle::instance().m_alternativeBackgroundBright.name()));
	m_ui->frameUserDB->setStyleSheet(QString(".QFrame { background-color: %1; }").arg(SVStyle::instance().m_userDBBackgroundBright.name()));
}

void SVAbstractDatabaseEditDialog::on_toolButtonApplyFilter_clicked()
{
	QString filter = m_ui->lineEditFilter->text();

	// Filter Column
	int filterCol = m_ui->comboBoxColumn->currentData().toInt();

	// Set filter
	m_proxyModel->setFilterWildcard(filter);
	m_proxyModel->setFilterKeyColumn(filterCol);
	m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void SVAbstractDatabaseEditDialog::on_comboBoxColumn_currentIndexChanged(int)
{
	m_proxyModel->setFilterWildcard("");
}

void SVAbstractDatabaseEditDialog::on_lineEditFilter_returnPressed()
{
	on_toolButtonApplyFilter_clicked();
}

void SVAbstractDatabaseEditDialog::onScreenChanged(const QScreen * screen)
{
	m_screenSize = screen->size();
}

void SVAbstractDatabaseEditDialog::selectItemById(unsigned int id) {
	// select item with given id
	for (int i=0, count = m_dbModel->rowCount(); i<count; ++i) {
		QModelIndex sourceIndex = m_dbModel->index(i,0);
		if (m_dbModel->data(sourceIndex, Role_Id).toUInt() == id) {
			// get proxy index
			QModelIndex proxyIndex = m_proxyModel->mapFromSource(sourceIndex);
			if (proxyIndex.isValid()) {
				m_ui->tableView->blockSignals(true);
				m_ui->tableView->setCurrentIndex(proxyIndex);
				m_ui->tableView->blockSignals(false);
			}
			break;
		}
	}
}

void SVAbstractDatabaseEditDialog::resizeDBDialog(double maxShareTableView)
{
	// set dialog size
	this->resize(int(0.8*m_screenSize.width()), int(0.8*m_screenSize.height()));
	// set max share that is occupied by table view
	double w = this->size().width();
	m_ui->groupBoxTableView->setMaximumWidth(int(w*maxShareTableView));
}
