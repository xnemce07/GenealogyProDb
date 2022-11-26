/*!
 *  \file   submitter.h
 *  \author Eva Navratilova
 */

#ifndef SUBMITTER_H
#define SUBMITTER_H

#include <QString>
#include <QTime>

#include "address.h"
#include "identifier.h"
#include "date.h"


/**
 * @brief
 *
 */
class Submitter
{
    friend class RecordRAM;
private:
    Identifier _ref; /**< Mandatory: Identifier of the Submitter */
    QString _name; /**< Mandatory: Submitter name (max 60 chars) */
    Address _address; /**< Optional: Submitter's address */
    QString _lang; /**< Optional: Language preference (see header language to check available language values) */
    QString _note; /**< Optional: Submitter note */

    // Submitter registered rfn - not supported
    // Automated record id - not supported

    Date _date; /**< Optional: Date of the last change */
    QTime _time; /**< Optional: Time of the last change */

protected:
    /**
     * @brief
     *
     */
    Submitter(Identifier ref);



public:
    /**
     * @brief Default copy constructor
     *
     * @param   Instance of Submitter to be copied
     */
    Submitter(const Submitter&) = default;

    /**
     * @brief Default copy constructor
     *
     * @param                           Instance of Submitter to be copied
     * @return Submitter &operator      Copy of Submitter
     */
    Submitter& operator=(const Submitter&) = default;

    /**
     * @brief Default destructor
     *
     */
    ~Submitter() = default;


    bool isEmpty() const;


    Address constAddress() const;
    Address& address();

    ///////////////////////////////////////////////////////////////////////////
    /// Getters
    ///////////////////////////////////////////////////////////////////////////

    Identifier getRef() const;

    QString getName() const;

    QString getLang() const;

    QString getNote() const;

    Date getDate() const;

    QTime getTime() const;


    ///////////////////////////////////////////////////////////////////////////
    /// Setters
    ///////////////////////////////////////////////////////////////////////////

    void setName(const QString name);

    void setLang(const QString lang);

    void setNote(const QString note);

    void setDate(const Date date);

    void setTime(const QTime time);


};

#endif // SUBMITTER_H
