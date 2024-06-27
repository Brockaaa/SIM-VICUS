#ifndef SVIMPORTPDFDIALOG_H
#define SVIMPORTPDFDIALOG_H

#include <QDialog>

namespace Ui {
class SVImportPDFDialog;
}

class SVImportPDFDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SVImportPDFDialog(QWidget *parent = nullptr);
	~SVImportPDFDialog();

	void openFile();

private:
	Ui::SVImportPDFDialog *m_ui;

	QString			m_fileName;
};

#endif // SVIMPORTPDFDIALOG_H
