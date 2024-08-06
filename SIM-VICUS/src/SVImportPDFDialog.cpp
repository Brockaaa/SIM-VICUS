#include "SVImportPDFDialog.h"
#include "ui_SVImportPDFDialog.h"

#include <QFileDialog>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QProgressDialog>
#include <QImageReader>
#include <QScreen>
#include <QProcess>
#include <QKeyEvent>
#include <QtExt_ValidatingLineEdit.h>

#include "SVSettings.h"

#include "SVImportPDFDialogGraphicsView.h"

SVImportPDFDialog::SVImportPDFDialog(QWidget *parent)
	: QDialog(parent)
	, m_ui(new Ui::SVImportPDFDialog)
{
	m_ui->setupUi(this);
	connect(m_ui->graphicsView, &SVImportPDFDialogGraphicsView::pointCountChanged, this, &SVImportPDFDialog::on_pointCountChanged);
	m_ui->lineEditWidth->setFormat('f', 3);
	m_ui->lineEditHeight->setFormat('f', 3);
	m_ui->lineEditWidth->setMinimum(0, false);
	m_ui->lineEditHeight->setMinimum(0, false);

	connect(m_ui->widgetBrowseFilename, &QtExt::BrowseFilenameWidget::editingFinished, this, &SVImportPDFDialog::filenameChanged);
}

SVImportPDFDialog::~SVImportPDFDialog()
{
	delete m_ui;
}

bool SVImportPDFDialog::import() {

	QString fname = QFileDialog::getOpenFileName(
		this,
		tr("Select File to open"),
		"/home/sandisk/SHK",
		tr("Image or PDF files (*.pdf *.bmp *.gif *.jpeg *.jpg *.png *.svg *.tif *.tiff *.webp);;All files (*.*)"), nullptr,
		SVSettings::instance().m_dontUseNativeDialogs ? QFileDialog::DontUseNativeDialog : QFileDialog::Options()
		);

	if (loadDocumentAndInitialize(fname)) {
		m_ui->widgetBrowseFilename->setup(fname, true, true, tr("Image or PDF files (*.pdf *.bmp *.gif *.jpeg *.jpg *.png *.svg *.tif *.tiff *.webp);;All files (*.*)"), true);
		int res = this->exec();
		return res == QDialog::Accepted ? true : false;
	} else {
		return false;
	}
}

void SVImportPDFDialog::changeTwoPointMode(bool checked) {

	m_twoPointMode = checked;

	m_ui->radioButtonTwoPoints->blockSignals(true);
	m_ui->radioButtonDocument->blockSignals(true);

	m_ui->radioButtonTwoPoints->setChecked(m_twoPointMode);
	m_ui->radioButtonDocument->setChecked(!m_twoPointMode);

	m_ui->radioButtonTwoPoints->blockSignals(false);
	m_ui->radioButtonDocument->blockSignals(false);

	QtExt::ValidatingLineEdit* lEDistance = m_ui->lineEditDistance;
	QtExt::ValidatingLineEdit* lEHeight = m_ui->lineEditHeight;
	QtExt::ValidatingLineEdit* lEWidth = m_ui->lineEditWidth;

	if (m_twoPointMode) {
		m_ui->labelInstructUser->setText(tr("Select Two Points and specify distance between them"));

		m_ui->lineEditHeight->blockSignals(true);
		m_ui->lineEditHeight->clear();
		m_ui->lineEditHeight->blockSignals(false);

		m_ui->lineEditWidth->blockSignals(true);
		m_ui->lineEditWidth->clear();
		m_ui->lineEditWidth->blockSignals(false);

		m_ui->widgetTwoPoints->setEnabled(true);
		m_ui->widgetDocument->setEnabled(false);
		m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	} else {
		m_ui->labelInstructUser->setText(tr("Specify either Height or Width of the document"));

		m_ui->lineEditDistance->blockSignals(true);
		m_ui->lineEditDistance->clear();
		m_ui->lineEditDistance->blockSignals(false);

		m_ui->widgetTwoPoints->setEnabled(false);
		m_ui->widgetDocument->setEnabled(true);
	}

	m_ui->graphicsView->setTwoPointMode(m_twoPointMode);
}

void SVImportPDFDialog::on_pointCountChanged(int numberOfPointsInScene) {
	bool equals2 = numberOfPointsInScene == 2;
	m_ui->lineEditDistance->setEnabled(equals2);
	if (!equals2) {
		m_ui->lineEditDistance->blockSignals(true);
		m_ui->lineEditDistance->clear();
		m_ui->lineEditDistance->blockSignals(false);
	}
}

void SVImportPDFDialog::filenameChanged() {
	QString fname = m_ui->widgetBrowseFilename->filename();
	if (!fname.isEmpty()) {
		if (!loadDocumentAndInitialize(fname))
			QMessageBox::critical(nullptr, "Failed to Load", QString("The requested file %1 could not be loaded.").arg(fname));
		resize(200, 200);
	}
}

void SVImportPDFDialog::keyPressEvent(QKeyEvent * event) {
	if (event->key() == Qt::Key_Return)
		event->accept();
}

