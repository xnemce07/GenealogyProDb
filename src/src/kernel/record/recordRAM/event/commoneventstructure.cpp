/*!
 *  \file   commoneventstructure.cpp
 *  \author Eva Navratilova
 */

#include "commoneventstructure.h"


CommonEventStructure::CommonEventStructure()
: _type(CommonEventType::EMPT)
{}

CommonEventStructure::CommonEventStructure(CommonEventType t)
    : _type(t)
{}

CommonEventStructure::CommonEventStructure(const CommonEventStructure &s)
{
    *this = s;
}

CommonEventStructure &CommonEventStructure::operator=(const CommonEventStructure &s)
{
    _type = s._type;
    _descr = s._descr;
    _detail = s._detail;
    return *this;
}

EventDetail CommonEventStructure::constDetail() const
{
    return this->_detail;
}

EventDetail &CommonEventStructure::detail()
{
    return this->_detail;
}

CommonEventType CommonEventStructure::getType() const
{
    return this->_type;
}

QString CommonEventStructure::getDescription() const
{
    return this->_descr;
}

void CommonEventStructure::setDescription(QString d)
{
    this->_descr = d;
}
