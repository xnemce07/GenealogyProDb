/*!
 *  \file   eventdetail.cpp
 *  \author Eva Navratilova
 */

#include "eventdetail.h"

SourceCitation EventDetail::constSourceCitation() const
{
    return this->_src;
}

Place EventDetail::constPlace() const
{
    return this->_place;
}

Address EventDetail::constAddress() const
{
    return this->_address;
}

SourceCitation &EventDetail::sourceCitation()
{
    return this->_src;
}

Place &EventDetail::place()
{
    return this->_place;
}

Address &EventDetail::address()
{
    return this->_address;
}


///////////////////////////////////////////////////////////////////////////////
/// Getters
///////////////////////////////////////////////////////////////////////////////

QString EventDetail::getType() const
{
    return this->_type;
}

DateType EventDetail::getDateType() const
{
    return this->_dateType;
}

Date EventDetail::getDate1() const
{
    return this->_date1;
}

Date EventDetail::getDate2() const
{
    return this->_date2;
}

QString EventDetail::getCause() const
{
    return this->_cause;
}

QString EventDetail::getNote() const
{
    return this->_note;
}

Identifier EventDetail::getPriest() const
{
    return _priest;
}

Identifier EventDetail::getWitness1() const
{
    return _witness1;
}

Identifier EventDetail::getWitness2() const
{
    return _witness2;
}

///////////////////////////////////////////////////////////////////////////////
/// Setters
///////////////////////////////////////////////////////////////////////////////

void EventDetail::setType(const QString &t)
{
    this->_type = t;
}

void EventDetail::setDateType(const DateType &type)
{
    this->_dateType = type;
}

void EventDetail::setDate1(const Date &date)
{
    this->_date1 = date;
}

void EventDetail::setDate2(const Date &date)
{
    this->_date2 = date;
}

void EventDetail::setCause(const QString &c)
{
    this->_cause = c;
}

void EventDetail::setNote(const QString &n)
{
    this->_note = n;
}

void EventDetail::setPriest(const Identifier &priest)
{
    _priest = priest;
}

void EventDetail::setWitness1(const Identifier &wittness1)
{
    _witness1 = wittness1;
}

void EventDetail::setWitness2(const Identifier &wittness2)
{
    _witness2 = wittness2;
}



