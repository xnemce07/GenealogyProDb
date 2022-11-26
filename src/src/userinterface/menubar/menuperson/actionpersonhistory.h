/*!
 *  \file   actionpersonhistory.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONPERSONHISTORY_H
#define ACTIONPERSONHISTORY_H

#include "../action.h"
#include "../../identifierhistory.h"

class ActionPersonHistory : public Action
{
    Q_OBJECT
protected:
    Kernel &_kernel;
    IdentifierHistory &_history;

public:
    ActionPersonHistory(Kernel &k, IdentifierHistory &h, QWidget *parent = nullptr);

private slots:
    virtual void update() = 0;
};

#endif // ACTIONPERSONHISTORY_H
