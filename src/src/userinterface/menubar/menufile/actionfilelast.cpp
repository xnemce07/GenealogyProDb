/*!
 *  \file   actionfilelast.cpp
 *  \author Eva Navratilova
 */

#include "actionfilelast.h"

ActionFileLast::ActionFileLast(Kernel &k, QString filename)
    : ActionFile (k)
{
    _filename = filename;
    QFileInfo info(_filename);
    this->setText(info.fileName());

    //connect(this, &ActionFileLast::triggered, this, &ActionFileLast::process);
}

ActionFileLast::~ActionFileLast()
{

}

void ActionFileLast::translate()
{

}

void ActionFileLast::process()
{
    // Promt to save currently open
    if(emit(this->fileLoadRequest()) == MessageBox::Accepted)
    {
        this->openFile();
    }
}
