/*!
 *  \file   actionpersonadd.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONPERSONADD_H
#define ACTIONPERSONADD_H

#include <QSettings>

#include "../action.h"

class ActionPersonAdd : public Action
{
    Q_OBJECT
protected:
    Kernel &_kernel;
    Identifier _newPerson;

public:
    ActionPersonAdd(Kernel &k, QWidget *parent = nullptr);

private:
    void process() override;
    virtual void modifyPerson() = 0;
};

#endif // ACTIONPERSONADD_H
