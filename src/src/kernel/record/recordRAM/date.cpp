/*!
 *  \file   date.cpp
 *  \author Eva Navratilova
 */

#include "date.h"

Date::Date()
    : QDate ()
{
    _precision = DatePrecision::EMPTY;
}

Date::Date(QDate qd)
{
    this->setDate(qd);
}

Date::Date(int y, int m, int d)
{
    this->setDate(y, m, d);
}

bool Date::setDate(QDate qd)
{
    this->setDate(qd.year(), qd.month(), qd.day());
    if(qd.isValid())
    {
        _precision = DatePrecision::FULL;
    }
    else
    {
        _precision = DatePrecision::EMPTY;
    }
    return this->isValid();
}

bool Date::setDate(int year, int month, int day)
{
    if(year <= 0 || month < 0 || day < 0)
    {
        _precision = DatePrecision::EMPTY;
    }
    else if(month == 0)
    {
        _precision = DatePrecision::YEAR;
        month = 1;
        day = 1;
    }
    else if(day == 0)
    {
        _precision = DatePrecision::YEAR_MONTH;
        day = 1;
    }
    else
    {
        _precision = DatePrecision::FULL;
    }

    QDate::setDate(year, month, day);

    return this->isValid();
}

DatePrecision Date::datePrecision() const
{
    return _precision;
}

QString Date::toString(const QString &format) const
{
    return QDate::toString(format);
}

Date Date::currentDate()
{
    QDate qd = QDate::currentDate();
    Date d(qd);
    return d;
}

Date Date::fromJulianDay(qint64 jd)
{
    QDate qd = QDate::fromJulianDay(jd);
    Date d(qd);
    return d;
}

Date Date::fromString(const QString &string, const QString formatFull, const QString formatYM, const QString formatY)
{
    /// TODO - not working for non-4-digit year
    Date d;
    QString copyString = string;
    QDate qd;
    if((qd = QDate::fromString(copyString, formatFull)).isValid())
    {
        d.setDate(qd);
    }
    else if((qd = QDate::fromString(copyString, formatYM)).isValid())
    {
        d.setDate(qd.year(), qd.month());
    }
    else if((qd = QDate::fromString(copyString, formatY)).isValid())
    {
        d.setDate(qd.year());
    }
    return d;
}

bool Date::isValid() const
{
    bool precisionOK = (_precision != DatePrecision::EMPTY);
    return precisionOK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////



Age::Age(Date birth, Date death)
{
    // THERE IS NO YEAR 0 IN QDATE
    if(birth == Date() || death == Date())
    {
        _valid = false;
    }
    else
    {
        _valid = true;

        qint64 daysBetween = death.toJulianDay() - birth.toJulianDay();
        _date = Date::fromJulianDay(daysBetween);
        QDate nullDate(1,1,1);         // QDate(0,0,0) would result in invalid date
        qint64 daysTo0 = nullDate.toJulianDay();
        _date  = _date.addDays(daysTo0);
    }
}

bool Age::operator==(const Age &r) const
{
    return this->daysBetween() == r.daysBetween();
}

bool Age::operator<(const Age &r) const
{
    return this->daysBetween() < r.daysBetween();
}

bool Age::isValid() const
{
    return _date.isValid() && _valid;
}

int Age::days() const
{
    return _date.day();
}

int Age::months() const
{
    return _date.month();
}

int Age::years() const
{
    return _date.year() - 1;
}

int Age::daysBetween() const
{
    long long int daysBegin   = QDate(1,1,1).toJulianDay();
    long long int daysBetween = _date.toJulianDay();
    return static_cast<int>(daysBetween - daysBegin);
}


