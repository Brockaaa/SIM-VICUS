#ifndef SVIMPORTOSMDIALOG_H
#define SVIMPORTOSMDIALOG_H

#include <QDialog>
#include <QString>
#include <VICUS_DrawingOSM.h>
#include <IBK_NotificationHandler.h>
#include <QProgressDialog>
#include <QApplication>
#include <QPropertyAnimation>

namespace Ui {
class SVImportOSMDialog;
}

class OSMImportProgressNotifyer : public IBK::NotificationHandler {
public:
	void notify() override {}
	void notify(double, const char *) override;
	void notifyDownloadProgress(QString text);
	void enableAnimation();
	void disableAnimation();
	void enablePrgBar(bool enable);
	QProgressBar		*m_prgBar = nullptr;
	QPropertyAnimation	*m_animation = nullptr;
};

class QQmlEngine;
class QQmlComponent;
class QProcess;
class QTimer;

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

	void on_buttonbox_cancel();

	void on_toolButtonMap_clicked();

	void on_qmlOK_clicked();
	void on_qmlCancel_clicked();

	void on_radioButtonImportFile_toggled(bool checked);

	void on_radioButtonDownloadOSM_toggled(bool checked);

private:
	void downloadOsmFile(double minlon, double minlat, double maxlon, double maxlat);

	void initialise();

	void createQml();

	void updateDownloadProgress();

	bool readAndConstructOSM();

	void on_widgetBrowseFilename_changed();

	bool					m_selectFromMap = false;

	QQmlEngine*				m_engine = nullptr;

	QQmlComponent*			m_component = nullptr;

	QObject*				m_activeObject = nullptr;

	QPushButton *			m_importButton = nullptr;

	OSMImportProgressNotifyer*	m_progressNotifyer = nullptr;

	QProcess*				m_process = nullptr;

	QTimer*					m_timer = nullptr;

	QString					m_downloadFilePath = "";

	Ui::SVImportOSMDialog	*m_ui;

	VICUS::DrawingOSM		m_drawingOSM;


};

#endif // SVIMPORTOSMDIALOG_H
