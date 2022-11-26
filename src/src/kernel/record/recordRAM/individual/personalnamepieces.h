/*!
 *  \file   personalnamepieces.h
 *  \author Eva Navratilova
 */

#ifndef PERSONALNAMEPIECES_H
#define PERSONALNAMEPIECES_H

#include <QString>

#include "../primitives.h"


/**
 * @brief
 *
 */
enum class NameType
{
    AKA,    // aka
    BIRT,   // birth
    IMMI,   // immigrant
    MAID,   // maiden
    MARR    // married

};

/**
 * @brief Defines name pieces of individual's name
 *
 */
class PersonalNamePieces
{
private:
    QString npfx;   // Name prefix /**< TODO: describe */
    QString givn;   // Given name /**< TODO: describe */
    //QString nick;   // Nickname - not necessary
    //QString spfx;   // Surname prefix - not necessary
    QString surn;   // Surname /**< TODO: describe */
    QString marn;   // Married surname (_MARNM) /**< TODO: describe */
    QString nsfx;   // Name suffix /**< TODO: describe */

    // Note - not necessary
   //QString note;

    // Source not supported

public:
    /**
     * @brief
     *
     */
    PersonalNamePieces() = default;
    ~PersonalNamePieces() = default;

    /// Get methods
    /**
     * @brief
     *
     * @return QString
     */
    QString getPrefix() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString getGiven() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString getSurname() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString getMarname() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString getSuffix() const;

    // Setters
    /**
     * @brief
     *
     * @param str
     */
    void setPrefix(const QString str);
    /**
     * @brief
     *
     * @param str
     */
    void setGiven(const QString str);
    /**
     * @brief
     *
     * @param str
     */
    void setSurname(const QString str);
    /**
     * @brief
     *
     * @param str
     */
    void setMarname(const QString str);
    /**
     * @brief
     *
     * @param str
     */
    void setSuffix(const QString str);

};


/*
class PersonalNameStructure
{
    QString namePersonal;
    NameType type;
    PersonalNamePieces pieces;

};
*/


#endif // PERSONALNAMEPIECES_H
