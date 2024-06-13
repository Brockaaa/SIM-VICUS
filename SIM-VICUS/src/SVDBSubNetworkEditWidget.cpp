#include "SVDBSubNetworkEditWidget.h"
#include "ui_SVDBSubNetworkEditWidget.h"

#include "SVDBSubNetworkTableModel.h"
#include "SVStyle.h"
#include "SVMainWindow.h"
#include "SVDatabaseEditDialog.h"
#include "SVSubNetworkEditDialog.h"
#include "SVProjectHandler.h"
#include "SVConstants.h"
#include "SVConversions.h"

#include <QFileInfo>

#include <QtExt_Directories.h>
#include <QtExt_LanguageHandler.h>

#include <VICUS_KeywordList.h>
#include <VICUS_utilities.h>


SVDBSubNetworkEditWidget::SVDBSubNetworkEditWidget(QWidget *parent) :
	SVAbstractDatabaseEditWidget(parent),
	m_ui(new Ui::SVDBSubNetworkEditWidget)
{
	m_ui->setupUi(this);

	//set background color of frame to white
	m_ui->previewFrame->setFrameShape(QFrame::Box);
	// no padding or margins
	m_ui->previewFrame->setStyleSheet("QFrame { background-color: white; border: 0px; padding: 0px; margin: 0px; }");
	connect(m_ui->widgetHoverToSelect, &QtExt_SubNetworkHoverToSelect::thumbNailClicked, this, &SVDBSubNetworkEditWidget::on_ThumbNailClicked);

	m_ui->lineEditSubNetworkName->initLanguages(QtExt::LanguageHandler::instance().langId().toStdString(), THIRD_LANGUAGE, true);
	m_ui->lineEditSubNetworkName->setDialog3Caption(tr("Sub network name"));

}

SVDBSubNetworkEditWidget::~SVDBSubNetworkEditWidget() {
	delete m_ui;
}

void SVDBSubNetworkEditWidget::setup(SVDatabase *db, SVAbstractDatabaseTableModel *dbModel) {
	m_db = db;
	m_dbModel = dynamic_cast<SVDBSubNetworkTableModel*>(dbModel);
}


void SVDBSubNetworkEditWidget::updateInput(int id) {
	m_currentSubNet = nullptr; // disable edit triggers

	if (id == -1) {
		// disable all controls - note: this does not disable signals of the components below
		setEnabled(false);

		// clear input controls
		m_ui->lineEditSubNetworkName->setText(QString());

		// remove any QPixmap in the Subnetwork preview label
		m_ui->widgetHoverToSelect->setThumbnail(QPixmap());

		// Note: color button is disabled, hence color is gray
		return;
	}

	// re-enable all controls
	setEnabled(true);

	// get current sub network
	m_currentSubNet = const_cast<VICUS::SubNetwork*>(m_db->m_subNetworks[(unsigned int)id]);
	Q_ASSERT(m_currentSubNet != nullptr);

	// now update the GUI controls
	m_ui->lineEditSubNetworkName->setString(m_currentSubNet->m_displayName);
	m_ui->pushButtonColor->setColor(m_currentSubNet->m_color);

	updateTableWidget();

	// for built-ins, disable editing/make read-only
	bool isEditable = !m_currentSubNet->m_builtIn;
	m_ui->lineEditSubNetworkName->setReadOnly(!isEditable);
}


void SVDBSubNetworkEditWidget::modelModify() {
	m_db->m_subNetworks.m_modified = true;
	m_dbModel->setItemModified(m_currentSubNet->m_id);
}


void SVDBSubNetworkEditWidget::updateTableWidget() {

	if (m_currentSubNet == nullptr)
		return;

	QString thumbName = SVProjectHandler::instance().projectFile();
	thumbName.replace("/", "_");
	thumbName.replace("\\", "_");
	thumbName.replace(":", "_");

	QString thumbNameWithTilde = "~SN" + thumbName + QString("#") +  QString::number(m_currentSubNet->m_id) + ".png";
	QString iconPath = QtExt::Directories::userDataDir()  + "/thumbs/subnetworks/" + thumbNameWithTilde;

	qDebug() << "iconPath: " << iconPath;
	QFileInfo thumbFileInfo(iconPath);
	if (!thumbFileInfo.exists()){
		QString thumbNameWithoutTilde = thumbNameWithTilde.remove(0,1);
		iconPath = QtExt::Directories::userDataDir()  + "/thumbs/subnetworks/" + thumbNameWithoutTilde;
		thumbFileInfo.setFile(iconPath);
	}
	if (!thumbFileInfo.exists()){
		iconPath =":/gfx/modeltypeicons/defaultSplashscreen.png";
	}
	QPixmap pixmap(iconPath);
	if (pixmap.isNull())
		pixmap.load(":/gfx/modeltypeicons/defaultSplashscreen.png");

	pixmap = pixmap.scaled(815, 480, Qt::KeepAspectRatio);

	// Create a label to show the image
	m_ui->widgetHoverToSelect->setThumbnail(pixmap);
}


void SVDBSubNetworkEditWidget::on_lineEditSubNetworkName_editingFinished()
{
	Q_ASSERT(m_currentSubNet != nullptr);
	if (m_currentSubNet->m_displayName != m_ui->lineEditSubNetworkName->string()) {
		m_currentSubNet->m_displayName = m_ui->lineEditSubNetworkName->string();
		modelModify();
	}
	updateInput((int)m_currentSubNet->m_id);
}


void SVDBSubNetworkEditWidget::on_pushButtonColor_clicked()
{
	Q_ASSERT(m_currentSubNet != nullptr);
	if (m_currentSubNet->m_color != m_ui->pushButtonColor->color()) {
		m_currentSubNet->m_color = m_ui->pushButtonColor->color();
		modelModify();
	}
	updateInput((int)m_currentSubNet->m_id);
}

void SVDBSubNetworkEditWidget::on_editSubNetworkButton_clicked()
{
	if(m_editDialog == nullptr){
		m_editDialog = new SVSubNetworkEditDialog(this, m_currentSubNet, m_db);
		m_editDialog->setWindowFlag(Qt::Window);
	} else {
		m_editDialog->setupSubNetwork(m_currentSubNet);
	}

	connect(m_editDialog, &SVSubNetworkEditDialog::widgetClosed, this, &SVDBSubNetworkEditWidget::on_subNetworkEditDialog_closed);

	m_editDialog->show();
}

void SVDBSubNetworkEditWidget::on_subNetworkEditDialog_closed()
{
	updateTableWidget();
}

void SVDBSubNetworkEditWidget::on_ThumbNailClicked()
{
	on_editSubNetworkButton_clicked();
}
