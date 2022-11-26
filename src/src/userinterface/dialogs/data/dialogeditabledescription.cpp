/*!
 *  \file   dialogeditabledescription.cpp
 *  \author Eva Navratilova
 */

#include "dialogeditabledescription.h"

DialogEditableDescription::DialogEditableDescription(const QString title, QString &description, DateType &datetype, Date &date1, Date &date2, const QStringList &descriptions, QWidget *parent)
    : DialogEditable (title, datetype, date1, date2, parent), _description(description)
{
    this->fill();

    _comDescription = new CompleterInline(descriptions);

    _subboxDescription->setCompleter(_comDescription);

    connect(_subboxDescription, &SubboxSimple::textChanged, this, &DialogEditableDescription::changeDescription);
    //connect(_comDescription, SIGNAL(activated()), this, SLOT(changeDescription()));
}

void DialogEditableDescription::fill()
{
    // Initialize
    _subboxDescription = new SubboxSimple(tr("Description"));

    // Set text
    _subboxDescription->update(_description);

    // Set layout
    _layout.addWidget(_subboxDescription, 0, 0);
    _layout.addWidget(_subboxDate, 1, 0);
    _layout.addWidget(_buttonBox, 2, 0);

    // Adjust widgets
    this->adjustLabelsWidth();
}

int DialogEditableDescription::maxLabelWidth() const
{
    int width = _subboxDate->maxLabelWidth();
    if(width < _subboxDescription->maxLabelWidth())
    {
        width = _subboxDescription->maxLabelWidth();
    }
    return width;
}

void DialogEditableDescription::setLabelsWidth(const int width)
{
    _subboxDate->setLabelsWidth(width);
    _subboxDescription->setLabelsWidth(width);
}

void DialogEditableDescription::changeDescription(const QString& descr)
{
    _description = descr;
}
