/*!
 *  \file   actionpersonaddman.cpp
 *  \author Eva Navratilova
 */

#include "actionpersonaddman.h"

ActionPersonAddMan::ActionPersonAddMan(Kernel &k, QWidget *parent)
    : ActionPersonAdd(k, parent)
{
    this->setIcon(QIcon(":icons/man"));
}

void ActionPersonAddMan::translate()
{
    this->setText(tr("Add Man"));
}

void ActionPersonAddMan::modifyPerson()
{
    _kernel.record()->setIndividualGender(_newPerson, Gender::MALE);
}
