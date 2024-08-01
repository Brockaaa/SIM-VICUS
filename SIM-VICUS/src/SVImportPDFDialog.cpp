#include "SVImportPDFDialog.h"
#include "ui_SVImportPDFDialog.h"

#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QImageReader>
#include <QScreen>
#include <QProcess>
#include <QKeyEvent>

#include "SVSettings.h"

#include "SVImportPDFDialogGraphicsView.h"

SVImportPDFDialog::SVImportPDFDialog(QWidget *parent)
	: QDialog(parent)
	, m_ui(new Ui::SVImportPDFDialog)
{
	m_ui->setupUi(this);
	connect(m_ui->graphicsView, &SVImportPDFDialogGraphicsView::pointCountChanged, this, &SVImportPDFDialog::on_pointCountChanged);
}

SVImportPDFDialog::~SVImportPDFDialog()
{
	delete m_ui;
}

bool SVImportPDFDialog::import()
{

	QString fname = QFileDialog::getOpenFileName(
		this,
		tr("Select File to open"),
		"/home/sandisk/SHK",
		tr("Image or PDF files (*.pdf *.png *.xpm *.jpg *.jpeg);;All files (*.*)"), nullptr,
		SVSettings::instance().m_dontUseNativeDialogs ? QFileDialog::DontUseNativeDialog : QFileDialog::Options()
		);

	if(loadDocumentAndInitialize(fname)) {
		int res = this->exec();
		return res == QDialog::Accepted ? true : false;
	} else {
		return false;
	}
}

float SVImportPDFDialog::scale() {
	return m_ui->graphicsView->scaling();
}

void SVImportPDFDialog::changeTwoPointMode()
{

	m_twoPointMode = !m_twoPointMode;

	if(m_twoPointMode){
		m_ui->labelInstructUser->setText(tr("Select Two Points and specify distance between them"));
		m_ui->lineEditHeight->clear();
		m_ui->lineEditWidth->clear();
	} else {
		m_ui->labelInstructUser->setText(tr("Specify either Height or Width of the document"));
		m_ui->lineEditDistance->clear();
		m_ui->lineEditHeight->clear();
		m_ui->lineEditWidth->clear();
	}

	m_ui->groupBoxDocument->setChecked(!m_twoPointMode);
	m_ui->groupBoxTwoPoints->setChecked(m_twoPointMode);

	m_ui->graphicsView->setTwoPointMode(m_twoPointMode);
}


void SVImportPDFDialog::on_groupBoxDocument_clicked(bool checked)
{
	changeTwoPointMode();
}


void SVImportPDFDialog::on_groupBoxTwoPoints_clicked(bool checked)
{
	changeTwoPointMode();
}

void SVImportPDFDialog::on_pointCountChanged(int numberOfPointsInScene)
{
	m_ui->lineEditDistance->setEnabled(numberOfPointsInScene == 2);
}

void SVImportPDFDialog::on_lineEditDistance_editingFinishedSuccessfully()
{
	m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}


void SVImportPDFDialog::on_lineEditWidth_editingFinishedSuccessfully()
{
	double width = m_ui->lineEditWidth->text().toDouble();
	m_scale = width / m_widthPx;
	m_ui->lineEditHeight->setValue(m_scale * m_heightPx);
}


void SVImportPDFDialog::on_lineEditHeight_editingFinishedSuccessfully()
{
	double height = m_ui->lineEditHeight->text().toDouble();
	m_scale = height / m_heightPx;
	m_ui->lineEditWidth->setValue(m_scale * m_widthPx);
}


void SVImportPDFDialog::on_toolButtonLoad_clicked()
{
	QString fname = QFileDialog::getOpenFileName(
		this,
		tr("Select File to open"),
		"/home/sandisk/SHK",
		tr("Image or PDF files (*.pdf *.png *.xpm *.jpg *.jpeg);;All files (*.*)"), nullptr,
		SVSettings::instance().m_dontUseNativeDialogs ? QFileDialog::DontUseNativeDialog : QFileDialog::Options()
		);

	loadDocumentAndInitialize(fname);
}

void SVImportPDFDialog::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Return)
		event->accept();
}

bool SVImportPDFDialog::loadDocumentAndInitialize(QString & fname)
{
	QFile imageFile(fname);
	if(!QFile::exists(fname))
	{
		QMessageBox::critical(nullptr, "Failed to Load", QString("The requested file %1 could not be loaded.").arg(fname));
		return false;
	}

	QImage newImage;
	QImageReader reader(fname);
	if(reader.canRead()) {
		newImage = reader.read();
	}

	QList<QByteArray> formats = QImageReader::supportedImageFormats();
	qDebug() << "Supported image formats:";
	for (const QByteArray &format : formats) {
		qDebug() << format;
	}

	// if given file is an image and can be loaded by QImage, proceed with it
	// else try to use ImageMagick to convert a pdf to a QImage and proceed
	// pngs dont reliably work under linux: "libpng error: unexpected end of LZ stream"
	if(newImage.isNull()){
		QProcess process;
		process.setWorkingDirectory("/home/sandisk/Downloads");
		QString binary = "magick";
		QString tempConvertedImage = "/home/sandisk/SHK/convertedImage.jpeg";
		QStringList arguments;
		arguments << "convert" << (fname + "[0]") << tempConvertedImage;
		process.start(binary, arguments);

		if (!process.waitForFinished()) {
			qDebug() << "Error:" << process.errorString();
			QMessageBox::critical(nullptr, "Failed to Load", QString("The requested file %1 could not be loaded.").arg(fname));
			return false;
		}

		newImage.load(tempConvertedImage);
	}

	if(newImage.isNull()){
		QMessageBox::critical(nullptr, "Failed to Load", QString("The requested file %1 could not be loaded.").arg(fname));
		return false;
	}

	// resetting values to default after image was able to be loaded
	m_twoPointMode = false;
	changeTwoPointMode();
	on_pointCountChanged(0);

	m_image = newImage;
	m_heightPx = m_widthPx = m_aspectRatio = 0;
	m_ui->lineEditDistance->clear();
	m_ui->lineEditWidth->clear();
	m_ui->lineEditHeight->clear();

	// Resize view to maintain aspect ratio

	m_widthPx = m_image.width();
	m_heightPx = m_image.height();

	m_aspectRatio = (double)m_widthPx / (double)m_heightPx;

	int newWidth, newHeight;

	// Check if the new height exceeds the screen height
	QScreen* screen = QGuiApplication::primaryScreen();
	int maxHeight = screen->availableGeometry().height() * 0.8; // 80% of screen height
	int maxWidth = screen ->availableGeometry().width() * 0.8;

	newHeight = maxHeight;
	newWidth = static_cast<int>(newHeight * m_aspectRatio);

	if(newWidth > maxWidth){
		newWidth = maxWidth;
		newHeight = static_cast<int>(newWidth * m_aspectRatio);
	}

	// Resize the view
	m_ui->graphicsView->setFixedSize(newWidth, newHeight);

	adjustSize();

	m_ui->graphicsView->setImage(m_image);
	return true;
}

QString SVImportPDFDialog::openDocument()
{

	QString fname = QFileDialog::getOpenFileName(
		this,
		tr("Select File to open"),
		"/home/sandisk/SHK",
		tr("Image or PDF files (*.pdf *.png *.xpm *.jpg *.jpeg);;All files (*.*)"), nullptr,
		SVSettings::instance().m_dontUseNativeDialogs ? QFileDialog::DontUseNativeDialog : QFileDialog::Options()
		);


	return fname;
}

