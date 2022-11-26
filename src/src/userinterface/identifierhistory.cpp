/*!
 *  \file   identifierhistory.cpp
 *  \author Eva Navratilova
 */

#include "identifierhistory.h"

IdentifierHistory::IdentifierHistory(int maxLength)
    : _maxLength(maxLength)
{
    _index = 0;
}

IdentifierHistory::~IdentifierHistory()
{

}

void IdentifierHistory::reset()
{
    _index = 0;
    _identifiers.clear();
}

int IdentifierHistory::currentIndex() const
{
    return _index - 1;
}

bool IdentifierHistory::isPreviousAvailable() const
{
    return (0 < currentIndex() && currentIndex() < _identifiers.length());
}

bool IdentifierHistory::isNextAvailable() const
{
    return (0 <= currentIndex() && currentIndex() < (_identifiers.length() - 1));
}

void IdentifierHistory::previous()
{
    if(isPreviousAvailable())
    {
        Identifier ref;
        ref = _identifiers.at(currentIndex() - 1);
        _index--;
        emit(this->probandChanged(ref));
        emit(this->updated());
    }
}

void IdentifierHistory::next()
{
    if(isNextAvailable())
    {
        Identifier ref;
        ref = _identifiers.at(currentIndex() + 1);
        _index++;
        emit(this->probandChanged(ref));
        emit(this->updated());
    }
}

void IdentifierHistory::update(Identifier ref)
{
    if(ref.isValid())
    {
        // Return if same as previous
        if(0 <= currentIndex() &&
           currentIndex() < _identifiers.length() &&
           _identifiers.at(currentIndex()) == ref)
        {
            return;
        }

        // Insert
        _identifiers.insert(_index++, ref);

        // If next history available -> remove it
        while(currentIndex() < _identifiers.length() - 1)
        {
            auto beginErase = _identifiers.begin() + _index;
            auto endErase = _identifiers.end();
            _identifiers.erase(beginErase, endErase);
        }

        // If history is longer than maximum length -> crop it
        while(_identifiers.length() > _maxLength)
        {
            _identifiers.removeFirst();
            _index--;
        }

        emit(this->updated());
    }
}

void IdentifierHistory::remove(Identifier ref)
{
    int position;
    // Remove and correct position
    while((position = _identifiers.indexOf(ref)) != -1)
    {
        if(position <= currentIndex())
        {
            _index--;
        }
        _identifiers.removeAt(position);
    }

    // Get new ref
    Identifier newRef;
    if(0 <= currentIndex() && currentIndex() < _identifiers.size())
    {
        newRef = _identifiers.at(currentIndex());
    }
    emit(this->probandChanged(newRef));
    emit(this->updated());
}
