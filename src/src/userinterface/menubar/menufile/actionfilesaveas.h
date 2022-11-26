/*!
 *  \file   actionfilesaveas.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONFILESAVEAS_H
#define ACTIONFILESAVEAS_H

#include <QFileInfo>

#include "actionfile.h"
#include "../../dialogs/file/savefiledialog.h"

class ActionFileSaveAs : public ActionFile
{
    Q_OBJECT
private:
    SaveFileDialog* _saveFileDialog;

public:
    ActionFileSaveAs(Kernel &k);

    void translate() override;
    QString getFileName() const;

private slots:
    void process() override;

public slots:
    void setFileName(QString filename);
};

#endif // ACTIONFILESAVEAS_H
