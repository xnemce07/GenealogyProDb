/*!
 *  \file   actionfileimportdb.h
 *  \author Leopold Nemcek
 */

#ifndef ACTIONFILEIMPORTDB_H
#define ACTIONFILEIMPORTDB_H

#include "actionfile.h"
#include "../../dialogs/file/openfiledialog.h"

class ActionFileImportDB : public ActionFile
{
    Q_OBJECT
private:
    OpenFileDialog* _openFileDialog;
    //Identifier _newPerson;

public:
    ActionFileImportDB(Kernel &k);
    ~ActionFileImportDB() override;

    void translate() override;

private slots:
    void process() override;
};

#endif // ACTIONFILEIMPORTDB_H
