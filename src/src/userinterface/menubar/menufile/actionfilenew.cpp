/*!
 *  \file   actionfilenew.cpp
 *  \author Eva Navratilova
 */

#include "actionfilenew.h"

ActionFileNew::ActionFileNew(Kernel &k)
    : ActionFile (k)
{
    this->setIcon(QIcon(":icons/new"));
    if(QKeySequence::keyBindings(QKeySequence::New).length() > 0)
        this->setShortcut(QKeySequence::New);
    else
        this->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));

    //connect(this, &ActionFileNew::triggered, this, &ActionFileNew::process);
}

ActionFileNew::~ActionFileNew()
{

}

void ActionFileNew::translate()
{
    this->setText(tr("New"));
}

void ActionFileNew::process()
{
    // Promt to save currently open
    if(emit(this->fileLoadRequest()) == MessageBox::Accepted)
    {
        DialogProgress dialog(_kernel);
        dialog.open();

        _kernel.newProject();
        emit(this->probandChanged(_kernel.record()->getIdentifierIndividualFirst()));
        emit(this->fileLoaded());
        emit(this->fileSaveable(QString()));
    }
}
