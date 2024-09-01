#include "VICUS_DrawingOSM.h"
#include "VICUS_Constants.h"

#include "IBK_MessageHandler.h"
#include "IBK_messages.h"
#include "IBK_physics.h"

#include "NANDRAD_Utilities.h"

#include <QDebug>

#include "tinyxml.h"


namespace VICUS {


DrawingOSM::~DrawingOSM() {
	// Clean up dynamically allocated nodes
	for (Node* node : m_nodes) {
		delete node;
	}
	m_nodes.clear();

	// Clean up dynamically allocated ways
	for (Way* way : m_ways) {
		delete way;
	}
	m_ways.clear();

	// Clean up dynamically allocated relations
	for (Relation* relation : m_relations) {
		delete relation;
	}
	m_relations.clear();
}

void DrawingOSM::readXML(const TiXmlElement * element) {
	FUNCID(DrawingOSM::readXML);

	try {
		// search for mandatory attributes

		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "bounds") {
			}
			attrib = attrib->Next();
		}
		// search for mandatory elements
		// reading elements
		const TiXmlElement * c = element->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "bounds") {
				// search for mandatory attributes
				if (!TiXmlAttribute::attributeByName(c, "minlat"))
					throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
											 IBK::FormatString("Missing required 'minlat' attribute.") ), FUNC_ID);
				if (!TiXmlAttribute::attributeByName(c, "minlon"))
					throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
											 IBK::FormatString("Missing required 'minlon' attribute.") ), FUNC_ID);
				if (!TiXmlAttribute::attributeByName(c, "maxlat"))
					throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
											 IBK::FormatString("Missing required 'maxlat' attribute.") ), FUNC_ID);
				if (!TiXmlAttribute::attributeByName(c, "maxlon"))
					throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
											 IBK::FormatString("Missing required 'maxlon' attribute.") ), FUNC_ID);

				// reading attributes
				const TiXmlAttribute * attrib = c->FirstAttribute();
				while (attrib) {
					const std::string & attribName = attrib->NameStr();
					if (attribName == "minlat")
						m_boundingBox.minlat = attrib->DoubleValue();
					else if (attribName == "minlon")
						m_boundingBox.minlon = attrib->DoubleValue();
					else if (attribName == "maxlat")
						m_boundingBox.maxlat = attrib->DoubleValue();
					else if (attribName == "maxlon")
						m_boundingBox.maxlon = attrib->DoubleValue();
					attrib = attrib->Next();
				}
			}
			else if (cName == "node") {
				Node *obj = new Node();
				obj->readXML(c);
				m_nodes.push_back(obj);
			}
			else if (cName == "way") {
				Way *obj = new Way();
				obj->readXML(c);
				m_ways.push_back(obj);
			}
			else if (cName == "relation") {
				Relation *obj = new Relation();
				obj->readXML(c);
				m_relations.push_back(obj);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Drawing' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Drawing::Text' element.").arg(ex2.what()), FUNC_ID);
	}
}

bool DrawingOSM::readOSMFile(QString filePath)
{
	TiXmlDocument document(filePath.toStdString());

	if (!document.LoadFile()) {
		qDebug() << "Failed to load file: " << filePath;
		qDebug() << "Error: " << document.ErrorDesc();
		return false;
	}

	TiXmlElement* root = document.RootElement();
	if (!root) {
		qDebug() << "Failed to get root element";
		return false;
	}

	// Print the root element's name
	qDebug() << "Root element: " << root->Value();

	readXML(document.RootElement());
	return true;
}

} // namespace VICUS
