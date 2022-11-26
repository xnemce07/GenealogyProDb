/*!
 *  \file   actiontree.cpp
 *  \author Eva Navratilova
 */

#include "actiontree.h"

ActionTree::ActionTree(TreeType type, QWidget *parent)
    : Action (parent), _type(type)
{
    QKeySequence shortcut;
    switch(_type)
    {
    case TreeType::EMPTY:
        break;
    case TreeType::ANCESTRAL_OUTLET:
        shortcut = (QKeySequence(Qt::SHIFT | Qt::Key_F10));
        break;
    case TreeType::FAMILY_TREE:
        shortcut = (QKeySequence(Qt::SHIFT | Qt::Key_F11));
        break;
    case TreeType::RELATIVES_TREE:
        shortcut = (QKeySequence(Qt::SHIFT | Qt::Key_F12));
        break;
    case TreeType::AGNAT_OUTLET:
        shortcut = (QKeySequence(Qt::SHIFT | Qt::Key_F8));
        break;
    case TreeType::KOGNAT_OUTLET:
        shortcut = (QKeySequence(Qt::SHIFT | Qt::Key_F9));
        break;
    }
    this->setShortcut(shortcut);

    this->disable();
}

void ActionTree::translate()
{
    QString text;
    switch(_type)
    {
    case TreeType::EMPTY:
        break;
    case TreeType::ANCESTRAL_OUTLET:
        text = (tr("Ancestral Outlet"));
        break;
    case TreeType::FAMILY_TREE:
        text = (tr("Family Tree"));
        break;
    case TreeType::RELATIVES_TREE:
        text = (tr("Relatives Tree"));
        break;
    case TreeType::AGNAT_OUTLET:
        text = (tr("Agnat Outlet"));
        break;
    case TreeType::KOGNAT_OUTLET:
        text = (tr("Kognat Outlet"));
        break;
    }
    this->setText(text);
}

void ActionTree::process()
{
    emit(this->drawTree(_type));
}
