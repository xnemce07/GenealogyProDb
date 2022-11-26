/*!
 *  \file   boxtree.cpp
 *  \author Eva Navratilova
 */

#include "boxtree.h"

BoxTree::BoxTree(QString title, Kernel &k, Identifier &p, QWidget *parent)
    : Box(title, BOX_CHECKABLE, k, p, parent)
{
    this->fill();
}

void BoxTree::update()
{

}

void BoxTree::fill()
{
    // Set static values
    _laTreeType.setText(tr("Tree Type"));
    _comboTreeType.addItem(tr("Ancestral Outlet"), static_cast<int>(TreeType::ANCESTRAL_OUTLET));
    _comboTreeType.addItem(tr("Agnat Outlet"), static_cast<int>(TreeType::AGNAT_OUTLET));
    _comboTreeType.addItem(tr("Kognat Outlet"), static_cast<int>(TreeType::KOGNAT_OUTLET));
    _comboTreeType.addItem(tr("Family Tree"), static_cast<int>(TreeType::FAMILY_TREE));
    _laGenerationCount.setText(tr("Generation limit"));
    _laSpousePresent.setText(tr("Include spouses"));
    _laSonsOnly.setText(tr("Include sons' families only"));


    _checkGenerationCount.setCheckState(Qt::CheckState::Unchecked);
    _spinGenerationCount.setEnabled(false);
    _checkSpousePresent.setCheckState(Qt::CheckState::Unchecked);
    _checkSonsOnly.setCheckState(Qt::CheckState::Unchecked);

    /// TODO - count max generation
    const int min = 1;
    const int max = 100;
    const int step = 1;
    const int def = 3;
    _spinGenerationCount.setRange(min, max);
    _spinGenerationCount.setSingleStep(step);
    _spinGenerationCount.setValue(def);

    // Set layout
    _layout.addWidget(&_laTreeType, 2, 0);
    _layout.addWidget(&_comboTreeType, 2, 1, 1, 2);
    _layout.addWidget(&_laGenerationCount, 3, 0);
    _layout.addWidget(&_checkGenerationCount, 3, 1);
    _layout.addWidget(&_spinGenerationCount, 3, 2);
    const int row = 4;
    _layout.addWidget(&_laSpousePresent, row, 0);
    _layout.addWidget(&_checkSpousePresent, row, 1, 1, 2);
    _layout.addWidget(&_laSonsOnly, row, 0);
    _layout.addWidget(&_checkSonsOnly, row, 1, 1, 2);

    // Remove unneeded widgets from layout
    this->remove();

    // Connect
    connect(this, &BoxTree::clicked, this, &BoxTree::setChecked);

    connect(&_comboTreeType, SIGNAL(currentIndexChanged(int)), this, SLOT(treeTypeChanged(int)));
    connect(&_checkGenerationCount, &QCheckBox::clicked, this, &BoxTree::checkGenerationClicked);
    connect(&_spinGenerationCount, SIGNAL(valueChanged(int)), this, SIGNAL(changeGenerationCount(int)));
    connect(&_checkSpousePresent, &QCheckBox::clicked, this, &BoxTree::changeSpousePresent);
    connect(&_checkSonsOnly, &QCheckBox::clicked, this, &BoxTree::changeSonsOnly);

    // Adjust
    _comboTreeType.setCurrentIndex(static_cast<int>(TreeType::ANCESTRAL_OUTLET) - 1);
}

void BoxTree::remove()
{
    _laSpousePresent.hide();
    _checkSpousePresent.hide();
    _laSonsOnly.hide();
    _checkSonsOnly.hide();
}

void BoxTree::setChecked(bool checked)
{
    Box::setChecked(checked);

    this->remove();
    TreeType type = (checked)? static_cast<TreeType>(_comboTreeType.currentData().toInt()) :
                                TreeType::EMPTY;
    this->treeTypeChanged(toUnderlying(type));
    emit(changeTreeType(type));
}

void BoxTree::treeTypeChanged(int type)
{
    remove();

    TreeType treeType = static_cast<TreeType>(type + 1);
    switch (treeType)
    {
    case TreeType::EMPTY:
    case TreeType::ANCESTRAL_OUTLET:
    case TreeType::RELATIVES_TREE:
        break;
    case TreeType::AGNAT_OUTLET:
    case TreeType::KOGNAT_OUTLET:
        _laSpousePresent.show();
        _checkSpousePresent.show();
        break;
    case TreeType::FAMILY_TREE:
        _laSonsOnly.show();
        _checkSonsOnly.show();
        break;
    }

    emit(changeTreeType(treeType));
}

void BoxTree::checkGenerationClicked(bool checked)
{
    int value = (checked)? _spinGenerationCount.value() : 0;
    _spinGenerationCount.setEnabled(checked);
    emit(this->changeGenerationCount(value));
}
