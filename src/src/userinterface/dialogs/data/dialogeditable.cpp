/*!
 *  \file   dialogeditable.cpp
 *  \author Eva Navratilova
 */

#include "dialogeditable.h"

DialogEditable::DialogEditable(const QString title, DateType &datetype, Date &date1, Date &date2, QWidget *parent)
    :  Dialog (parent), _datetype(datetype), _date1(date1), _date2(date2)
{
    this->setWindowTitle(title);

    // Initialize
    _buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    _subboxDate = new SubboxDate(tr("Date"), DateTypeAvailability::OnlyPeriods);

    _subboxDate->update(_datetype, _date1, _date2);

    // Connect
    connect(_subboxDate, &SubboxDate::dateTypeChanged, this, &DialogEditable::changeDateType);
    connect(_subboxDate, &SubboxDate::date1Changed, this, &DialogEditable::changeDate1);
    connect(_subboxDate, &SubboxDate::date2Changed, this, &DialogEditable::changeDate2);

    connect(_buttonBox, &QDialogButtonBox::accepted, this, &DialogEditable::accept);
    connect(_buttonBox, &QDialogButtonBox::rejected, this, &DialogEditable::reject);
}

DialogEditable::~DialogEditable()
{
    _subboxDate->deleteLater();
    _buttonBox->deleteLater();
}

void DialogEditable::changeDateType(const DateType datetype)
{
    _datetype = datetype;
}

void DialogEditable::changeDate1(const Date date)
{
    _date1 = date;
}

void DialogEditable::changeDate2(const Date date)
{
    _date2 = date;
}
