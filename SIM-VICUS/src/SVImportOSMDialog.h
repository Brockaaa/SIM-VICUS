#ifndef SVIMPORTOSMDIALOG_H
#define SVIMPORTOSMDIALOG_H

#include <QDialog>
#include <QString>
#include <VICUS_DrawingOSM.h>

namespace Ui {
class SVImportOSMDialog;
}

class SVImportOSMDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SVImportOSMDialog(QWidget *parent = nullptr);
	~SVImportOSMDialog();

	bool import();

	VICUS::DrawingOSM& drawingOSM(){ return m_drawingOSM; }



	QString					m_fname = "";
private slots:
	void on_buttonbox_accepted();

	void on_toolButtonLocal_clicked();

private:
	void downloadOsmFile(double minlon, double minlat, double maxlon, double maxlat);

	bool					m_stateSelectFromMap = false;

	Ui::SVImportOSMDialog	*m_ui;

	VICUS::DrawingOSM		m_drawingOSM;


};

#endif // SVIMPORTOSMDIALOG_H
