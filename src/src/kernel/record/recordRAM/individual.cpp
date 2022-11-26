/*!
 *  \file   individual.cpp
 *  \author Eva Navratilova
 */

#include "individual.h"

///////////////////////////////////////////////////////////////////////////////

bool Individual::isEvent(const CommonEventType t) const
{
    return this->_events.contains(t);
}

CommonEventStructure Individual::constEvent(const CommonEventType t) const
{
    if(this->isEvent(t))
    {
        return *this->_events.constFind(t);
    }else
        return CommonEventStructure();
}

CommonEventStructure &Individual::event(const CommonEventType t)
{
    if(!this->isEvent(t))
        this->setEvent(t);
    return *this->_events.find(t);
}

void Individual::setEvent(CommonEventType t)
{
    if(!this->isEvent(t))
        this->_events.insert(t,CommonEventStructure(t));
}

void Individual::removeEvent(CommonEventType t)
{
    this->_events.remove(t);
}


///////////////////////////////////////////////////////////////////////////////

Individual::Individual(Identifier ref) : _ref(ref)
{
    this->_gender = Gender::UNDET;

}

Individual::~Individual()
{}

PersonalNamePieces Individual::constName() const
{
    return this->_name;
}

PersonalNamePieces &Individual::name()
{
    return this->_name;
}


CommonEventStructure Individual::constBirth() const
{
    return this->constEvent(CommonEventType::BIRT);
}

CommonEventStructure Individual::constChristening() const
{
    return this->constEvent(CommonEventType::CHR);
}

CommonEventStructure Individual::constDeath() const
{
    return this->constEvent(CommonEventType::DEAT);
}

CommonEventStructure Individual::constBurial() const
{
    return this->constEvent(CommonEventType::BURI);
}

CommonEventStructure Individual::constOccupation(const unsigned int index) const
{
    if(static_cast<signed>(index) < this->_occu.size())
    {
        return this->_occu.at(static_cast<signed>(index));
    }
    return CommonEventStructure();
}

CommonEventStructure Individual::constEducation(const unsigned int index) const
{
    if(static_cast<signed>(index) < this->_educ.size())
    {
        return this->_educ.at(static_cast<signed>(index));
    }
    return CommonEventStructure();
}

CommonEventStructure Individual::constResidence(const unsigned int index) const
{
    if(static_cast<signed>(index) < this->_resi.size())
    {
        return this->_resi.at(static_cast<signed>(index));
    }
    return CommonEventStructure();
}

CommonEventStructure Individual::constReligion(const unsigned int index) const
{
    if(static_cast<signed>(index) < this->_reli.size())
    {
        return this->_reli.at(static_cast<signed>(index));
    }
    return CommonEventStructure();
}

Address Individual::constAddress() const
{
    return _address;
}

CommonEventStructure& Individual::birth()
{
    return this->event(CommonEventType::BIRT);
}

CommonEventStructure &Individual::christening()
{
    return this->event(CommonEventType::CHR);
}

CommonEventStructure& Individual::death()
{
    return this->event(CommonEventType::DEAT);
}

CommonEventStructure &Individual::burial()
{
    return this->event(CommonEventType::BURI);
}

CommonEventStructure &Individual::occupation(const unsigned int index)
{
    if(static_cast<signed>(index) == this->_occu.size())
    {
        this->_occu.push_back(CommonEventStructure());
    }

    auto it = this->_occu.begin();
    it += index;
    return *it;
}

CommonEventStructure &Individual::education(const unsigned int index)
{
    if(static_cast<signed>(index) == this->_educ.size())
    {
        this->_educ.push_back(CommonEventStructure());
    }
    auto it = this->_educ.begin();
    it += index;
    return *it;
}

CommonEventStructure &Individual::residence(const unsigned int index)
{
    if(static_cast<signed>(index) == this->_resi.size())
    {
        this->_resi.push_back(CommonEventStructure());
    }
    auto it = this->_resi.begin();
    it += index;
    return *it;
}

