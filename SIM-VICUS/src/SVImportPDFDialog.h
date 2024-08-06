#ifndef SVIMPORTPDFDIALOG_H
#define SVIMPORTPDFDIALOG_H

#include <QDialog>

namespace Ui {
class SVImportPDFDialog;
}

class QAbstractButton;
class SVImportPDFDialogGraphicsView;

class SVImportPDFDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SVImportPDFDialog(QWidget *parent = nullptr);
	~SVImportPDFDialog();

	/*! opens a QFileDialog then a QDialog to choose a file and specify the height and width of the file in m.
	Check if import was successful. The image and scale can be requested by their respective getters */
	bool import();

	/*! Resulting image */
	QImage image(){ return m_image; }

	/*! Resulting scale. Calculated by userSpecifiedDistance / pixelDistance */
	float scale(){ return m_scale; }

private slots:
	/*! gets called when SVImportPDFDialogGraphicsView emits pointCountChanged
	 *  usually thrown when the user clicks in the scene */
	void on_pointCountChanged(int numberOfPointsInScene);

	/*! triggered when lineEdit in QtExt::BrowseFilenameWidget is changed */
	void filenameChanged();

	void on_lineEditDistance_textChanged(const QString &arg1);

	/*! disables the other radioButton and it's widget */
	void on_radioButtonTwoPoints_clicked(bool checked);

	/*! disables the other radioButton and it's widget */
	void on_radioButtonDocument_clicked(bool checked);

	void on_lineEditWidth_textChanged(const QString &arg1);

	void on_lineEditHeight_textChanged(const QString &arg1);

	/*! applies the value to m_dpi */
	void on_spinBoxDPI_valueChanged(int arg1);

	/*! applies DPI changes. Uses ImageMagick again to reload the file with increased DPI */
	void on_toolButtonApplyDpi_clicked();

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	Ui::SVImportPDFDialog *m_ui;

	/* resets or initialises the UI, attempts to load the file */
	bool loadDocumentAndInitialize(const QString& fname);

	void changeTwoPointMode(bool twoPointMode);

	void updateAcceptButton();

	/*! Calls ImageMagick via QProcess. Stores the converted image in a temporary directory
	 * QImage then loads that image */
	QImage loadFileWithImageMagick(const QString& fname);

	bool				m_twoPointMode = false;

	bool				m_dpiAdjustable = false;

	int					m_dpi = 100;

	int					m_heightPx = 0;

	int					m_widthPx = 0;

	double				m_aspectRatio = 0;

	float				m_scale = 1;

	QImage				m_image;

};

#endif // SVIMPORTPDFDIALOG_H
