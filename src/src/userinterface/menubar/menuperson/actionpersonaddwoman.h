/*!
 *  \file   actionpersonaddwoman.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONPERSONADDWOMAN_H
#define ACTIONPERSONADDWOMAN_H

#include "actionpersonadd.h"

class ActionPersonAddWoman : public ActionPersonAdd
{
    Q_OBJECT
public:
    ActionPersonAddWoman(Kernel &k, QWidget *parent = nullptr);

    void translate() override;

private:
    void modifyPerson() override;

};

#endif // ACTIONPERSONADDWOMAN_H
