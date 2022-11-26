/*!
 *  \file   actionfile.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONFILEOPEN_H
#define ACTIONFILEOPEN_H

#include <QApplication>
#include <QSettings>
#include <QDir>
#include <QKeySequence>
#include <QFileInfo>
#include <QDebug>

#include "../action.h"
#include "../../dialogs/messageboxes/messageimportfailed.h"
#include "../../dialogs/messageboxes/messageexportfailed.h"
#include "../../dialogs/import/dialogprogress.h"

class ActionFile : public Action
{
    Q_OBJECT
private:
    MessageImportFailed* _messageImportFailed;
    MessageExportFailed* _messageExportFailed;

protected:
    Kernel &_kernel;
    QString _filename;

public:
    ActionFile(Kernel &k, QWidget *parent = nullptr);
    virtual ~ActionFile() override;

signals:
    int fileLoadRequest();
    void fileLoaded(QString filename = QString());
    void fileSaveable(QString filename);

public slots:
    void setFileName(QString filename);

protected:
    void openFile();
    void saveFile();
    void updateSettings();
};

#endif // ACTIONFILEOPEN_H
