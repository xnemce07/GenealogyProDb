/*!
 *  \file   family.cpp
 *  \author Eva Navratilova
 */

#include "family.h"

bool Family::isEvent(CommonEventType t) const
{
    return this->_events.contains(t);
}

CommonEventStructure Family::constEvent(CommonEventType t) const
{
    if(this->isEvent(t))
        return *this->_events.constFind(t);
    else
        return CommonEventStructure();
}

CommonEventStructure &Family::event(CommonEventType t)
{
    if(!this->isEvent(t))
        this->setEvent(t);
    return *this->_events.find(t);
}

void Family::setEvent(CommonEventType t)
{
    if(!this->isEvent(t))
        this->_events.insert(t,CommonEventStructure(t));
}

void Family::removeEvent(CommonEventType t)
{
    this->_events.remove(t);
}

void Family::copyFamily(const Family &f)
{
    if(_ref.isValid())
    {
        _events = QHash<CommonEventType, CommonEventStructure>(f._events);

        _refHusb = f._refHusb;
        _refWife = f._refWife;

        _refChil = f._refChil;
    }
}

bool Family::isEmpty() const
{
    /// TODO - verify this - VERY IMPORTANT !!!!! (seems ok)
    int isHusbandPresent = static_cast<int>(this->_refHusb.isValid());
    int isWifePresent = static_cast<int>(this->_refWife.isValid());
    int childrenCount = this->_refChil.length();

    // Family has to have at least two people in it
    bool empty = ((isHusbandPresent + isWifePresent + childrenCount) < 2);

    return empty;
}

bool Family::isMarried() const
{
    return this->isEvent(CommonEventType::MARR);
}

bool Family::isDivorced() const
{
    return this->isEvent(CommonEventType::DIV);
}

///////////////////////////////////////////////////////////////////////////
/// Getters
///////////////////////////////////////////////////////////////////////////

Identifier Family::getRef() const
{
    return this->_ref;
}

Identifier Family::getHusband() const
{
    return this->_refHusb;
}

Identifier Family::getWife() const
{
    return this->_refWife;
}

QVector<Identifier> Family::getChildren() const
{
    return this->_refChil;
}

CommonEventStructure Family::constMarriage() const
{
    return this->constEvent(CommonEventType::MARR);
}

CommonEventStructure Family::constDivorce() const
{
    return this->constEvent(CommonEventType::DIV);
}

CommonEventStructure& Family::marriage()
{
    return this->event(CommonEventType::MARR);
}

CommonEventStructure &Family::divorce()
{
    return this->event(CommonEventType::DIV);
}

///////////////////////////////////////////////////////////////////////////
/// Setters
///////////////////////////////////////////////////////////////////////////

void Family::setHusband(Identifier indi)
{
    /// TODO - gender check? Is it necessary?
    this->_refHusb = indi;
}

void Family::setWife(Identifier indi)
{
    /// TODO - gender check? Is it necessary?
    this->_refWife = indi;
}

void Family::setChild(Identifier indi)
{
    if(this->_refChil.indexOf(indi) == -1)
        this->_refChil.push_back(indi);
}

void Family::setMarriage()
{
    this->setEvent(CommonEventType::MARR);
}

void Family::setDivorce()
{
    this->setEvent(CommonEventType::DIV);
}

void Family::removeHusband()
{
    this->setHusband(Identifier());
}

void Family::removeWife()
{
    this->setWife(Identifier());
}

void Family::removeChild(Identifier indi)
{
    // RemoveOne should be sufficient in this case - there is duplicity check at insetring
    this->_refChil.removeOne(indi);
}

void Family::removeIndividual(Identifier indi)
{
    if(this->_refHusb == indi)
    {
        this->removeHusband();
    }
    else if(this->_refWife == indi)
    {
        this->removeWife();
    }
    else
    {
        this->removeChild(indi);
    }
}

void Family::removeMarriage()
{
    this->removeEvent(CommonEventType::MARR);
}

void Family::removeDivorce()
{
    this->removeEvent(CommonEventType::DIV);
}



