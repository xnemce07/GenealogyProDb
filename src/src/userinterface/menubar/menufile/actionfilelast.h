/*!
 *  \file   actionfilelast.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONFILELAST_H
#define ACTIONFILELAST_H

#include <QFileInfo>

#include "actionfile.h"

class ActionFileLast : public ActionFile
{
    Q_OBJECT
public:
    ActionFileLast(Kernel &k, QString filename);
    ~ActionFileLast() override;

    void translate() override;

private slots:
    void process() override;
};

#endif // ACTIONFILELAST_H
