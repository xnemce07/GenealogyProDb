/*!
 *  \file   sourcecitation.cpp
 *  \author Eva Navratilova
 */

#include "sourcecitation.h"

SourceCitation::SourceCitation()
{
    this->_ref = Identifier();
}

SourceCitation::SourceCitation(Identifier ref) : _ref(ref)
{

}

Identifier SourceCitation::getRef() const
{
    return this->_ref;
}

QString SourceCitation::getPage() const
{
    return this->_page;
}

QString SourceCitation::getUrl() const
{
    return this->_url;
}

void SourceCitation::setRef(const Identifier ref)
{
    this->_ref = ref;
    this->_page = QString();
    this->_url = QString();
}

void SourceCitation::setPage(const QString page)
{
    this->_page = page;
}

void SourceCitation::setUrl(const QString url)
{
    this->_url = url;
}

void SourceCitation::remove()
{
    this->setRef(Identifier());
}
