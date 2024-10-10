#include "SVImportOSMDialog.h"
#include "ui_SVImportOSMDialog.h"
#include "SVSettings.h"

#include <QtNetwork>
#include <QFileDialog>
#include <QQmlContext>
#include <QQuickItem>
#include <QVariantMap>
#include <QApplication>

SVImportOSMDialog::SVImportOSMDialog(QWidget *parent)
	: QDialog(parent)
	, m_ui(new Ui::SVImportOSMDialog)
{
	m_ui->setupUi(this);
	// Expose the QQuickWidget's width and height to QML
	m_ui->quickWidget->rootContext()->setContextProperty("widgetWidth", m_ui->quickWidget->width());
	m_ui->quickWidget->rootContext()->setContextProperty("widgetHeight", m_ui->quickWidget->height());

	// Connect to the dialog's show event to update the properties
	m_ui->quickWidget->rootContext()->setContextProperty("widgetWidth", m_ui->quickWidget->width());
	m_ui->quickWidget->rootContext()->setContextProperty("widgetHeight", m_ui->quickWidget->height());

	connect(m_ui->buttonBox, &QDialogButtonBox::accepted, this, &SVImportOSMDialog::on_buttonbox_accepted);
	on_toolButtonLocal_clicked();
}

SVImportOSMDialog::~SVImportOSMDialog()
{
	delete m_ui;
}

bool SVImportOSMDialog::import()
{
	//m_fname = QFileDialog::getOpenFileName(
	//	this,
	//	tr("Select File to open"),
	//	"/home/sandisk/SHK/osm/",
	//	tr("OSM (*.osm *.xml *.txt);;All files (*.*)"), nullptr,
	//	SVSettings::instance().m_dontUseNativeDialogs ? QFileDialog::DontUseNativeDialog : QFileDialog::Options()
	//	);

	//m_drawingOSM = VICUS::DrawingOSM();
	//if (fname.contains("vicosm")) {
	//	TiXmlDocument document(fname.toStdString());

	//	if (!document.LoadFile()) {
	//		qDebug() << "Failed to load file: " << fname;
	//		qDebug() << "Error: " << document.ErrorDesc();
	//		return false;
	//	}

	//	TiXmlElement* root = document.RootElement();
	//	if (!root) {
	//		qDebug() << "Failed to get root element";
	//		return false;
	//	}

	//	// Print the root element's name
	//	qDebug() << "Root element: " << root->Value();
	//	const TiXmlElement * c = document.FirstChildElement();
	//	const TiXmlElement * d = c->FirstChildElement();

	//	m_drawingOSM.readXML(d->FirstChildElement());
	//} else if (fname.contains(".osm")) {
	//	if (!m_drawingOSM.readOSMFile(fname))
	//		return false;
	//	m_drawingOSM.constructObjects();
	//} else {
		//m_ui->quickWidget->rootContext()->setContextProperty("widgetWidth", m_ui->quickWidget->width());
		//m_ui->quickWidget->rootContext()->setContextProperty("widgetHeight", m_ui->quickWidget->height());

		exec();
	//	//open();
	//	//QEventLoop loop;
	//	//connect(this, &QDialog::finished, &loop, &QEventLoop::quit);
	//	//loop.exec();
	//	//if (!m_drawingOSM.readOSMFile(m_fname))
	//	//	return false;
	//	//m_drawingOSM.constructObjects();
	//}
	//if (!m_drawingOSM.readOSMFile(m_fname))
	//	return false;
	//m_drawingOSM.constructObjects();

	m_fname = QString("/home/sandisk/SHK/osm/Garrel.osm");

	return true;
}

