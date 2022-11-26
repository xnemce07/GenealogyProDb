/*!
 *  \file   actioninformation.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONINFORMATION_H
#define ACTIONINFORMATION_H

#include "../action.h"
#include "../../dialogs/data/informationfamilytree.h"

class ActionInformation : public Action
{
    Q_OBJECT
private:
    Kernel &_kernel;

    InformationFamilyTree* _dialog;

public:
    ActionInformation(Kernel &k, QWidget *parent = nullptr);

    void translate() override;

    void process() override;
};

#endif // ACTIONINFORMATION_H
