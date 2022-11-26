/*!
 *  \file   treesceneoutletxnat.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENEOUTLETXNAT_H
#define TREESCENEOUTLETXNAT_H

#include "treesceneoutletancestral.h"

class TreeSceneOutletXnat : public TreeSceneOutletAncestral
{
    Q_OBJECT
private:
    Gender _genderToDraw;
    bool _drawSpouse = false;

public:
    TreeSceneOutletXnat(Kernel &k, Identifier p, Gender g, QObject *parent = nullptr);
    virtual ~TreeSceneOutletXnat() override = default;

    void setSpousePresent(bool present);

    // Tree draw
    TreeItemPerson* initNodeTree(const Identifier indi, const Generation gen) override;
};

#endif // TREESCENEOUTLETXNAT_H
