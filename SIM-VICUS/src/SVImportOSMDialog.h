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

	/*! Opens the Import OSM Dialog. After a successful import, the resulting DrawingOSM can be requested with drawingOSM() */
	bool import();

	/*! returns the created DrawingOSM. Should only be called after a successful import */
	VICUS::DrawingOSM& drawingOSM(){ return m_drawingOSM; }

private slots:
	/*! connected to slot of buttonbox. Will be called when user clicked on import */
	void buttonbox_accepted();
	/*! connected to slot of buttonbox. Will be called when user clicked on cancel */
	void buttonbox_cancel();
	/*! will call createQml() */
	void on_toolButtonMap_clicked();
	/*! connected to Import button of qml quick widget */
	void on_qmlOK_clicked();
	/*! connected to cancel button of qml quick widget */
	void on_qmlCancel_clicked();
	/*! enables or disables widget containing local file import */
	void on_radioButtonImportFile_toggled(bool checked);
	/*! enables or disables widget containing osm download dialog */
	void on_radioButtonDownloadOSM_toggled(bool checked);

private:
	/*! downloads the osm file specified by the bounding box by spawning a new process */
	void downloadOsmFile(double minlon, double minlat, double maxlon, double maxlat);
	/*! resets state of the dialog to be ready for the next import */
	void initialise();
	/*! creates the QQuickWindow displaying the OSM Map */
	void createQml();
	/*! requests the file size of the downloaded file and updates the log */
	void updateDownloadProgress();
	/*! attempts to reads the (downloaded or local) file and constructs all objects */
	bool readAndConstructOSM();
	/*! connected to slot in QtExt::BrowseFilenameWidget. Gets called whenever the filename in the widgetBrowseFilename gets changed */
	void on_widgetBrowseFilename_changed();

	QString					m_fname = "";

	// true if user chose radioButton to select map
	bool					m_selectFromMap = false;

	// QML engine, used to spawn the qml window that displays the osm map
	QQmlEngine*				m_engine = nullptr;
	// QML component, used to spawn the qml window that displays the osm map
	QQmlComponent*			m_component = nullptr;
	// QML object, used to spawn the qml window that displays the osm map
	QObject*				m_activeObject = nullptr;
	// import button of the QDialog buttonbox
	QPushButton *			m_importButton = nullptr;
	// Progress notifyer that is passed to readOSM and constructObjects in VICUS_DrawingOSM
	OSMImportProgressNotifyer*	m_progressNotifyer = nullptr;
	// Process that is used to download the map
	QProcess*				m_process = nullptr;
	// Timer, updates the download progress in the log periodically
	QTimer*					m_timer = nullptr;
	// path of temporary downloaded file
	QString					m_downloadFilePath = "";

	Ui::SVImportOSMDialog	*m_ui;

	// DrawingOSM. After successful import ready to be imported to the scene
	VICUS::DrawingOSM		m_drawingOSM;


};

#endif // SVIMPORTOSMDIALOG_H
