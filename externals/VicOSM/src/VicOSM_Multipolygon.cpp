#include "VicOSM_Multipolygon.h"
#include "VicOSM_Constants.h"
#include <IBK_messages.h>
#include <IBK_Exception.h>

namespace VicOSM {

void Multipolygon::readXML(const TiXmlElement * element) {
	FUNCID(Multipolygon::readXML);
	try {
		// Read outer polyline
		const TiXmlElement* outerElement = element->FirstChildElement("Outer");
		if (outerElement == nullptr)
			throw IBK::Exception("Missing 'Outer' element.", FUNC_ID);

		std::string text = outerElement->GetText();
		text = IBK::replace_string(text, ",", " ");
		std::vector<double> vals;
		try {
			IBK::string2valueVector(text, vals);
			// must have n*2 elements
			if (vals.size() % 2 != 0)
				throw IBK::Exception("Mismatching number of values.", FUNC_ID);
			if (vals.empty())
				throw IBK::Exception("Missing values.", FUNC_ID);
			m_outerPolyline.resize(vals.size() / 2);
			for (unsigned int i=0; i<m_outerPolyline.size(); ++i){
				m_outerPolyline[i].m_x = vals[i*2];
				m_outerPolyline[i].m_y = vals[i*2+1];
			}
		} catch (IBK::Exception & ex) {
			throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(outerElement->Row()).arg(
										 IBK::FormatString("Error reading vector element '%1'.").arg("Outer") ), FUNC_ID);
		}

		// Read inner polylines (holes)
		const TiXmlElement* holesElement = element->FirstChildElement("Holes");
		if (holesElement != nullptr) {
			const TiXmlElement* holeElement = holesElement->FirstChildElement("Hole");
			while (holeElement != nullptr) {
				text = holeElement->GetText();
				text = IBK::replace_string(text, ",", " ");
				vals.clear();
				try {
					IBK::string2valueVector(text, vals);
					if (vals.size() % 2 != 0)
						throw IBK::Exception("Mismatching number of values.", FUNC_ID);
					if (vals.empty())
						throw IBK::Exception("Missing values.", FUNC_ID);
					std::vector<IBKMK::Vector2D> innerPolyline;
					innerPolyline.resize(vals.size() / 2);
					for (unsigned int i=0; i<innerPolyline.size(); ++i){
						innerPolyline[i].m_x = vals[i*2];
						innerPolyline[i].m_y = vals[i*2+1];
					}
					m_innerPolylines.push_back(innerPolyline);
				} catch (IBK::Exception & ex) {
					throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(holeElement->Row()).arg(
												 IBK::FormatString("Error reading vector element '%1'.").arg("Hole") ), FUNC_ID);
				}
				holeElement = holeElement->NextSiblingElement("Hole");
			}
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Multipolygon' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Multipolygon' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Multipolygon::writeXML(TiXmlElement * parent) const {
	FUNCID(Multipolygon::writeXML);

	if (m_outerPolyline.empty())
		return nullptr;

	TiXmlElement * e = new TiXmlElement("Multipolygon");
	parent->LinkEndChild(e);

	TiXmlElement * outer = new TiXmlElement("Outer");
	e->LinkEndChild(outer);

	std::stringstream vals;
	for (unsigned int i=0; i<m_outerPolyline.size(); ++i) {
		vals << m_outerPolyline[i].m_x << " " << m_outerPolyline[i].m_y;
		if (i<m_outerPolyline.size()-1)  vals << ", ";
	}
	TiXmlText * text = new TiXmlText( vals.str() );
	outer->LinkEndChild( text );

	if (!m_innerPolylines.empty()) {
		TiXmlElement * holes = new TiXmlElement("Holes");
		e->LinkEndChild(holes);
		for (unsigned int i=0; i<m_innerPolylines.size(); ++i) {
			TiXmlElement * hole = new TiXmlElement("Hole");
			holes->LinkEndChild(hole);

			std::stringstream vals;
			for (unsigned int j=0; j<m_innerPolylines[i].size(); ++j) {
				vals << m_innerPolylines[i][j].m_x << " " << m_innerPolylines[i][j].m_y;
				if (j<m_innerPolylines[i].size()-1)  vals << ", ";
			}
			TiXmlText * text = new TiXmlText( vals.str() );
			hole->LinkEndChild( text );
		}
	}

	return e;
}

} // namespace VicOSM
