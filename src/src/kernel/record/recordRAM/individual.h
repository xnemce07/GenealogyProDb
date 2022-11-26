/*!
 *  \file   individual.h
 *  \author Eva Navratilova
 */

#ifndef PERSON_H
#define PERSON_H

#include <QVector>
#include <QString>

#include "primitives.h"
#include "event/commoneventstructure.h"
#include "individual/personalnamepieces.h"
#include "identifier.h"
#include "date.h"



enum class Gender
{
    MALE,     // Male
    FEMALE,   // Female
    UNDET     // Undetermined
};


/**
 * @brief
 *
 */
class Individual
{
    // Who can use my protected members?
    friend class RecordRAM;
private:
    // Reference to this
    Identifier _ref; /**< Individual's identifier */

    PersonalNamePieces _name; /**< Individual's name structure */
    Gender _gender; /**< Individual's gender */

    // Individual event structure
    // Birth, death, bapm, chr, buri, crem, ...
    QHash<CommonEventType, CommonEventStructure> _events; /**< Events of Individual's life (birth, death, etc.) */

//    vector of indi attr structure
//    probably change to one QMultiHash in the future as well !!!
    QVector<CommonEventStructure> _occu; /**< Individual's occupations */
    QVector<CommonEventStructure> _educ; /**< Individual's education information */
    QVector<CommonEventStructure> _resi; /**< Individual's  places of residence */
    QVector<CommonEventStructure> _reli; /**< Individual's religions */
    CommonEventStructure _nati;  /**< Individual's national or tribal origin */
    Address _address;


//    vector of lds individual ordinance

//    vector of child to family link - not supported
    //Identifier famc; /**< Reference (Identifier) to Individual's parental Family */

//    vector of spouse to family link - not supported
    //QVector<Identifier> fams; /**< Reference (Identifier) to Individual's Families, where the Individual figures as a spouse */

    //QVector<Submitter> subm;

//    vector of association structure - not supported
    //QVector<AssociationStructure> _asso; /**< Records associated to the Individual */

//    vector of alia
//    vector of anci
//    vector of desi

    QString _note; /**< Notes about the Individual */
    //QVector<SourceCitation> src;

    ///////////////////////////////////////////////////////////////////////////
    /// PRIVATE METHODS
    ///////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////
    /// Helper functions to ease the bodies of public functions
    ///////////////////////////////////////////////////////////////////////////

    /**
     * @brief Returns true if EventType exists for this Individual
     *
     * @param t     EventType to check
     * @return      Existence of the checked EventType
     */
    bool isEvent(const CommonEventType t) const;

    CommonEventStructure constEvent(const CommonEventType t) const;

    CommonEventStructure& event(const CommonEventType t);

    void setEvent(CommonEventType t);

    /// Removers

    void removeEvent(CommonEventType t);

protected:
    /**
     * @brief Constructor
     *
     * @param ref Identifier to initialize the Individual with
     */
    Individual(Identifier _ref);


public:
    /**
     * @brief Default copy constructor
     *
     * @param   Instance of Individual to be copied
     */
    Individual(const Individual&) = default;

    /**
     * @brief Default copy constructor
     *
     * @param                           Instance of Individual to be copied
     * @return Individual &operator     Copy of Individual
     */
    Individual& operator=(const Individual&) = default;

    /**
     * @brief Destructor
     *
     */
    ~Individual();

    ///////////////////////////////////////////////////////////////////////////

    PersonalNamePieces constName() const;
    PersonalNamePieces& name();

    CommonEventStructure constBirth() const;
    CommonEventStructure constChristening() const;
    CommonEventStructure constDeath() const;
    CommonEventStructure constBurial() const;

    CommonEventStructure constOccupation(const unsigned int index) const;
    CommonEventStructure constEducation(const unsigned int index) const;
    CommonEventStructure constResidence(const unsigned int index) const;
    CommonEventStructure constReligion(const unsigned int index) const;

    Address constAddress() const;

    CommonEventStructure& birth();
    CommonEventStructure& christening();
    CommonEventStructure& death();
    CommonEventStructure& burial();

    CommonEventStructure& occupation(const unsigned int index);
    CommonEventStructure& education(const unsigned int index);
    CommonEventStructure& residence(const unsigned int index);
    CommonEventStructure& religion(const unsigned int index);

    Address& address();


    ///////////////////////////////////////////////////////////////////////////
    /// Validators
    ///////////////////////////////////////////////////////////////////////////

    bool isBorn() const;
    bool isChristened() const;
    bool isBuried() const;
    /**
     * @brief Returns information, whether the Individual is deceased
     *
     * @return bool     Information about the Individual being deceased
     */
    bool isDeceased() const;


    ///////////////////////////////////////////////////////////////////////////
    /// Getters
    ///////////////////////////////////////////////////////////////////////////


    Identifier getRef() const;

    /**
     * @brief Returns gender of the Individual
     *
     * @return Gender   Gender of the individual
     */
    Gender getGender() const;

    unsigned int getOccuCount() const;
    unsigned int getEducCount() const;
    unsigned int getResiCount() const;
    unsigned int getReliCount() const;

    QString getNote() const;


    ///////////////////////////////////////////////////////////////////////////
    /// Setters
    ///////////////////////////////////////////////////////////////////////////

    /**
     * @brief Sets Individual's gender
     *
     * @param str   Gender to set to the Individual
     */
    void setGender(const Gender g);

    void setNote(QString n);

    void setDeath();


    ///////////////////////////////////////////////////////////////////////////
    /// swapers
    ///////////////////////////////////////////////////////////////////////////

    void swapOccu(const unsigned int index1, const unsigned int index2);
    void swapEduc(const unsigned int index1, const unsigned int index2);
    void swapResi(const unsigned int index1, const unsigned int index2);
    void swapReli(const unsigned int index1, const unsigned int index2);


    ///////////////////////////////////////////////////////////////////////////
    /// Removers
    ///////////////////////////////////////////////////////////////////////////

    void removeBirth();
    void removeChristening();
    void removeDeath();
    void removeBurial();

    void removeOccu(const unsigned int index);
    void removeEduc(const unsigned int index);
    void removeResi(const unsigned int index);
    void removeReli(const unsigned int index);

};


#endif // PERSON_H
