/*!
 *  \file   treesceneuniversal.cpp
 *  \author Eva Navratilova
 */

#include "treesceneuniversal.h"


TreeScene *TreeSceneUniversal::sceneForType(Kernel &k, Identifier p, TreeType type)
{
    TreeScene* scene = nullptr;
    switch(type)
    {
    case TreeType::EMPTY:
        // Empty Identifier -> Empty tree
        scene = new TreeSceneOutletAncestral(k, Identifier());
        break;
    case TreeType::ANCESTRAL_OUTLET:
        scene = new TreeSceneOutletAncestral(k, p);
        break;
    case TreeType::AGNAT_OUTLET:
        scene = new TreeSceneOutletXnat(k, p, Gender::MALE);
        break;
    case TreeType::KOGNAT_OUTLET:
        scene = new TreeSceneOutletXnat(k, p, Gender::FEMALE);
        break;
    case TreeType::FAMILY_TREE:
        scene = new TreeSceneFamilyTree(k, p);
        break;
    case TreeType::RELATIVES_TREE:
        scene = new TreeSceneRelativesTree(k, p);
        break;
        /// TODO - other types
    }
    return scene;
}
