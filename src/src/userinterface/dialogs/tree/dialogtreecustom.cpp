/*!
 *  \file   dialogtreecustom.cpp
 *  \author Eva Navratilova
 */

#include "dialogtreecustom.h"

DialogTreeCustom::DialogTreeCustom(Kernel &k, Identifier &p, QWidget *parent)
    : Dialog(parent), _kernel(k), _proband(p)
{
    this->fill();

    /// Connect
    // Button Box
    connect(_buttonBox, &QDialogButtonBox::accepted, this, &DialogTreeCustom::accept);
    connect(_buttonBox, &QDialogButtonBox::rejected, this, &DialogTreeCustom::reject);

    // North South
    connect(_boxTreeCrown, &BoxTree::changeTreeType, this, &DialogTreeCustom::changeNorthTreeType);
    connect(_boxTreeCrown, &BoxTree::changeGenerationCount, this, &DialogTreeCustom::changeNorthGenerationCount);
    connect(_boxTreeCrown, &BoxTree::changeSpousePresent, this, &DialogTreeCustom::changeNorthSpousePresent);
    connect(_boxTreeCrown, &BoxTree::changeSonsOnly, this, &DialogTreeCustom::changeNorthSonsOnly);

    connect(_boxTreeRoots, &BoxTree::changeTreeType, this, &DialogTreeCustom::changeSouthTreeType);
    connect(_boxTreeRoots, &BoxTree::changeGenerationCount, this, &DialogTreeCustom::changeSouthGenerationCount);
    connect(_boxTreeRoots, &BoxTree::changeSpousePresent, this, &DialogTreeCustom::changeSouthSpousePresent);
    connect(_boxTreeRoots, &BoxTree::changeSonsOnly, this, &DialogTreeCustom::changeSouthSonsOnly);
}

TreeScene *DialogTreeCustom::getTreeScene()
{
    if(this->exec())
    {
        return _scene;
    }
    return nullptr;
}

void DialogTreeCustom::fill()
{
    // Initialize
    _buttonBox = new QDialogButtonBox(QDialogButtonBox::StandardButton::Ok |
                                      QDialogButtonBox::StandardButton::Cancel);
    _boxTreeCrown = new BoxTree(tr("Tree Crown"), _kernel, _proband);
    _boxTreeRoots = new BoxTree(tr("Tree Roots"), _kernel, _proband);
    _treeView = new TreeView(_kernel, _proband);
    _scene = new TreeSceneDoubleTree(_kernel, _proband);

    // Set static text
    _laRecent.setText(tr("Recent Trees"));

    // Adjust
    _treeView->scale(0.1, 0.1);

    // Set layout
    _layout.addWidget(&_laRecent, 0, 0);
    _layout.addWidget(&_listRecent, 1, 0, 1, 2);
    _layout.addWidget(_boxTreeCrown, 2, 0);
    _layout.addWidget(_boxTreeRoots, 3, 0);
    _layout.addWidget(_treeView, 2, 1, 2, 1);
    _layout.addWidget(_buttonBox, 4, 1, Qt::AlignRight);

    _layout.setRowStretch(0, 1);
    _layout.setRowStretch(1, 1);
    _layout.setRowStretch(2, 100);
    _layout.setRowStretch(3, 100);
    _layout.setRowStretch(4, 1);

    this->updatePreview();
}

void DialogTreeCustom::changeNorthTreeType(TreeType type)
{
    _northType = type;
    this->changeTreeType(TreeDirection::NORTH, type);
}

void DialogTreeCustom::changeNorthGenerationCount(int count)
{
    _northMaxGen = count;
    this->changeGenerationCount(TreeDirection::NORTH, count);
}

void DialogTreeCustom::changeNorthSpousePresent(bool present)
{
    _northSpousePresent = present;
    this->changeSpousePresent(TreeDirection::NORTH, present);
}

void DialogTreeCustom::changeNorthSonsOnly(bool sonsOnly)
{
    _northSonsOnly = sonsOnly;
    this->changeSonsOnly(TreeDirection::NORTH, sonsOnly);
}

void DialogTreeCustom::changeSouthTreeType(TreeType type)
{
    _southType = type;
    this->changeTreeType(TreeDirection::SOUTH, type);
}

void DialogTreeCustom::changeSouthGenerationCount(int count)
{
    _southMaxGen = count;
    this->changeGenerationCount(TreeDirection::SOUTH, count);
}

void DialogTreeCustom::changeSouthSpousePresent(bool present)
{
    _southSpousePresent = present;
    this->changeSpousePresent(TreeDirection::SOUTH, present);
}

void DialogTreeCustom::changeSouthSonsOnly(bool sonsOnly)
{
    _southSonsOnly = sonsOnly;
    this->changeSonsOnly(TreeDirection::SOUTH, sonsOnly);
}

void DialogTreeCustom::changeTreeType(TreeDirection dir, TreeType type)
{
    _scene->changeTreeType(dir, type);

    /// TODO - STILL ONLY NORTH!!!
    // Adjust
    switch(type)
    {
    case TreeType::EMPTY:
    case TreeType::ANCESTRAL_OUTLET:
    case TreeType::RELATIVES_TREE:
        // Update
        this->updatePreview();
        break;
    case TreeType::AGNAT_OUTLET:
    case TreeType::KOGNAT_OUTLET:
        this->changeSpousePresent(dir, _northSpousePresent);
        break;
    case TreeType::FAMILY_TREE:
        this->changeSonsOnly(dir, _northSonsOnly);
    }

}

void DialogTreeCustom::changeGenerationCount(TreeDirection dir, int count)
{
    _scene->changeMaximumGeneration(dir, count);
    this->updatePreview();
}

void DialogTreeCustom::changeSpousePresent(TreeDirection dir, bool present)
{
    _scene->changeSpousePresent(dir, present);
    this->updatePreview();
}

void DialogTreeCustom::changeSonsOnly(TreeDirection dir, bool sonsOnly)
{
    _scene->changeSonsOnly(dir, sonsOnly);
    this->updatePreview();
}

void DialogTreeCustom::updatePreview()
{
    _treeView->drawTree(_scene);
}
