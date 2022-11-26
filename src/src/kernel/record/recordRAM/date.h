/*!
 *  \file   date.h
 *  \author Eva Navratilova
 */

#ifndef DATE_H
#define DATE_H

#include <QDebug>
#include <QDate>

enum class DatePrecision
{
    EMPTY = 0,
    YEAR,
    YEAR_MONTH,
    FULL
};


class Date : public QDate
{
private:
    DatePrecision _precision = DatePrecision::EMPTY;

public:
    Date();
    Date(QDate qd);
    Date(int y, int m=0, int d=0);

    bool setDate(QDate qd);
    bool setDate(int year, int month=0, int day=0);

    DatePrecision datePrecision() const;

    QString toString(const QString &format) const;
    QString toString(QStringView format) const = delete;

    static Date currentDate();
    static Date fromJulianDay(qint64 jd);
    static Date fromString(const QString &string, Qt::DateFormat format = Qt::TextDate) = delete;
    static Date fromString(const QString &string, const QString &format) = delete;
    static Date fromString(const QString &string, const QString formatFull, const QString formatYM, const QString formatY);
    bool isValid() const;

};



class Age
{
private:
    Date _date;
    bool _valid;

public:
    Age() = default;
    Age(Date birth, Date death);

    bool operator==(const Age& r) const;
    bool operator<(const Age& r) const;

    bool isValid() const;

    int days() const;
    int months() const;
    int years() const;

    int daysBetween() const;
};

#endif // DATE_H
