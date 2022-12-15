/*!
 *  \file   actionpersondbimport.h
 *  \author Leopold Nemcek
 */

#ifndef ACTIONPERSONDBIMPORT_H
#define ACTIONPERSONDBIMPORT_H

#include <QSettings>
#include <QtSql>

#include "../action.h"

class ActionPersonDbImport : public Action
{
    Q_OBJECT
protected:
    Kernel &_kernel;
    Identifier _newPerson;

public:
    ActionPersonDbImport(Kernel &k, QWidget *parent = nullptr);
    void translate() override;

private:
    void process() override;
    void modifyPerson();
};

#endif // ACTIONPERSONDBIMPORT_H
