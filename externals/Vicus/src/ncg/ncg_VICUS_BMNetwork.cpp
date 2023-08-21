/*	The NANDRAD data model library.

    Copyright (c) 2012-today, Institut für Bauklimatik, TU Dresden, Germany

    Primary authors:
      Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
      Anne Paepcke     <anne.paepcke -[at]- tu-dresden.de>

    This library is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.
*/

#include <VICUS_BMNetwork.h>
#include <VICUS_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VICUS_Constants.h>

#include <tinyxml.h>

namespace VICUS {
/*
void BMNetwork::readXML(const TiXmlElement * element) {
    FUNCID(BMNetwork::readXML);

    try {
        // search for mandatory elements
        // reading elements
        const TiXmlElement * c = element->FirstChildElement();
        while (c) {
            const std::string & cName = c->ValueStr();
            if (cName == "Blocks") {
                const TiXmlElement * c2 = c->FirstChildElement();
                while (c2) {
                    const std::string & c2Name = c2->ValueStr();
                    if (c2Name != "BMBlock")
                        IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
                    BMBlock obj;
                    obj.readXML(c2);
                    m_blocks.push_back(obj);
                    c2 = c2->NextSiblingElement();
                }
            }
            else {
                IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
            }
            c = c->NextSiblingElement();
        }
    }
    catch (IBK::Exception & ex) {
        throw IBK::Exception( ex, IBK::FormatString("Error reading 'BMNetwork' element."), FUNC_ID);
    }
    catch (std::exception & ex2) {
        throw IBK::Exception( IBK::FormatString("%1\nError reading 'BMNetwork' element.").arg(ex2.what()), FUNC_ID);
    }
}

TiXmlElement * BMNetwork::writeXML(TiXmlElement * parent) const {
    TiXmlElement * e = new TiXmlElement("BMNetwork");
    parent->LinkEndChild(e);


    if (!m_blocks.empty()) {
        TiXmlElement * child = new TiXmlElement("Blocks");
        e->LinkEndChild(child);

        for (std::vector<BMBlock>::const_iterator it = m_blocks.begin();
            it != m_blocks.end(); ++it)
        {
            it->writeXML(child);
        }
    }

    return e;
}*/

} // namespace VICUS
