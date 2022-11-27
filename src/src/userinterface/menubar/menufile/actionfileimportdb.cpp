/*!
 *  \file   actionfileimportdb.cpp
 *  \author Leopold Nemcek
 */

#include "actionfileimportdb.h"

ActionFileImportDB::ActionFileImportDB(Kernel &k)
    :ActionFile(k)
{
    this->setIcon(QIcon(":icons/open"));
    if(QKeySequence::keyBindings(QKeySequence::Open).length() > 0)
        this->setShortcut(QKeySequence::Open);
    else
        this->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));

    //connect(this, &ActionFileOpen::triggered, this, &ActionFileOpen::process);
}

ActionFileImportDB::~ActionFileImportDB()
{

}

void ActionFileImportDB::translate()
{
    this->setText(tr("Import from DB..."));
}

void ActionFileImportDB::process()
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

    /*
     * QSettings settings;
    _newPerson = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(_newPerson, settings.value("dataConstraints/autoDead").toBool());
    _kernel.record()->setIndividualNameGiven(_newPerson, "Marek :)");
    emit(this->probandChanged(_newPerson));
    */
}
