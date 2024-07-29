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
	void changeTwoPointMode();

	void on_groupBoxDocument_clicked(bool checked);

	void on_groupBoxTwoPoints_clicked(bool checked);

	void on_pointCountChanged(int numberOfPointsInScene);

	void on_lineEditDistance_editingFinishedSuccessfully();

	void on_lineEditWidth_editingFinishedSuccessfully();

	void on_lineEditHeight_editingFinishedSuccessfully();

private:
	Ui::SVImportPDFDialog *m_ui;

	bool				m_twoPointMode = false;

	int					m_heightPx = 0;

	int					m_widthPx = 0;

	float				m_scale = 1;

	QImage				m_image;

};

#endif // SVIMPORTPDFDIALOG_H
