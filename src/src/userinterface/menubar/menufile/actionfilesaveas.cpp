/*!
 *  \file   actionfilesaveas.cpp
 *  \author Eva Navratilova
 */

#include "actionfilesaveas.h"

ActionFileSaveAs::ActionFileSaveAs(Kernel &k)
    :ActionFile(k)
{
    this->setIcon(QIcon(":icons/save"));
    if(QKeySequence::keyBindings(QKeySequence::StandardKey::SaveAs).length() > 0)
        this->setShortcut(QKeySequence(QKeySequence::StandardKey::SaveAs));
    else
        this->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));

    this->setDisabled(true);
    //connect(this, &ActionFileSaveAs::triggered, this, &ActionFileSaveAs::process);
}

void ActionFileSaveAs::translate()
{
    this->setText(tr("Save As..."));
}

QString ActionFileSaveAs::getFileName() const
{
    return _filename;
}

void ActionFileSaveAs::process()
{
    // Initialize dialog
    _saveFileDialog = new SaveFileDialog();

    // Get filename
    QFileInfo info(_filename);
    _filename = _saveFileDialog->getSaveFileName(info.fileName());
    qDebug() << _filename;
    // Delete dialog instance
    _saveFileDialog->deleteLater();

    if(!_filename.isEmpty())
    {
        this->saveFile();
    }
}

void ActionFileSaveAs::setFileName(QString filename)
{
    this->setEnabled(true);
    this->ActionFile::setFileName(filename);
}
