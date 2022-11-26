/*!
 *  \file   commoneventstructure.h
 *  \author Eva Navratilova
 */

#ifndef INDIVIDUAEVENTSTRUCTURE_H
#define INDIVIDUAEVENTSTRUCTURE_H

#include <QString>

#include "../eventdetail.h"

/**
 * @brief Common enumerator for all types of supported Events and Attributes
 *
 */
enum class CommonEventType
{
    // Individual Evet Type
    EMPT = 0,   // Empty structure
    BIRT = 1,
    CHR,
    DEAT,
    BURI,

    /*
    CREM,
    ADOP,
    BAPM,
    BARM,
    BASM,
    BLES,
    CHRA,
    CONF,
    FCOM,
    ORDN,
    NATU,
    EMIG,
    IMMI,
    CENS,
    PROB,
    WILL,
    GRAD,
    RETI,
    EVEN
    */

    // Individual Attribute Type
    EDUC,
    NATI,
    OCCU,
    RELI,
    RESI,


    // Family Event Type
    MARR,       // MARRIAGE
    DIV         // DIVORCE

    /*
    // Not supported
    CENS,   // Census
    MARB,   // Official public notice about two people intending to get married
    MARC,   // Marriage contract
    MARL,   // Obtaining legal license to marry
    MARS,   // Marriage settlement (After-marriage property rights modification)
    ENGA,   // Engagement
    EVEN,   // Noteworthy event related to indi, group, organization
    ANUL,   // Declaring marriage void from the beginning (never existed)
    DIVF,   // A spouse filed for a divorce
    RESI    // Residence
    */
};


/**
 * @brief Common class for IndividualEvent, IndividualAttribute and FamilyEvent
 */
class CommonEventStructure
{
private:
    CommonEventType _type; /**< Type of event */
    QString _descr; /**< Desription - only when IndividualAttribute!! */
    EventDetail _detail; /**< Additional event data */

public:
    // Constructor
    CommonEventStructure();
    CommonEventStructure(CommonEventType t);

    // Copy constructor
    CommonEventStructure(const CommonEventStructure &s);
    CommonEventStructure& operator=(const CommonEventStructure &s);

    // Destructor
    ~CommonEventStructure() = default;

    EventDetail constDetail() const;
    EventDetail& detail();

    // Getters
    CommonEventType getType() const;
    QString getDescription() const;

    void setDescription(QString d);
};




#endif // INDIVIDUAEVENTSTRUCTURE_H
