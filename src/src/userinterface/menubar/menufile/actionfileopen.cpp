/*!
 *  \file   actionfileopen.cpp
 *  \author Eva Navratilova
 */

#include "actionfileopen.h"

ActionFileOpen::ActionFileOpen(Kernel &k)
    :ActionFile(k)
{
    this->setIcon(QIcon(":icons/open"));
    if(QKeySequence::keyBindings(QKeySequence::Open).length() > 0)
        this->setShortcut(QKeySequence::Open);
    else
        this->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));

    //connect(this, &ActionFileOpen::triggered, this, &ActionFileOpen::process);
}

ActionFileOpen::~ActionFileOpen()
{

}

void ActionFileOpen::translate()
{
    this->setText(tr("Open..."));
}

void ActionFileOpen::process()
{
    // Promt to save currently open
    if(emit(this->fileLoadRequest()) == MessageBox::Accepted)
    {
        // Initialize dialog
        _openFileDialog = new OpenFileDialog();

        // Get filename
        _filename = _openFileDialog->getOpenFileName();
        // Delete dialog instance
        _openFileDialog->deleteLater();

        if(!_filename.isEmpty())
        {
            this->openFile();
        }
    }
}
