/*!
 *  \file   identifier.h
 *  \author Eva Navratilova
 */

#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#define INDI_STRING "IND"
#define FAM_STRING  "FAM"
#define SUBM_STRING "SBM"
#define SOUR_STRING "SRC"

#include <QString>
#include <QHash>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "identifier/identifiertype.h"
//#include "identifier/identifierfactory.h"


/**
 * @brief
 *
 */
class Identifier
{
friend class IdentifierFactory;

private:
    IdentifierType _type; /**< Identifier type */
    unsigned long long int _number; /**< Identifier number */

protected:
    /**
     * @brief
     *
     * @param t
     * @param n
     */
    Identifier(const IdentifierType t, const unsigned long long int n) : _type(t), _number(n){}
    Identifier(QString ref);

    Identifier& operator++();
    Identifier operator++(int);

public:

    /**
     * @brief
     *
     */
    Identifier() : _type(IdentifierType::ID_INVAL), _number(0){}

    // Copy constructors are available
    /**
     * @brief
     *
     * @param obj
     */
    Identifier(const Identifier &obj) = default;
    /**
     * @brief
     *
     * @param obj
     */
    void operator=(Identifier const &obj);

    /**
     * @brief
     *
     * @param obj
     * @return bool operator
     */
    bool operator<(const Identifier &obj) const;
    bool operator<=(const Identifier &obj) const;
    bool operator==(const Identifier &obj) const;
    bool operator!=(const Identifier &obj) const;

    /**
     * @brief Enables sorting of Individual's  Identifiers
     *        according to the Individual's ages
     *
     * If the Identifier parameters don't belong to Individuals, false is returned
     *
     * MUST BE IMPLEMENTED SOMEWHERE ELSE - NEEDS TO BE ABLE TO SEARCH IN RECORDRAM FOR
     * THE INDIVIDUAL WITH THE IDENTIFIER!!!!
     *
     * @param a                 Identifier of a
     * @param b                 Identifier of b
     * @return bool operator    True if Individual a is younger than Individual b, else false
     */
    //bool operator<(const Identifier& a, const Identifier& b);

    /**
     * @brief
     *
     * @return QString
     */
    QString get() const;

    unsigned long long int getNumber();

    static Identifier fromString(const QString string);

    /**
     * @brief
     *
     * @return bool
     */
    bool isValid() const;

};

#endif // IDENTIFIER_H

