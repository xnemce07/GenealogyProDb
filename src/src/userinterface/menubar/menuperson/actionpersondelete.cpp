/*!
 *  \file   actionpersondelete.cpp
 *  \author Eva Navratilova
 */

#include "actionpersondelete.h"

ActionPersonDelete::ActionPersonDelete(Kernel &k, Identifier p, QWidget *parent)
    : Action(parent), _kernel(k), _individualToDelete(p)
{
    this->setIcon(QIcon(":icons/delete"));
    this->disable();
}

void ActionPersonDelete::translate()
{
    this->setText(tr("Delete Person"));
}

void ActionPersonDelete::process()
{
    _dialogDelete = new MessageDelete(tr("person \"%1\"").arg(TextFormatter::getPersonLineText(_kernel, _individualToDelete)));
    if(_dialogDelete->exec())
    {
        _kernel.record()->deleteIndividual(_individualToDelete);
        emit(this->individualDeleted(_individualToDelete));
    }
}

void ActionPersonDelete::changePerson(const Identifier ref)
{
    _individualToDelete = ref;
    this->setEnabled(_kernel.record()->isIndividual(ref));
}
