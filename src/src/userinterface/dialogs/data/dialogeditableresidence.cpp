/*!
 *  \file   dialogeditableresidnece.cpp
 *  \author Eva Navratilova
 */

#include "dialogeditableresidence.h"

DialogEditableResidence::DialogEditableResidence(const QString title, QString &city, QString &address, DateType &datetype, Date &date1, Date &date2, const QStringList &cities, const QStringList &addresses, QWidget *parent)
    : DialogEditable (title, datetype, date1, date2, parent), _city(city), _address(address)
{
    this->fill();

    _comCity = new CompleterInline(cities);
    _comAddr = new CompleterInline(addresses);

    _subboxCity->setCompleter(_comCity);
    _subboxAddress->setCompleter(_comAddr);

    connect(_subboxCity, &SubboxSimple::textChanged, this, &DialogEditableResidence::changeCity);
    connect(_subboxAddress, &SubboxSimple::textChanged, this, &DialogEditableResidence::changeAddress);
}

DialogEditableResidence::~DialogEditableResidence()
{
    _comCity->deleteLater();
    _comAddr->deleteLater();
}

void DialogEditableResidence::fill()
{
    // Initialize
    _subboxCity = new SubboxSimple(tr("City"));
    _subboxAddress = new SubboxSimple(tr("Address"));

    // Set text
    _subboxCity->update(_city);
    _subboxAddress->update(_address);

    // Set layout
    _layout.addWidget(_subboxCity, 0, 0);
    _layout.addWidget(_subboxAddress, 1, 0);
    _layout.addWidget(_subboxDate, 2, 0);
    _layout.addWidget(_buttonBox, 3, 0);

    // Adjust widgets
    this->adjustLabelsWidth();
}

int DialogEditableResidence::maxLabelWidth() const
{
    int width = _subboxDate->maxLabelWidth();
    if(width < _subboxCity->maxLabelWidth())
    {
        width = _subboxCity->maxLabelWidth();
    }
    if(width < _subboxAddress->maxLabelWidth())
    {
        width = _subboxAddress->maxLabelWidth();
    }
    return width;
}

void DialogEditableResidence::setLabelsWidth(const int width)
{
    _subboxDate->setLabelsWidth(width);
    _subboxCity->setLabelsWidth(width);
    _subboxAddress->setLabelsWidth(width);
}

void DialogEditableResidence::changeCity(const QString city)
{
    _city = city;
}

void DialogEditableResidence::changeAddress(const QString addr)
{
    _address = addr;
}
