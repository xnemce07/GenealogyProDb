/*!
 *  \file   sourcerecord.cpp
 *  \author Eva Navratilova
 */

#include "sourcerecord.h"


QVector<EventRecorded> SourceRecord::constData(const CommonEventType t) const
{
    switch (t) {
    case CommonEventType::BIRT:
        return _birt;
        break;
    case CommonEventType::MARR:
        return _marr;
        break;
    case CommonEventType::DEAT:
        return _deat;
        break;
    default:
        return QVector<EventRecorded>();
        break;
    }
}

QVector<EventRecorded>& SourceRecord::data(const CommonEventType t)
{
    switch (t) {
    case CommonEventType::BIRT:
        return _birt;
        break;
    case CommonEventType::MARR:
        return _marr;
        break;
    case CommonEventType::DEAT:
        return _deat;
        break;
    default:
        return _othr;
        break;
    }
}


///////////////////////////////////////////////////////////////////////////////


SourceRecord::SourceRecord(const Identifier ref)
    : _ref(ref)
{}

bool SourceRecord::isDateContained(const CommonEventType t, unsigned int index, const Date date) const
{
    if(index < this->getDataCount(t))
    {
        return this->constData(t)[static_cast<int>(index)].isDateContained(date);
    }
    else
    {
        return false;
    }
}



/// Getters

Identifier SourceRecord::getRef() const
{
    return this->_ref;
}

QVector<CommonEventType> SourceRecord::getData() const
{
    QVector<CommonEventType> data;
    if(!_birt.isEmpty())
    {
        data.push_back(CommonEventType::BIRT);
    }
    if(!_marr.isEmpty())
    {
        data.push_back(CommonEventType::MARR);
    }
    if(!_deat.isEmpty())
    {
        data.push_back(CommonEventType::DEAT);
    }
    return data;
}

unsigned int SourceRecord::getDataCount(const CommonEventType t) const
{
    return static_cast<unsigned int>(this->constData(t).count());
}

Date SourceRecord::getDataDateFrom(const CommonEventType t, unsigned int index) const
{
    if(index < this->getDataCount(t))
    {
        return this->constData(t)[static_cast<int>(index)].getDateFrom();
    }
    return Date();
}


Date SourceRecord::getDataDateTo(const CommonEventType t, unsigned int index) const
{
    if(index < this->getDataCount(t))
    {
        return this->constData(t)[static_cast<int>(index)].getDateTo();
    }
    return Date();
}


QString SourceRecord::getDataPlac(const CommonEventType t, unsigned int index) const
{
    if(index < this->getDataCount(t))
    {
        return this->constData(t)[static_cast<int>(index)].getPlacName();
    }
    return QString();
}

QString SourceRecord::getDataPage1(const CommonEventType t, unsigned int index) const
{
    if(index < this->getDataCount(t))
    {
        return this->constData(t)[static_cast<int>(index)].getPage1();
    }
    return QString();
}

QString SourceRecord::getDataPage2(const CommonEventType t, unsigned int index) const
{
    if(index < this->getDataCount(t))
    {
        return this->constData(t)[static_cast<int>(index)].getPage2();
    }
    return QString();
}

QString SourceRecord::getDataUrl(const CommonEventType t, unsigned int index) const
{
    if(index < this->getDataCount(t))
    {
        return this->constData(t)[static_cast<int>(index)].getUrl();
    }
    return QString();
}

QString SourceRecord::getArchive() const
{
    return _auth;
}


QString SourceRecord::getSignature() const
{
    return this->_titl;
}

QString SourceRecord::getOriginator() const
{
    return _publ;
}

QString SourceRecord::getUrl() const
{
    return this->_url;
}


/// Setters

void SourceRecord::setDataDateFrom(const CommonEventType t, unsigned int index, const Date from)
{
    if(index < this->getDataCount(t))
    {
        this->data(t)[static_cast<int>(index)].setDateFrom(from);
    }
}

void SourceRecord::setDataDateTo(const CommonEventType t, unsigned int index, const Date to)
{
    if(index < this->getDataCount(t))
    {
        this->data(t)[static_cast<int>(index)].setDateTo(to);
    }
}

void SourceRecord::setDataPlac(const CommonEventType t, unsigned int index, const QString plac)
{
    if(index < this->getDataCount(t))
    {
        this->data(t)[static_cast<int>(index)].setPlaceName(plac);
    }
}

void SourceRecord::setDataPage1(const CommonEventType t, unsigned int index, const QString page)
{
    if(index < this->getDataCount(t))
    {
        this->data(t)[static_cast<int>(index)].setPage1(page);
    }
}

void SourceRecord::setDataPage2(const CommonEventType t, unsigned int index, const QString page)
{
    if(index < this->getDataCount(t))
    {
        this->data(t)[static_cast<int>(index)].setPage2(page);
    }
}

void SourceRecord::setDataUrl(const CommonEventType t, unsigned int index, const QString url)
{
    if(index < this->getDataCount(t))
    {
        this->data(t)[static_cast<int>(index)].setUrl(url);
    }
}

void SourceRecord::setArchive(const QString &archive)
{
    _auth = archive;
}

void SourceRecord::setSignature(const QString &title)
{
    this->_titl = title;
}

void SourceRecord::setOriginator(const QString &originator)
{
    _publ = originator;
}

void SourceRecord::setUrl(const QString &url)
{
    this->_url = url;
}

unsigned int SourceRecord::addData(const CommonEventType t)
{
    this->data(t).push_back(EventRecorded(t));
    // Return index of data
    return static_cast<unsigned int>(this->constData(t).count() - 1);
}

void SourceRecord::removeData(const CommonEventType t, unsigned int index)
{
    if(index < this->getDataCount(t))
    {
        this->data(t).removeAt(static_cast<int>(index));
    }
}
