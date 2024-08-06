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

	bool import();

	QImage image(){ return m_image; }

	float scale();

private slots:
	void on_pointCountChanged(int numberOfPointsInScene);

	void filenameChanged();

	void on_lineEditDistance_textChanged(const QString &arg1);

	void on_radioButtonTwoPoints_clicked(bool checked);

	void on_radioButtonDocument_clicked(bool checked);

	void on_lineEditWidth_textChanged(const QString &arg1);

	void on_lineEditHeight_textChanged(const QString &arg1);

	void on_spinBoxDPI_valueChanged(int arg1);

	void on_toolButtonApplyDpi_clicked();

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	Ui::SVImportPDFDialog *m_ui;

	bool loadDocumentAndInitialize(const QString& fname);

	void changeTwoPointMode(bool twoPointMode);

	void updateAcceptButton();

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
