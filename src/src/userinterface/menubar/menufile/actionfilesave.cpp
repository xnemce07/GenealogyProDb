/*!
 *  \file   actionfilesave.cpp
 *  \author Eva Navratilova
 */

#include "actionfilesave.h"

ActionFileSave::ActionFileSave(Kernel &k)
    : ActionFile (k)
{
    this->setIcon(QIcon(":icons/save"));
    if(QKeySequence::keyBindings(QKeySequence::Save).length() > 0)
        this->setShortcut(QKeySequence::Save);
    else
        this->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));

    this->setDisabled(true);
    //connect(this, &ActionFileSave::triggered, this, &ActionFileSave::process);
}

void ActionFileSave::translate()
{
    this->setText(tr("Save"));
}

void ActionFileSave::process()
{
    if(!_filename.isEmpty())
    {
        this->saveFile();
    }
}

void ActionFileSave::setFileName(QString filename)
{
    this->setDisabled(filename.isEmpty());
    this->ActionFile::setFileName(filename);
}
