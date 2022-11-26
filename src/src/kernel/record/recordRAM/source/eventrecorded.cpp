/*!
 *  \file   eventrecorded.cpp
 *  \author Eva Navratilova
 */

#include "eventrecorded.h"

EventRecorded::EventRecorded()
    : _eventAttrType(CommonEventType::BIRT)
{

}

EventRecorded::EventRecorded(CommonEventType t)
    : _eventAttrType(t)
{
}

/// Validatiors

bool EventRecorded::isDateContained(const Date date) const
{
    if(date.isNull())
    {
        return true;
    }
    else
    {
        Date dateFrom = this->getDateFrom();
        Date dateTo = this->getDateTo();
        return ((dateFrom <= date) || dateFrom.isNull())
                &&
                ((date <= dateTo)  || dateTo.isNull());
    }
}

/// Getters

CommonEventType EventRecorded::getEventType() const
{
    return _eventAttrType;
}

Date EventRecorded::getDateFrom() const
{
    return _date1;
}

Date EventRecorded::getDateTo() const
{
    return _date2;
}

QString EventRecorded::getPlacName() const
{
    return _placName;
}

QString EventRecorded::getPage1() const
{
    return _page1;
}

QString EventRecorded::getPage2() const
{
    return _page2;
}

QString EventRecorded::getUrl() const
{
    return _url;
}

/// Setters

void EventRecorded::setDateFrom(const Date &from)
{
    _date1 = from;
}

void EventRecorded::setDateTo(const Date &to)
{
    _date2 = to;
}

void EventRecorded::setPlaceName(const QString &plac)
{
    _placName = plac;
}

void EventRecorded::setPage1(const QString &page)
{
    _page1 = page;
}

void EventRecorded::setPage2(const QString &page)
{
    _page2 = page;
}

void EventRecorded::setUrl(const QString &url)
{
    _url = url;
}
