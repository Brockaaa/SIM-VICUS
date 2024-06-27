#include "SVImportPDFDialog.h"
#include "ui_SVImportPDFDialog.h"

#include <QFileDialog>
#include <QDebug>
#include <QWebEngineView>

#include "SVSettings.h"

SVImportPDFDialog::SVImportPDFDialog(QWidget *parent)
	: QDialog(parent)
	, m_ui(new Ui::SVImportPDFDialog)
{
	m_ui->setupUi(this);
	openFile();
}

SVImportPDFDialog::~SVImportPDFDialog()
{
	delete m_ui;
}

void SVImportPDFDialog::openFile()
{
	// request IDF file and afterwards open import dialog
	QString fileName = QFileDialog::getOpenFileName(
		this,
		tr("Select PDF file"),
		SVSettings::instance().m_propertyMap[SVSettings::PT_LastImportOpenDirectory].toString(),
		tr("PDF files (*.pdf);;All files (*.*)"), nullptr,
		SVSettings::instance().m_dontUseNativeDialogs ? QFileDialog::DontUseNativeDialog : QFileDialog::Options()
		);

	m_fileName = fileName;
	qDebug() << fileName;

	QUrl url = QUrl::fromLocalFile(m_fileName);

	QWebEngineView* webEngineView = new QWebEngineView(this);
	m_ui->verticalLayout->addWidget(webEngineView);

	if(webEngineView) {
		webEngineView->load(url);
		webEngineView->show();
	}
}
