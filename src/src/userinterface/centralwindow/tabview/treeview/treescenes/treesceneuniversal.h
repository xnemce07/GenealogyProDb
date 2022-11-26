/*!
 *  \file   treesceneuniversal.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENEUNIVERSAL_H
#define TREESCENEUNIVERSAL_H

#include "../treescenevariables.h"
#include "treesceneoutletancestral.h"
#include "treesceneoutletxnat.h"
#include "treescenefamilytree.h"
#include "treescenerelativestree.h"

class TreeSceneUniversal : public TreeSceneVariables
{
public:
    static TreeScene* sceneForType(Kernel &k, Identifier p, TreeType type);
};

#endif // TREESCENEUNIVERSAL_H
