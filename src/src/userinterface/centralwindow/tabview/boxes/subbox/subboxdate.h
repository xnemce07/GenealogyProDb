/*!
 *  \file   subboxdate.h
 *  \author Eva Navratilova
 */

#ifndef SUBBOXDATE_H
#define SUBBOXDATE_H

#include <QLabel>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QLineEdit>
#include <QComboBox>
#include <QFontMetrics>

#include "subbox.h"
#include "userinterface/objects/datelineedit.h"

enum class DateTypeAvailability
{
    AllAvailable = 0,
    NoPeriod,           // For birth date, etc
    OnlyPeriods,        // For jobs, etc
    OnlySimple
};


class SubboxDate : public Subbox
{
    Q_OBJECT
private:
    QString _textLabel;
    DateTypeAvailability _dateTypeAvailability;

    Label _laDate;

    DateLineEdit _lineDate1;
    DateLineEdit _lineDate2;
    QComboBox _comboDateType;

public:
    explicit SubboxDate(QString title, DateTypeAvailability availability, QWidget *parent = nullptr);

    void update(DateType datetype, Date date1, Date date2);
    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

private:
    void fill() override;

signals:
    void dateTypeChanged(const DateType datetype);
    void date1Changed(const Date date);
    void date2Changed(const Date date);

public slots:
    void changeDateType(int type);
    void changeDate1(const Date date);
    void changeDate2(const Date date);
};

#endif // SUBBOXDATE_H
