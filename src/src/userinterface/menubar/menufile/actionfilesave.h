/*!
 *  \file   actionfilesave.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONFILESAVE_H
#define ACTIONFILESAVE_H

#include "actionfile.h"

class ActionFileSave : public ActionFile
{
    Q_OBJECT
public:
    ActionFileSave(Kernel &k);

    void translate() override;

private slots:
    void process() override;

public slots:
    void setFileName(QString filename);
};

#endif // ACTIONFILESAVE_H
