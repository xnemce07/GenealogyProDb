/*!
 *  \file   actionpersonaddwoman.cpp
 *  \author Eva Navratilova
 */

#include "actionpersonaddwoman.h"

ActionPersonAddWoman::ActionPersonAddWoman(Kernel &k, QWidget *parent)
    : ActionPersonAdd (k, parent)
{
    this->setIcon(QIcon(":icons/woman"));
}

void ActionPersonAddWoman::translate()
{
    this->setText(tr("Add Woman"));
}

void ActionPersonAddWoman::modifyPerson()
{
    _kernel.record()->setIndividualGender(_newPerson, Gender::FEMALE);
}
