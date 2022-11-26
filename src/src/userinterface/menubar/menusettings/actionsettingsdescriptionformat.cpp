/*!
 *  \file   actionsettingsdescriptionformat.cpp
 *  \author Eva Navratilova
 */

#include "actionsettingsdescriptionformat.h"

ActionSettingsDescriptionFormat::ActionSettingsDescriptionFormat(Kernel &k, Identifier &r, FormatableText f, QWidget *parent)
    : Action(parent), _kernel(k), _ref(r), _formattable(f)
{

}

void ActionSettingsDescriptionFormat::translate()
{
    QString text;
    switch(_formattable)
    {
    case FormatableText::INDIVIDUAL:
        text = tr("Person...");
        break;
    case FormatableText::TREE_INDIVIDUAL:
        text = tr("Tree Cell Person...");
        break;
    case FormatableText::TREE_MARRIAGE:
        text = tr("Tree Cell Marriage...");
        break;
    case FormatableText::SOURCE:
        text = tr("Source...");
        break;
    case FormatableText::SOURCE_CITATION:
        text = tr("Source Citation...");
        break;
    case FormatableText::EMPTY:
        break;
    }
    this->setText(text);
}

void ActionSettingsDescriptionFormat::process()
{
    _dialog = new DialogSettingsDescriptionFormat(_kernel, _ref, _formattable);
    int result = _dialog->exec();

    if(result == Dialog::Accepted)
    {
        switch(_formattable)
        {
        case FormatableText::INDIVIDUAL:
        case FormatableText::SOURCE_CITATION:
            emit(this->probandChanged(_ref));
            break;
        case FormatableText::SOURCE:
            emit(this->sourceChanged(_ref));
            break;
        default:
            break;
        }
    }
}
