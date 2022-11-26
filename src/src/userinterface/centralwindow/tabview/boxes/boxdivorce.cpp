/*!
 *  \file   boxdivorce.cpp
 *  \author Eva Navratilova
 */

#include "boxdivorce.h"

BoxDivorce::BoxDivorce(QString title, Kernel &k, Identifier &p, Identifier &f, QWidget *parent)
    :Box(title, BOX_CHECKABLE, k, p, parent), _family(f)
{
    this->fill();

    connect(this, &BoxDivorce::clicked, this, &BoxDivorce::changeDivorceState);
    connect(_subboxDate, &SubboxDate::dateTypeChanged, this, &BoxDivorce::changeDatetype);
    connect(_subboxDate, &SubboxDate::date1Changed, this, &BoxDivorce::changeDate1);
    connect(_subboxDate, &SubboxDate::date2Changed, this, &BoxDivorce::changeDate2);
}

void BoxDivorce::update()
{
    // Initialize values
    bool divorced = _kernel.record()->isFamilyDivorced(_family);
    DateType datetype = _kernel.record()->getFamilyDivorceDateType(_family);
    Date date1 = _kernel.record()->getFamilyDivorceDate1(_family);
    Date date2 = _kernel.record()->getFamilyDivorceDate2(_family);

    // Set new values
    this->setChecked(divorced);
    _subboxDate->update(datetype, date1, date2);
}

void BoxDivorce::fill()
{
    // Initialize
    _subboxDate = new SubboxDate(tr("Divorce Date"), DateTypeAvailability::NoPeriod, this);
    _spacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);

    // Set static values

    // Set layout
    _layout.addWidget(_subboxDate, 0, 0);
    _layout.addItem(_spacer, 1, 0);
}

void BoxDivorce::changeDivorceState(bool checked)
{
    _kernel.record()->setFamilyDivorced(_family, checked);
}

void BoxDivorce::changeDatetype(const DateType datetype)
{
    _kernel.record()->setFamilyDivorceDateType(_family, datetype);
}

void BoxDivorce::changeDate1(const Date date)
{
    _kernel.record()->setFamilyDivorceDate1(_family, date);
}

void BoxDivorce::changeDate2(const Date date)
{
    _kernel.record()->setFamilyDivorceDate2(_family, date);
}
