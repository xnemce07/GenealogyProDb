/*!
 *  \file   personalnamepieces.cpp
 *  \author Eva Navratilova
 */

#include "personalnamepieces.h"


QString PersonalNamePieces::getPrefix() const
{
    return this->npfx;
}

QString PersonalNamePieces::getGiven() const
{
    return this->givn;
}

QString PersonalNamePieces::getSurname() const
{
    return this->surn;
}

QString PersonalNamePieces::getMarname() const
{
    return this->marn;
}

QString PersonalNamePieces::getSuffix() const
{
    return this->nsfx;
}


// Setters
void PersonalNamePieces::setPrefix(const QString str)
{
    this->npfx = str;
}

void PersonalNamePieces::setGiven(const QString str)
{
    this->givn = str;
}

void PersonalNamePieces::setSurname(const QString str)
{
    this->surn = str;
}

void PersonalNamePieces::setMarname(const QString str)
{
    this->marn = str;
}

void PersonalNamePieces::setSuffix(const QString str)
{
    this->nsfx = str;
}





