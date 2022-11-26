/*!
 *  \file   actionfileopen.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONFILEIMPORT_H
#define ACTIONFILEIMPORT_H

#include "actionfile.h"
#include "../../dialogs/file/openfiledialog.h"

class ActionFileOpen : public ActionFile
{
    Q_OBJECT
private:
    OpenFileDialog* _openFileDialog;

public:
    ActionFileOpen(Kernel &k);
    ~ActionFileOpen() override;

    void translate() override;

private slots:
    void process() override;
};

#endif // ACTIONFILEIMPORT_H