void SVImportOSMDialog::on_buttonbox_accepted()
{
	//m_drawingOSM.m_enable3D = m_ui->checkBoxToggle3D->isChecked();

	if (m_stateSelectFromMap) {
		// Get the root object from QML
		QQuickItem *rootObject = m_ui->quickWidget->rootObject();
		if (!rootObject) {
			qDebug() << "Root object not found!";
			return;
		}

		// Print the children of the root object for debugging
		QList<QQuickItem*> children = rootObject->childItems();
		for (QQuickItem* child : children) {
			qDebug() << "Child object:" << child->objectName();
		}

		// Get the Map object from QML
		QQuickItem *mapObject = rootObject->findChild<QQuickItem*>("mapObject");
		if (mapObject) {
			// Call the getBoundingBox method from QML
			QVariant returnedValue;
			QMetaObject::invokeMethod(mapObject, "getBoundingBox",
									  Q_RETURN_ARG(QVariant, returnedValue));
			QVariantMap boundingBox = returnedValue.toMap();
			qDebug() << "Bounding Box:" << boundingBox;

			// call downloadOsmFile: Bounding Box: QMap(("northWest", QVariant(QVariantMap, QMap(("latitude", QVariant(double, 52.5358))("longitude", QVariant(double, 13.3253)))))("southEast", QVariant(QVariantMap, QMap(("latitude", QVariant(double, 52.4968))("longitude", QVariant(double, 13.4302))))))
			QVariantMap northWest = boundingBox["northWest"].toMap();
			QVariantMap southEast = boundingBox["southEast"].toMap();

			double minlon = northWest["longitude"].toDouble();
			double minlat = southEast["latitude"].toDouble();
			double maxlon = southEast["longitude"].toDouble();
			double maxlat = northWest["latitude"].toDouble();

			downloadOsmFile(minlon, minlat, maxlon, maxlat);
		} else {
			qDebug() << "Map object not found!";
			return;
		}

		m_fname = QString("/home/sandisk/SHK/downloaded_map.osm");
	} else {
		m_fname = m_ui->widgetBrowseFilename->filename();
		//if (fname.contains("vicosm")) {
		//	TiXmlDocument document(fname.toStdString());

		//	if (!document.LoadFile()) {
		//		qDebug() << "Failed to load file: " << fname;
		//		qDebug() << "Error: " << document.ErrorDesc();
		//		return;
		//	}

		//	TiXmlElement* root = document.RootElement();
		//	if (!root) {
		//		qDebug() << "Failed to get root element";
		//		return;
		//	}

		//	// Print the root element's name
		//	qDebug() << "Root element: " << root->Value();
		//	const TiXmlElement * c = document.FirstChildElement();
		//	const TiXmlElement * d = c->FirstChildElement();

		//	m_drawingOSM.readXML(d->FirstChildElement());
		/*} else if (fname.contains(".osm")) {
			if (!m_drawingOSM.readOSMFile(fname))
				return;
			m_drawingOSM.constructObjects();
		}*/
	}

	//if (!m_drawingOSM.readOSMFile(m_fname))
	//	return;
	//m_drawingOSM.constructObjects();
}

void SVImportOSMDialog::on_toolButtonLocal_clicked()
{
	m_stateSelectFromMap = !m_stateSelectFromMap;
	if (m_stateSelectFromMap) {
		m_ui->toolButtonLocal->setText("Select Local .osm file");
		m_ui->quickWidget->setEnabled(true);
		m_ui->widgetBrowseFilename->setVisible(false);
	} else {
		m_ui->toolButtonLocal->setText("Select From Map");
		m_ui->quickWidget->setEnabled(false);
		m_ui->widgetBrowseFilename->setVisible(true);
	}

}

void SVImportOSMDialog::downloadOsmFile(double minlon, double minlat, double maxlon, double maxlat)
{
	// Construct the URL for the OSM file
	QString url = QString("https://api.openstreetmap.org/api/0.6/map?bbox=%1,%2,%3,%4")
					  .arg(minlon)
					  .arg(minlat)
					  .arg(maxlon)
					  .arg(maxlat);

	QProcess process;
	process.setWorkingDirectory("/home/sandisk/SHK");
	QString binary = "/usr/bin/curl";
	QStringList arguments;
	arguments << "-o" << "/home/sandisk/SHK/downloaded_map.osm" << url;

	process.start(binary, arguments);

	if (!process.waitForStarted())
		return;

	if (!process.waitForFinished())
		return;

	qDebug() << process.readAllStandardError();
	qDebug() << process.readAllStandardOutput();
}

