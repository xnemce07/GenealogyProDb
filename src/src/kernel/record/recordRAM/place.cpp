/*!
 *  \file   place.cpp
 *  \author Eva Navratilova
 */

#include "place.h"


QString Place::getName() const
{
    return this->_name;
}

QString Place::getHier() const
{
    return this->_hier;
}

QString Place::getLatit() const
{
    return this->_latit;
}

QString Place::getLongit() const
{
    return this->_longit;
}

void Place::setName(const QString n)
{
    this->_name = n;
}

void Place::setHier(const QString h)
{
    this->_hier = h;
}

void Place::setLatit(const QString l)
{
    this->_latit = l;
}

void Place::setLongit(const QString l)
{
    this->_longit = l;
}