bool SVImportPDFDialog::loadDocumentAndInitialize(const QString & fname) {
	m_dpiAdjustable = false;

	QFile imageFile(fname);
	if (!QFile::exists(fname)) {
		QMessageBox::critical(nullptr, "Failed to Load", QString("The requested file %1 could not be loaded.").arg(fname));
		return false;
	}

	QImage newImage;
	QImageReader reader(fname);
	if (reader.canRead()) {
		newImage = reader.read();
	}

	// if given file is an image and can be loaded by QImage, proceed with it
	// else try to use ImageMagick to convert a pdf to a QImage and proceed
	// pngs dont reliably work under linux: "libpng error: unexpected end of LZ stream"
	if (newImage.isNull()) {
		newImage = loadFileWithImageMagick(fname);
	}

	// if newImage is null, neither QImage nor ImageMagick were able to load the document
	if (newImage.isNull()) {
		QMessageBox::critical(nullptr, "Failed to Load", QString("The requested file %1 could not be loaded.").arg(fname));
		return false;
	} else {
		// if image is loaded this time, it is loaded via ImageMagick and DPI can be adjusted
		m_dpiAdjustable = true;
	}

	// resetting values to default after image was able to be loaded
	changeTwoPointMode(true);
	on_pointCountChanged(0);
	m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	m_ui->spinBoxDPI->blockSignals(true);
	m_ui->spinBoxDPI->setValue(m_dpi);
	m_ui->spinBoxDPI->blockSignals(false);
	m_ui->widgetDPIAdjustable->setVisible(m_dpiAdjustable);

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

	if (newWidth > maxWidth) {
		newWidth = maxWidth;
		newHeight = static_cast<int>(newWidth * m_aspectRatio);
	}

	// Resize the view
	m_ui->graphicsView->setFixedSize(newWidth, newHeight);

	adjustSize();

	m_ui->graphicsView->setImage(m_image);
	return true;
}

void SVImportPDFDialog::updateAcceptButton() {
	if (m_twoPointMode) {
		// enable Ok Button when lineEditDistance is filled with valid value
		m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_ui->lineEditDistance->isValid());
	} else {
		m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(m_ui->lineEditWidth->isValid() && m_ui->lineEditHeight->isValid());
	}
}

QImage SVImportPDFDialog::loadFileWithImageMagick(const QString & fname) {
	// create a QProgressDialog. It will not have any buttons. During the loading process, the
	// progress bar will be fixed at 50
	QProgressDialog progress("Converting image...", "Cancel", 0, 100, this);
	progress.setWindowModality(Qt::WindowModal);
	progress.setMinimumDuration(0);
	progress.setValue(0);
	progress.setCancelButton(nullptr);  // to remove the cancel button
	progress.show();

	QProcess process;
	process.setWorkingDirectory("/home/sandisk/Downloads");
	QString binary = "magick";
	QString tempConvertedImage = "/home/sandisk/SHK/convertedImage.jpeg";
	QStringList arguments;
	arguments << "convert"  << "-density" << QString::number(m_dpi) << (fname + "[0]") << tempConvertedImage;

	process.start(binary, arguments);

	while (process.state() != QProcess::NotRunning) {
		QApplication::processEvents();
		progress.setValue(50);
	}

	if (process.exitCode() != 0) {
		qDebug() << "Error:" << process.errorString();
		qDebug() << "Failed to Load" << QString("The requested file %1 could not be loaded.").arg(fname);
		return QImage();
	}

	progress.setValue(100);
	QApplication::processEvents();

	QImage image;
	image.load(tempConvertedImage);
	return image;
}


void SVImportPDFDialog::on_lineEditDistance_textChanged(const QString &arg1) {
	Q_ASSERT(m_ui->graphicsView->m_points.size() == 2);

	QPointF &point0 = m_ui->graphicsView->m_points[0];
	QPointF &point1 = m_ui->graphicsView->m_points[1];

	// calculate euklidian distance
	double powOfSumX = pow(point0.x() - point1.x(), 2);
	double powOfSumY = pow(point0.y() - point1.y(), 2);
	double euclDistance = sqrt(powOfSumX + powOfSumY);

	double distanceUser = m_ui->lineEditDistance->value();
	m_scale = distanceUser / euclDistance;

	m_ui->lineEditHeight->blockSignals(true);
	m_ui->lineEditHeight->setValue(m_scale * m_heightPx);
	m_ui->lineEditHeight->blockSignals(false);

	m_ui->lineEditWidth->blockSignals(true);
	m_ui->lineEditWidth->setValue(m_scale * m_widthPx);
	m_ui->lineEditWidth->blockSignals(false);

	updateAcceptButton();
}


void SVImportPDFDialog::on_radioButtonTwoPoints_clicked(bool checked) {
	changeTwoPointMode(checked);
}


void SVImportPDFDialog::on_radioButtonDocument_clicked(bool checked) {
		changeTwoPointMode(!checked);
}


void SVImportPDFDialog::on_lineEditWidth_textChanged(const QString &arg1) {
	double width = m_ui->lineEditWidth->text().toDouble();
	m_scale = width / m_widthPx;
	m_ui->lineEditHeight->setValue(m_scale * m_heightPx);
	updateAcceptButton();
}


void SVImportPDFDialog::on_lineEditHeight_textChanged(const QString &arg1) {
	double height = m_ui->lineEditHeight->text().toDouble();
	m_scale = height / m_heightPx;
	m_ui->lineEditWidth->setValue(m_scale * m_widthPx);
	updateAcceptButton();
}


void SVImportPDFDialog::on_spinBoxDPI_valueChanged(int arg1) {
	m_dpi = arg1;
}

void SVImportPDFDialog::on_toolButtonApplyDpi_clicked() {
	QString fname = m_ui->widgetBrowseFilename->filename();
	m_image = loadFileWithImageMagick(fname);
	m_ui->graphicsView->m_points.clear();
	on_pointCountChanged(0);
	m_ui->graphicsView->setImage(m_image);
	m_widthPx = m_image.width();
	m_heightPx = m_image.height();
	updateAcceptButton();
}
