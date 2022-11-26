/*!
 *  \file   actionfile.cpp
 *  \author Eva Navratilova
 */

#include "actionfile.h"

ActionFile::ActionFile(Kernel &k, QWidget *parent)
    :Action (parent), _kernel(k)
{

}

ActionFile::~ActionFile()
{

}

void ActionFile::setFileName(QString filename)
{
    _filename = filename;
}


void ActionFile::updateSettings()
{
    QSettings settings;

    if(!_filename.isEmpty())
    {
        QFileInfo info(_filename);
        QString absoluteFilePath = info.absoluteFilePath();
        QString absoluteDirPath = info.absoluteDir().path();
        QStringList files = settings.value("path/recentFiles").toStringList();
        files.removeAll(absoluteFilePath);
        files.prepend(absoluteFilePath);
        if(files.length() > 5)
            files.erase(files.begin() + 5, files.end());

//        qDebug() << absoluteDirPath;
//        qDebug() << absoluteFilePath;

        settings.setValue("path/defaultDir", absoluteDirPath);
        settings.setValue("path/recentFiles", files);
    }
}

void ActionFile::openFile()
{
    // Set wait cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    DialogProgress dialog(_kernel);
    dialog.open();

    bool saveable;
    bool isImportOk = _kernel.importFile(_filename, saveable);

    // Unset wait cursor
    QApplication::restoreOverrideCursor();
    QApplication::processEvents();

    if(isImportOk)
    {
        // Update settings must happen first -> Last open files order changed!!
        this->updateSettings();
        //emit(this->probandChanged(_kernel.record()->getIdentifierIndividualFirst()));
        if(saveable)
        {
            emit(this->fileSaveable(_filename));
        }
        else
        {
            emit(this->fileSaveable(QString()));
        }
        emit(this->fileLoaded(_filename));
    }
    else
    {
        _messageImportFailed = new MessageImportFailed(_filename);
        _messageImportFailed->exec();
        _messageImportFailed->deleteLater();
    }
}

void ActionFile::saveFile()
{
    // Set wait cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    bool isExportOk = _kernel.exportFile(_filename);

    // Unset wait cursor
    QApplication::restoreOverrideCursor();
    QApplication::processEvents();

    if(isExportOk)
    {
        // Update settings must happen first -> Last open files order changed!!
        this->updateSettings();
        emit(this->fileSaveable(_filename));
        emit(this->fileLoaded(_filename));
    }
    else
    {
        _messageExportFailed = new MessageExportFailed(_filename);
        _messageExportFailed->exec();
        _messageExportFailed->deleteLater();
    }
}
