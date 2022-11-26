/*!
 *  \file   subboxdate.cpp
 *  \author Eva Navratilova
 */

#include "subboxdate.h"

SubboxDate::SubboxDate(QString title, DateTypeAvailability availability, QWidget *parent)
    : Subbox (parent)
{
    _textLabel = title;
    _dateTypeAvailability = availability;

    this->fill();

    connect(&_comboDateType, SIGNAL(currentIndexChanged(int)), this, SLOT(changeDateType(int)));
    connect(&_lineDate1, &DateLineEdit::dateChanged, this, &SubboxDate::changeDate1);
    connect(&_lineDate2, &DateLineEdit::dateChanged, this, &SubboxDate::changeDate2);
}

void SubboxDate::update(DateType datetype, Date date1, Date date2)
{
    this->blockSignals(true);
    _comboDateType.setCurrentIndex(toUnderlying(datetype));
    this->changeDateType(static_cast<int>(datetype));
    if(_comboDateType.currentIndex() < 0)
        _comboDateType.setCurrentIndex(0);
    this->blockSignals(false);
    _lineDate1.setText(TextFormatter::dateToText(date1));
    _lineDate2.setText(TextFormatter::dateToText(date2));
}

int SubboxDate::maxLabelWidth() const
{
    QFont font;
    QFontMetrics fontMetrics(font);
    int width = fontMetrics.horizontalAdvance(_laDate.text());
    return width;
}

void SubboxDate::setLabelsWidth(int width)
{
    _laDate.setFixedWidth(width);
}

void SubboxDate::fill()
{
    // Set static text
    _laDate.setText(_textLabel);
    _comboDateType.addItems(QStringList()
                       << tr("Exact")
                       << tr("Estimated")
                       << tr("Before")
                       << tr("After")
                       << tr("Period")
                       << tr("Between"));

    // Adjust widgets
    QFont defaultFont;
    QFontMetrics fontMetrics(defaultFont);
    int minimumDateWidth = fontMetrics.horizontalAdvance("00.00.0000");
    _lineDate1.setMinimumWidth(minimumDateWidth + Sizer::padding());
    _lineDate2.setMinimumWidth(minimumDateWidth + Sizer::padding());

    // Set layout
    _layout.addWidget(&_laDate, 0, 0);
    _layout.addWidget(&_comboDateType, 0, 1);
    _layout.addWidget(&_lineDate1, 0, 2);
    _layout.addWidget(&_lineDate2, 0, 3);

    // Remove unwanted indexes
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(_comboDateType.model());
    if(model == nullptr)
        return;
    for(int dt = toUnderlying(DateType::SIMPLE); dt <= toUnderlying(DateType::BETWEEN); dt++)
    {
        QStandardItem *item = model->item(dt);
        switch(_dateTypeAvailability)
        {
        case DateTypeAvailability::AllAvailable:
            // Leave as is
            break;
        case DateTypeAvailability::NoPeriod:
            if(dt == toUnderlying(DateType::PERIOD))
            {
                item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
            }
            break;
        case DateTypeAvailability::OnlyPeriods:
            if(dt != toUnderlying(DateType::PERIOD) &&
               dt != toUnderlying(DateType::BEFORE) &&
               dt != toUnderlying(DateType::AFTER))
            {
                item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
            }
            else if(dt == toUnderlying(DateType::PERIOD))
            {
                _comboDateType.setCurrentIndex(dt);
            }
            break;
        case DateTypeAvailability::OnlySimple:
            _comboDateType.setHidden(true);
            _lineDate2.setHidden(true);
        }
    }
}

void SubboxDate::changeDateType(int type)
{
    DateType datetype;
    if(type >= toUnderlying(DateType::SIMPLE) && type <= toUnderlying(DateType::BETWEEN))
    {
        datetype = static_cast<DateType>(type);
        switch (datetype)
        {
        case DateType::SIMPLE:
            _lineDate2.setEnabled(false);
            break;
        case DateType::ESTIMATED:
            _lineDate2.setEnabled(false);
            break;
        case DateType::BEFORE:
            _lineDate2.setEnabled(false);
            break;
        case DateType::AFTER:
            _lineDate2.setEnabled(false);
            break;
        case DateType::PERIOD:
            _lineDate2.setEnabled(true);
            break;
        case DateType::BETWEEN:
            _lineDate2.setEnabled(true);
            break;
        default:
            break;
        }
    }
    else
    {
        datetype = DateType::EMPT;
    }
    emit(this->dateTypeChanged(datetype));
}

void SubboxDate::changeDate1(const Date date)
{
    DateType currentDatetype = static_cast<DateType>(_comboDateType.currentIndex());

    // If impercise date and Exact datetype -> change to Estimated
    // -> DEPRECATED, not a good idea
    /*bool notFullPrecisionDate = ((date.datePrecision() == DatePrecision::YEAR) || (date.datePrecision() == DatePrecision::YEAR_MONTH));
    bool isCurrentDatetypeExact = currentDatetype == DateType::SIMPLE;

    if(isCurrentDatetypeExact && notFullPrecisionDate)
    {
        currentDatetype = DateType::ESTIMATED;
    }*/

    // If empty date -> set Empty datetype
    if(date.datePrecision() == DatePrecision::EMPTY)
    {
        emit(dateTypeChanged(DateType::EMPT));
    }
    else
    {
        emit(dateTypeChanged(currentDatetype));
    }
    emit(this->date1Changed(date));
}

void SubboxDate::changeDate2(const Date date)
{
    emit(this->date2Changed(date));
}