CommonEventStructure &Individual::religion(const unsigned int index)
{
    if(static_cast<signed>(index) == this->_reli.size())
    {
        this->_reli.push_back(CommonEventStructure());
    }
    auto it = this->_reli.begin();
    it += index;
    return *it;
}

Address &Individual::address()
{
    return _address;
}


/// GETTERS

Identifier Individual::getRef() const
{
    return this->_ref;
}

Gender Individual::getGender() const
{
    return this->_gender;
}

unsigned int Individual::getOccuCount() const
{
    return static_cast<unsigned>(this->_occu.length());
}

unsigned int Individual::getEducCount() const
{
    return static_cast<unsigned>(this->_educ.length());
}

unsigned int Individual::getResiCount() const
{
    return static_cast<unsigned>(this->_resi.length());
}

unsigned int Individual::getReliCount() const
{
    return static_cast<unsigned>(this->_reli.length());
}

QString Individual::getNote() const
{
    return this->_note;
}

bool Individual::isBorn() const
{
    return this->isEvent(CommonEventType::BIRT);
}

bool Individual::isChristened() const
{
    return this->isEvent(CommonEventType::CHR);
}

bool Individual::isBuried() const
{
    return this->isEvent(CommonEventType::BURI);
}


bool Individual::isDeceased() const
{
    return this->isEvent(CommonEventType::DEAT);
}




/// SETTERS

void Individual::setGender(const Gender g)
{
    this->_gender = g;
}

void Individual::setNote(QString n)
{
    this->_note = n;
}

void Individual::setDeath()
{
    this->setEvent(CommonEventType::DEAT);
}

void Individual::swapOccu(const unsigned int index1, const unsigned int index2)
{
    unsigned int count = this->getOccuCount();
    if(index1 < count || index2 < count)
    {
        std::swap(_occu[static_cast<int>(index1)], _occu[static_cast<int>(index2)]);
    }
}

void Individual::swapEduc(const unsigned int index1, const unsigned int index2)
{
    unsigned int count = this->getEducCount();
    if(index1 < count || index2 < count)
    {
        std::swap(_educ[static_cast<int>(index1)], _educ[static_cast<int>(index2)]);
    }
}

void Individual::swapResi(const unsigned int index1, const unsigned int index2)
{
    unsigned int count = this->getResiCount();
    if(index1 < count || index2 < count)
    {
        std::swap(_resi[static_cast<int>(index1)], _resi[static_cast<int>(index2)]);
    }
}

void Individual::swapReli(const unsigned int index1, const unsigned int index2)
{
    unsigned int count = this->getReliCount();
    if(index1 < count || index2 < count)
    {
        std::swap(_reli[static_cast<int>(index1)], _reli[static_cast<int>(index2)]);
    }
}

void Individual::removeBirth()
{
    this->removeEvent(CommonEventType::BIRT);
}

void Individual::removeChristening()
{
    this->removeEvent(CommonEventType::CHR);
}

void Individual::removeDeath()
{
    this->removeEvent(CommonEventType::DEAT);
}

void Individual::removeBurial()
{
    this->removeEvent(CommonEventType::BURI);
}

void Individual::removeOccu(const unsigned int index)
{
    if(static_cast<signed>(index) < _occu.length())
        _occu.removeAt(static_cast<signed>(index));
}

void Individual::removeEduc(const unsigned int index)
{
    if(static_cast<signed>(index) < _educ.length())
        _educ.removeAt(static_cast<signed>(index));
}

void Individual::removeResi(const unsigned int index)
{
    if(static_cast<signed>(index) < _resi.length())
        _resi.removeAt(static_cast<signed>(index));
}

void Individual::removeReli(const unsigned int index)
{
    if(static_cast<signed>(index) < _reli.length())
        _reli.removeAt(static_cast<signed>(index));
}
