/*!
 *  \file   actionpersonhistory.cpp
 *  \author Eva Navratilova
 */

#include "actionpersonhistory.h"

ActionPersonHistory::ActionPersonHistory(Kernel &k, IdentifierHistory &h, QWidget *parent)
    : Action(parent), _kernel(k), _history(h)
{
    connect(&_history, &IdentifierHistory::probandChanged, this, &ActionPersonHistory::probandChanged);

    connect(&_history, &IdentifierHistory::updated, this, &ActionPersonHistory::update);
}
