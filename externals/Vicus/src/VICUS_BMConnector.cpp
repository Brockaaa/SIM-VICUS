/*	BSD 3-Clause License

    This file is part of the BlockMod Library.

    Copyright (c) 2019, Andreas Nicolai
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
       contributors may be used to endorse or promote products derived from
       this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "VICUS_BMConnector.h"

#include <QXmlStreamWriter>
#include <QStringList>
#include <QDebug>
#include "tinyxml.h"


namespace VICUS {

TiXmlElement *BMConnector::writeXML(TiXmlElement *parent) const
{
    TiXmlElement * e = new TiXmlElement("Connector");
    parent->LinkEndChild(e);
    e->SetAttribute("source", m_sourceSocket.toStdString());
    e->SetAttribute("target", m_targetSocket.toStdString());
    for(auto Segment : m_segments){
        TiXmlElement * e2 = new TiXmlElement("Segment");
        e->LinkEndChild(e2);
        e2->SetAttribute("orientation", Segment.m_direction == Qt::Horizontal ? "Horizontal" : "Vertical");
        e2->SetAttribute("offset", Segment.m_offset);
    }
    return e;
}

void BMConnector::readXML(const TiXmlElement *element)
{
    m_sourceSocket = QString::fromStdString(element->Attribute("source"));
    m_targetSocket = QString::fromStdString(element->Attribute("target"));
    m_segments.clear();
    for(const TiXmlElement * e = element->FirstChildElement("Segment"); e; e = e->NextSiblingElement("Segment")) {
        Segment s;
        if (e->Attribute("orientation") == std::string("Horizontal"))
            s.m_direction = Qt::Horizontal;
        else
            s.m_direction = Qt::Vertical;
        e->Attribute("offset", &s.m_offset);
        m_segments.push_back(s);
    }
}

} // namespace VICUS

