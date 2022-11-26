/*!
 *  \file   eventrecorded.h
 *  \author Eva Navratilova
 */

#ifndef EVENTRECORDED_H
#define EVENTRECORDED_H

#include <QString>

#include "../event/commoneventstructure.h"
#include "../date.h"


class EventRecorded
{
private:
    CommonEventType _eventAttrType;
    Date _date1;
    Date _date2;
    QString _placName;
    QString _page1;
    QString _page2;
    QString _url;

public:
    // Constructors
    EventRecorded();
    EventRecorded(CommonEventType t) ;

    // Copy constructors
    EventRecorded(const EventRecorded&) = default;
    EventRecorded& operator=(const EventRecorded&) = default;

    // Destructor
    ~EventRecorded() = default;

    ///////////////////////////////////////////////////////////////////////////
    /// Validators
    ///////////////////////////////////////////////////////////////////////////

    bool isDateContained(const Date date) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Getters
    ///////////////////////////////////////////////////////////////////////////

    CommonEventType getEventType() const;
    Date getDateFrom() const;
    Date getDateTo() const;
    QString getPlacName() const;
    QString getPage1() const;
    QString getPage2() const;
    QString getUrl() const;


    ///////////////////////////////////////////////////////////////////////////
    /// Setters
    ///////////////////////////////////////////////////////////////////////////

    void setDateFrom(const Date &from);
    void setDateTo(const Date &to);
    void setPlaceName(const QString &plac);
    void setPage1(const QString &page);
    void setPage2(const QString &page);
    void setUrl(const QString &url);

};


#endif // EVENTRECORDED_H
