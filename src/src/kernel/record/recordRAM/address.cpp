/*!
 *  \file   address.cpp
 *  \author Eva Navratilova
 */

#include "address.h"


QString Address::getAddress() const
{
    return this->address;
}

QString Address::getCity() const
{
    return this->city;
}

QString Address::getState() const
{
    return this->state;
}

QString Address::getPhone() const
{
    return this->phone;
}

QString Address::getEmail() const
{
    return this->email;
}

QString Address::getWww() const
{
    return this->www;
}

///////////////////////////////////////////////////////////////////////////////

void Address::setAddress(QString str)
{
    this->address = str;
}

void Address::setCity(QString str)
{
    this->city = str;
}

void Address::setState(QString str)
{
    this->state = str;
}

void Address::setPhone(QString str)
{
    this->phone = str;
}

void Address::setEmail(QString str)
{
    this->email = str;
}

void Address::setWww(QString str)
{
    this->www = str;
}
