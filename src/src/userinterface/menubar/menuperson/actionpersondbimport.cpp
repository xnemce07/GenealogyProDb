/*!
 *  \file   actionpersondbimport.cpp
 *  \author Leopold Nemcek
 */

#include "actionpersondbimport.h"

ActionPersonDbImport::ActionPersonDbImport(Kernel &k, QWidget *parent)
    : Action (parent), _kernel(k)
{
    //connect(this, &ActionPersonAdd::triggered, this, &ActionPersonAdd::process);
    this->disable();
}

void ActionPersonDbImport::process()
{
    QSettings settings;
    _newPerson = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(_newPerson, settings.value("dataConstraints/autoDead").toBool());
    this->modifyPerson();
    emit(this->probandChanged(_newPerson));
}


void ActionPersonDbImport::modifyPerson()
{
    _kernel.record()->setIndividualNameGiven(_newPerson, "Mark");
}

void ActionPersonDbImport::translate()
{
    this->setText(tr("Import from database..."));
}
