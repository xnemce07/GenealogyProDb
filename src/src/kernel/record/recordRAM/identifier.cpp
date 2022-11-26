/*!
 *  \file   identifier.cpp
 *  \author Eva Navratilova
 */

#include "identifier.h"

unsigned long long Identifier::getNumber()
{
    return this->_number;
}

Identifier::Identifier(QString ref)
{
    *this = this->fromString(ref);
}

void Identifier::operator=(Identifier const &obj)
{
    this->_type = obj._type;
    this->_number = obj._number;
}

bool Identifier::operator==(const Identifier &obj) const
{
    return (this->_type == obj._type && this->_number == obj._number);
}

bool Identifier::operator!=(const Identifier &obj) const
{
    return ! ((*this) == obj);
}

Identifier &Identifier::operator++()
{
    ++(this->_number);
    return *this;
}

Identifier Identifier::operator++(int)
{
    Identifier res = (*this);
    ++(*this);
    return res;
}

bool Identifier::operator<(const Identifier &obj) const
{
    return (this->_type == obj._type && this->_number < obj._number);
}

bool Identifier::operator<=(const Identifier &obj) const
{
    return (*this < obj) || (*this == obj);
}

QString Identifier::get() const
{
    if(! this->isValid())
        return QString();

    QString id;
    switch(this->_type)
    {
    case IdentifierType::ID_INDI:
        id = INDI_STRING;
        break;
    case IdentifierType::ID_FAM:
        id = FAM_STRING;
        break;
    case IdentifierType::ID_SUBM:
        id = SUBM_STRING;
        break;
    case IdentifierType::ID_SOUR:
        id = SOUR_STRING;
        break;
    default:
        return "INVALID";
    }
    return id + QString::number(this->_number);
}

Identifier Identifier::fromString(const QString string)
{
    QRegularExpression expression("^([A-Z]{3})((0)|([1-9]\\d*))$");
    QRegularExpressionMatch match = expression.match(string);
    if(match.isValid())
    {
        IdentifierType type = IdentifierType::ID_INVAL;
        QString typeString = match.captured(1);
        unsigned long long int num = static_cast<unsigned long long>(match.captured(2).toInt());

        if(typeString == INDI_STRING)
        {
            type = IdentifierType::ID_INDI;
        }
        else if(typeString == FAM_STRING)
        {
            type = IdentifierType::ID_FAM;
        }
        else if(typeString == SUBM_STRING)
        {
            type = IdentifierType::ID_SUBM;
        }
        else if(typeString == SOUR_STRING)
        {
            type = IdentifierType::ID_SOUR;
        }

        if(type != IdentifierType::ID_INVAL)
        {
            return Identifier(type, num);
        }
    }
    return Identifier();
}

bool Identifier::isValid() const
{
    return (this->_type != IdentifierType::ID_INVAL);
}


