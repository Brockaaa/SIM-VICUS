#include "SVImportPDFDialog.h"
#include "ui_SVImportPDFDialog.h"

#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QImageReader>
#include <QScreen>

#include "SVSettings.h"

#include "SVImportPDFDialogGraphicsView.h"

#include <QProcess>

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
	m_twoPointMode = false;
	changeTwoPointMode();
	on_pointCountChanged(0);
	m_image = QImage();
	m_heightPx = m_widthPx = 0;

	QString fname = QFileDialog::getOpenFileName(
		this,
		tr("Select File to open"),
		"/home/sandisk/SHK",
		tr("Image or PDF files (*.pdf *.png *.xpm *.jpg *.jpeg);;All files (*.*)"), nullptr,
		SVSettings::instance().m_dontUseNativeDialogs ? QFileDialog::DontUseNativeDialog : QFileDialog::Options()
		);

	QFile imageFile(fname);
	if(!QFile::exists(fname))
	{
		QMessageBox::critical(nullptr, "Failed to Load", QString("The requested file %1 could not be loaded.").arg(fname));
		return false;
	}

	QImageReader reader(fname);
	if(reader.canRead()) {
		m_image = reader.read();
	}

	QList<QByteArray> formats = QImageReader::supportedImageFormats();
	qDebug() << "Supported image formats:";
	for (const QByteArray &format : formats) {
		qDebug() << format;
	}

	// if given file is an image and can be loaded by QImage, proceed with it
	// else try to use ImageMagick to convert a pdf to a QImage and proceed
	// pngs dont reliably work under linux: "libpng error: unexpected end of LZ stream"
	if(m_image.isNull()){
		//image = m_image;
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

		// Read the output
		// QString output = QString::fromUtf8(process.readAllStandardOutput());
		// QString errorOutput = QString::fromUtf8(process.readAllStandardError());

		m_image.load(tempConvertedImage);
	}

	if(m_image.isNull()){
		QMessageBox::critical(nullptr, "Failed to Load", QString("The requested file %1 could not be loaded.").arg(fname));
		return false;
	}


	// Resize view to maintain aspect ratio

	int imageWidth = m_image.width();
	int imageHeight = m_image.height();

	double aspectRatio = (double)imageWidth / (double)imageHeight;

	int newWidth, newHeight;

	// Check if the new height exceeds the screen height
	QScreen* screen = QGuiApplication::primaryScreen();
	int maxHeight = screen->availableGeometry().height() * 0.8; // 80% of screen height
	int maxWidth = screen ->availableGeometry().width() * 0.8;

	newHeight = maxHeight;
	newWidth = static_cast<int>(newHeight * aspectRatio);

	if(newWidth > maxWidth){
		newWidth = maxWidth;
		newHeight = static_cast<int>(newWidth * aspectRatio);
	}

	// Resize the view
	qDebug() << "NewWidth: " << newWidth << "NewHeight: " << newHeight;
	m_ui->graphicsView->setFixedSize(newWidth, newHeight);

	adjustSize();

	m_ui->graphicsView->setImage(m_image);

	int res = this->exec();

	return res == QDialog::Accepted ? true : false;
}

float SVImportPDFDialog::scale() {
	return m_ui->graphicsView->scaling();
}

void SVImportPDFDialog::changeTwoPointMode()
{
	m_ui->labelInstructUser->setText(tr("Select Two Points and specify distance between them"));
	m_twoPointMode = !m_twoPointMode;

	if(!m_twoPointMode)
		m_ui->lineEditDistance->clear();

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

}


void SVImportPDFDialog::on_lineEditHeight_editingFinishedSuccessfully()
{

}

