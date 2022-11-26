/*!
 *  \file   head.cpp
 *  \author Eva Navratilova
 */

#include "head.h"


Address Head::constSrcCorpAddr() const
{
    return this->_srcCorpAddr;
}

Address &Head::srcCorpAddr()
{
    return this->_srcCorpAddr;
}

///////////////////////////////////////////////////////////////////////////////

QString Head::getSrc() const
{
    return this->_src;
}

QString Head::getSrcVersion() const
{
    return this->_srcVersion;
}

QString Head::getSrcName() const
{
    return this->_srcName;
}

QString Head::getSrcCorp() const
{
    return this->_srcCorp;
}

QString Head::getSrcData() const
{
    return this->_srcData;
}

Date Head::getSrcDataDate() const
{
    return this->_srcDataDate;
}

QString Head::getDest() const
{
    return this->_dest;
}

Date Head::getDate() const
{
    return this->_date;
}

QTime Head::getTime() const
{
    return this->_time;
}

Identifier Head::getRefSubm() const
{
    return this->_refSubm;
}

QString Head::getFile() const
{
    return this->_file;
}

QString Head::getCopr() const
{
    return this->_copr;
}

QString Head::getGedVers() const
{
    return this->_gedVers;
}

QString Head::getGedForm() const
{
    return this->_gedForm;
}

QString Head::getCharSet() const
{
    return this->_charSet;
}

QString Head::getCharVers() const
{
    return this->_charVers;
}

QString Head::getLang() const
{
    return this->_lang;
}

QString Head::getPlac() const
{
    return this->_plac;
}

QString Head::getNote() const
{
    return this->_note;
}

///////////////////////////////////////////////////////////////////////////////

void Head::setSrc(const QString src)
{
    this->_src = src;
}

void Head::setSrcVersion(const QString vers)
{
    this->_srcVersion = vers;
}

void Head::setSrcName(const QString name)
{
    this->_srcName = name;
}

void Head::setSrcCorp(const QString corp)
{
    this->_srcCorp = corp;
}

void Head::setSrcData(const QString data)
{
    this->_srcData = data;
}

void Head::setSrcDataDate(const Date date)
{
    this->_srcDataDate = date;
}

void Head::setDest(const QString dest)
{
    this->_dest = dest;
}

void Head::setDate(const Date date)
{
    this->_date = date;
}

void Head::setTime(const QTime time)
{
    this->_time = time;
}

void Head::setRefSubm(const Identifier subm)
{
    this->_refSubm = subm;
}

void Head::setFile(const QString file)
{
    this->_file = file;
}

void Head::setCopr(const QString copr)
{
    this->_copr = copr;
}

void Head::setGedVers(const QString vers)
{
    this->_gedVers = vers;
}

void Head::setGedForm(const QString form)
{
    this->_gedForm = form;
}

void Head::setCharSet(const QString charset)
{
    this->_charSet = charset;
}

void Head::setCharVers(const QString vers)
{
    this->_charVers = vers;
}

void Head::setLang(const QString lang)
{
    this->_lang = lang;
}

void Head::setPlac(const QString place)
{
    this->_plac = place;
}

void Head::setNote(const QString note)
{
    this->_note = note;
}



