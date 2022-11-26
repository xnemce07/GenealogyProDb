/*!
 *  \file   family.h
 *  \author Eva Navratilova
 */

#ifndef FAMILY_H
#define FAMILY_H

#include <QVector>
#include <QString>

#include "primitives.h"
#include "identifier.h"
#include "event/commoneventstructure.h"
#include "date.h"


/**
 * @brief Structure for saving and accessing family data
 *
 */
class Family
{
    friend class RecordRAM;
private:
    // Probably add AssociationStructure ????

    Identifier _ref; /**< Identifier of Faimly */

    QHash<CommonEventType, CommonEventStructure> _events; /**< Family events - MARR, DIV, ... */

    Identifier _refHusb; /**< Identifier of husband */
    Identifier _refWife; /**< Identifier of wife */

    // References to children
    QVector<Identifier> _refChil; /**< Vector of Identifiers of children */

    // Submitter reference SUBM
    //QVector<QString> subm;

    // Vector of LDS_SPOUSE_SEALING?

    // USER_REFERENCE_TYPE?
    // RIN?

    //QString note; /**< Note to family - not necessary */

    // Source - exists in event detail, that is all that is needed
    // SourceCitation src;

    ///////////////////////////////////////////////////////////////////////////
    /// METHODS

    /// Validators

    bool isEvent(CommonEventType t) const;
    CommonEventStructure constEvent(CommonEventType t) const;
    CommonEventStructure& event(CommonEventType t);

    void setEvent(CommonEventType t);
    void removeEvent(CommonEventType t);

protected:
    /**
     * @brief Protected constructor
     *
     * @param ref   Identifier of the newly constructed Family structure
     */
    Family(Identifier ref) : _ref(ref) {}


public:

    /**
     * @brief Default copy constructor
     *
     * @param   Family structure to be copied
     */
    Family(const Family &f) = default;

    /**
     * @brief Copy constructor
     *
     * @param                       Family structure to be copied
     * @return Family &operator     The new Family copy
     */
    Family& operator=(const Family &f) = default;

    /**
     * @brief Default destructor
     *
     */
    ~Family() = default;


    void copyFamily(const Family &f);

    /// Validators

    bool isEmpty() const;

    /**
     * @brief Method indicating whether the partners in the Family were married
     *
     * @return bool     Returns the indicator, whether the partners were married
     */
    bool isMarried() const;

    /**
     * @brief Method indicationg whether the partners in the Family were divorced
     *
     * @return bool     Returns the indicator, whether the partners were divorced
     */
    bool isDivorced() const;


    ///////////////////////////////////////////////////////////////////////////
    /// Getters
    ///////////////////////////////////////////////////////////////////////////

    Identifier getRef() const;

    /**
     * @brief
     *
     * @param ref
     * @return Identifier
     */
    Identifier getHusband() const;

    /**
     * @brief
     *
     * @param ref
     * @return Identifier
     */
    Identifier getWife() const;

    /**
     * @brief
     *
     * @param ref
     * @return QVector<Identifier>
     */
    QVector<Identifier> getChildren() const;

    CommonEventStructure constMarriage() const;
    CommonEventStructure constDivorce() const;
    CommonEventStructure& marriage();
    CommonEventStructure &divorce();



    ///////////////////////////////////////////////////////////////////////////
    /// Setters
    ///////////////////////////////////////////////////////////////////////////

    /**
     * @brief
     *
     * @param ref
     */
    void setHusband(Identifier indi);
    /**
     * @brief
     *
     * @param ref
     */
    void setWife(Identifier indi);

    /**
     * @brief
     *
     * @param ref
     */
    void setChild(Identifier indi);

    void setMarriage();
    void setDivorce();


    ///////////////////////////////////////////////////////////////////////////
    /// Removers

    void removeHusband();
    void removeWife();

    /**
     * @brief Removes a child whose Identifier conforms to parameter.
     *
     * @param ref   Identifier to be removed
     */
    void removeChild(Identifier indi);

    /**
     * @brief Removes either husband, wife or child, whose Identifier conforms to parameter.
     *
     * @param indi  Identifier to be removed
     */
    void removeIndividual(Identifier indi);

    void removeMarriage();
    void removeDivorce();



};


#endif // FAMILY_H
