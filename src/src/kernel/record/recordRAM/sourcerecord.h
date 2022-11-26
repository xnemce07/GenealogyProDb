/*!
 *  \file   sourcerecord.h
 *  \author Eva Navratilova
 */

#ifndef SOURCERECORD_H
#define SOURCERECORD_H

#include <QHash>
#include <QString>
#include <QVector>

#include "primitives.h"
#include "identifier.h"
#include "source/eventrecorded.h"
#include "date.h"


class SourceRecord
{
    friend class RecordRAM;
private:
    Identifier _ref;

    /// Data
    QVector<EventRecorded> _birt;
    QVector<EventRecorded> _marr;
    QVector<EventRecorded> _deat;

    QVector<EventRecorded> _othr; /**< Stores no data */
    QString _auth;  /**< Author stores Archive name */
    QString _titl;  /**< Title stores signature number */
    QString _publ;  /**< Publication stores place of origin */
    // Abbreviation not supported
    // Text from source not supported

    /// New features added according to geni software: https://wiki.geni.com/index.php/GEDCOM
    QString _url;

    ///////////////////////////////////////////////////////////////////////////

    QVector<EventRecorded> constData(const CommonEventType t) const;
    QVector<EventRecorded>& data(const CommonEventType t);

    ///////////////////////////////////////////////////////////////////////////

protected:
    // Constructor
    SourceRecord(const Identifier ref);
public:
    // Copy constructors
    SourceRecord(const SourceRecord&) = default;
    SourceRecord& operator=(const SourceRecord&) = default;

    // Destructor
    ~SourceRecord() = default;

    ///////////////////////////////////////////////////////////////////////////
    /// Validators
    ///////////////////////////////////////////////////////////////////////////

    bool isDateContained(const CommonEventType t, unsigned int index, const Date date) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Getters
    ///////////////////////////////////////////////////////////////////////////

    Identifier getRef() const;

    QVector<CommonEventType> getData() const;
    unsigned int getDataCount(const CommonEventType t) const;

    Date getDataDateFrom(const CommonEventType t, unsigned int index) const;
    Date getDataDateTo(const CommonEventType t, unsigned int index) const;
    QString getDataPlac(const CommonEventType t, unsigned int index) const;
    QString getDataPage1(const CommonEventType t, unsigned int index) const;
    QString getDataPage2(const CommonEventType t, unsigned int index) const;
    QString getDataUrl(const CommonEventType t, unsigned int index) const;

    QString getArchive() const;
    QString getSignature() const;
    QString getOriginator() const;
    QString getUrl() const;

    ///////////////////////////////////////////////////////////////////////////
    /// Setters
    ///////////////////////////////////////////////////////////////////////////

    void setDataDateFrom(const CommonEventType t, unsigned int index, const Date date1);
    void setDataDateTo(const CommonEventType t, unsigned int index, const Date date2);
    void setDataPlac(const CommonEventType t, unsigned int index, const QString plac);
    void setDataPage1(const CommonEventType t, unsigned int index, const QString page);
    void setDataPage2(const CommonEventType t, unsigned int index, const QString page);
    void setDataUrl(const CommonEventType t, unsigned int index, const QString url);

    void setArchive(const QString &archive);
    void setSignature(const QString &title);
    void setOriginator(const QString &originator);
    void setUrl(const QString &url);

    ///////////////////////////////////////////////////////////////////////////
    /// Adders
    ///////////////////////////////////////////////////////////////////////////

    unsigned int addData(const CommonEventType t);

    ///////////////////////////////////////////////////////////////////////////
    /// Removers
    ///////////////////////////////////////////////////////////////////////////

    void removeData(const CommonEventType t, unsigned int index);

};

#endif // SOURCERECORD_H
