/*!
 *  \file   eventdetail.h
 *  \author Eva Navratilova
 */

#ifndef EVENTDETAIL_H
#define EVENTDETAIL_H

#include <QString>
#include "place.h"
#include "address.h"
#include "source/sourcecitation.h"
#include "date.h"

enum class DateType
{
    EMPT = -1,  // Empty date
    SIMPLE,     // One precise date1
    ESTIMATED,  // Estimated around date1
    BEFORE,     // Estimated before date1
    AFTER,      // Estimated after date1
    PERIOD,     // From date1 to date2
    BETWEEN     // Date is between date1 and date2
};

template <typename E>
constexpr typename std::underlying_type<E>::type toUnderlying(E e) noexcept
{
    return static_cast<typename std::underlying_type<E>::type>(e);
}


/**
 * @brief
 *
 */
class EventDetail
{
private:
    QString _type; /**< Description (classification) of event */
    DateType _dateType = DateType::EMPT; /**< Type of date written in variables */
    Date _date1; /**< Date 1 of event */
    Date _date2; /**< Date 2 of event - used only for PERIOD and BETWEEN */
    Place _place; /**< Place of event */
    Address _address; /**< Address of event */
    //QString agency;
    //QString religion;
    QString _cause; /**< Event cause */
    QString _note; /**< Note to the event */
    SourceCitation _src; /**< Source of the event information */

    Identifier _priest;
    Identifier _witness1;
    Identifier _witness2;


public:
    EventDetail() = default;
    ~EventDetail() = default;

    SourceCitation constSourceCitation() const;
    Place constPlace() const;
    Address constAddress() const;

    SourceCitation& sourceCitation();
    Place& place();
    Address& address();

    // Getters
    QString getType() const;
    DateType getDateType() const;
    Date getDate1() const;
    Date getDate2() const;
    QString getCause() const;
    QString getNote() const;
    Identifier getPriest() const;
    Identifier getWitness1() const;
    Identifier getWitness2() const;

    // Setters
    void setType(const QString &t);
    void setDateType(const DateType &type);
    void setDate1(const Date &date);
    void setDate2(const Date &date);
    void setCause(const QString &c);
    void setNote(const QString &n);
    void setPriest(const Identifier &priest);
    void setWitness1(const Identifier &wittness1);
    void setWitness2(const Identifier &wittness2);
};

#endif // EVENTDETAIL_H
