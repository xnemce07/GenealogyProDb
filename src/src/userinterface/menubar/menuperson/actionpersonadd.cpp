/*!
 *  \file   actionpersonadd.cpp
 *  \author Eva Navratilova
 */

#include "actionpersonadd.h"

ActionPersonAdd::ActionPersonAdd(Kernel &k, QWidget *parent)
    : Action (parent), _kernel(k)
{
    //connect(this, &ActionPersonAdd::triggered, this, &ActionPersonAdd::process);
    this->disable();
}

void ActionPersonAdd::process()
{
    QSettings settings;
    _newPerson = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(_newPerson, settings.value("dataConstraints/autoDead").toBool());
    this->modifyPerson();
    emit(this->probandChanged(_newPerson));
}
