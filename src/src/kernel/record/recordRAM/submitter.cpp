/*!
 *  \file   submitter.cpp
 *  \author Eva Navratilova
 */

#include "submitter.h"

Submitter::Submitter(Identifier ref) : _ref(ref) {}

bool Submitter::isEmpty() const
{
    bool isNameEmpty = this->getName().isEmpty();
    bool isLangEmpty = this->getLang().isEmpty();
    bool isNoteEmpty = this->getNote().isEmpty();
    bool isDateEmpty = this->getDate().isNull();

    return (isNameEmpty && isLangEmpty && isNoteEmpty && isDateEmpty);
}


/// Getters

Identifier Submitter::getRef() const
{
    return this->_ref;
}

QString Submitter::getName() const
{
    return this->_name;
}

QString Submitter::getLang() const
{
    return this->_lang;
}

QString Submitter::getNote() const
{
    return this->_note;
}

Date Submitter::getDate() const
{
    return this->_date;
}

QTime Submitter::getTime() const
{
    return this->_time;
}


/// Setters

void Submitter::setName(const QString name)
{
    this->_name = name;
}

void Submitter::setLang(const QString lang)
{
    this->_lang = lang;
}

void Submitter::setNote(const QString note)
{
    this->_note = note;
}

void Submitter::setDate(const Date date)
{
    this->_date = date;
}

void Submitter::setTime(const QTime time)
{
    this->_time = time;
}
