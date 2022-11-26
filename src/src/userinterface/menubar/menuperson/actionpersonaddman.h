/*!
 *  \file   actionpersonaddman.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONPERSONADDMAN_H
#define ACTIONPERSONADDMAN_H

#include "actionpersonadd.h"

class ActionPersonAddMan : public ActionPersonAdd
{
    Q_OBJECT
public:
    ActionPersonAddMan(Kernel &k, QWidget *parent = nullptr);

    void translate() override;

private:
    void modifyPerson() override;
};

#endif // ACTIONPERSONADDMAN_H
