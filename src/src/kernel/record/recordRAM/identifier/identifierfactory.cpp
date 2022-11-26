/*!
 *  \file   identifierfactory.cpp
 *  \author Eva Navratilova
 */

#include "identifierfactory.h"
#include "../../recordram.h"


IdentifierFactory::IdentifierFactory(IdentifierType t) : _type(t)
{
    this->reset();
}

Identifier IdentifierFactory::newIdentifier()
{
    Identifier ref;
    if(this->_freeNumbers.isEmpty())
    {
        ref = Identifier(this->_type, this->_nextNumber++);
    }
    else
    {
        ref = Identifier(this->_type, this->_freeNumbers.first());
        this->_freeNumbers.removeFirst();
    }
    return ref;
}

Identifier IdentifierFactory::importIdentifier(Identifier ref)
{
    Identifier newRef;
    unsigned long long int refNumber = ref.getNumber();
    if(refNumber == this->_nextNumber)
    {
        newRef = Identifier(this->_type, this->_nextNumber++);
    }
    else if(refNumber > this->_nextNumber)
    {
        for(unsigned long long int i = this->_nextNumber; i < refNumber; i++)
        {
            this->_freeNumbers.push_back(i);
        }
        newRef = Identifier(this->_type, refNumber);
        this->_nextNumber = refNumber + 1;
    }
    // Id number should be in _freeNumbers, else already taken!!
    else if(this->_freeNumbers.contains(refNumber))
    {
        this->_freeNumbers.removeAll(refNumber);
        newRef = Identifier(this->_type, refNumber);
    }
    else // Number was not in _freeNumbers -> Number is already taken (was just generated) !!!!
    {
        newRef = ref;
    }
    return newRef;
}

void IdentifierFactory::freeIdentifier(Identifier ref)
{
    unsigned long long int number = ref.getNumber();
    if(number == this->_nextNumber - 1)
    {
        this->_nextNumber--;

        // Remove all pending freeNumbers, that might have been made last now
        while(_freeNumbers.contains(_nextNumber - 1))
        {
            _nextNumber--;
            _freeNumbers.removeAll(_nextNumber);
        }
    }
    else
    {
        this->_freeNumbers.push_back(number);
    }
}

Identifier IdentifierFactory::firstIdentifier() const
{
    // Invalid Identifier constructor
    Identifier ref;
    // If not 0 Identifiers generated
    if(this->_nextNumber > 0)
    {
        unsigned long long int first = 0;
        while(_freeNumbers.contains(first))
        {
            first++;
        }
        ref = Identifier(_type, first);
    }
    return ref;
}

Identifier IdentifierFactory::lastIdentifier() const
{
    // Invalid Identifier constructor
    Identifier ref;
    unsigned long long int last;
    // If not 0 Identifiers generated
    if(this->_nextNumber > 0)
    {
        last = _nextNumber;
        ref = Identifier(_type, last);
    }
    return ref;
}

Identifier IdentifierFactory::nextIdentifier(Identifier &ref) const
{
    while(_freeNumbers.contains((++ref).getNumber()))
    {
        if(this->lastIdentifier() <= ref)
        {
            ref = this->lastIdentifier();
            break;
        }
    }
    return ref;
}

void IdentifierFactory::reset()
{
    _nextNumber = 0;
    _freeNumbers.clear();
}

