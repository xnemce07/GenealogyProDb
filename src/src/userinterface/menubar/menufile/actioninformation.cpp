/*!
 *  \file   actioninformation.cpp
 *  \author Eva Navratilova
 */

#include "actioninformation.h"

ActionInformation::ActionInformation(Kernel &k, QWidget *parent)
    : Action(parent), _kernel(k)
{
    this->setIcon(QIcon(":icons/info"));
    this->disable();
}

void ActionInformation::translate()
{
    this->setText(tr("Information..."));
}

void ActionInformation::process()
{
    _dialog = new InformationFamilyTree(_kernel);
    if(_dialog->exec())
    {
        Identifier subm = _kernel.record()->getIdentifierSubmitterFirst();
        _kernel.record()->setSubmitterName(subm, _dialog->getAuthor());
        _kernel.record()->setSubmitterDate(subm, _dialog->getDate());
        _kernel.record()->setSubmitterNote(subm, _dialog->getDescription());
    }

    _dialog->deleteLater();
}
