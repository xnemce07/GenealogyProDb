/*!
 *  \file   record.h
 *  \author Eva Navratilova
 */

#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QTime>

//#include "record/recordRAM/agefile.h"
#include "record/recordRAM/family.h"
#include "record/recordRAM/individual.h"
#include "record/recordRAM/place.h"
#include "record/recordRAM/event/commoneventstructure.h"
#include "record/recordRAM/date.h"
//#include "record/recordRAM/submitter.h"

class Individual;
class Family;

enum class BoolExtended
{
    FALSE = 0,
    TRUE,
    UNDETERMINED
};

/**
 * @brief
 *
 */
class Record
{
    friend class ImporterGedcom;

protected:
    virtual Identifier newIndividual(Identifier indi) = 0;

    /**
     * @brief Constructs a new empty Family Record with a unique identifier
     *
     * @return Identifier   Unique identifier of the constructed Family
     */
    virtual Identifier newFamily(Identifier fam) = 0;

    virtual Identifier newSubmitter(Identifier subm) = 0;

    virtual Identifier newSource(Identifier sour) = 0;

public:
    /**
     * @brief
     *
     */
    Record();
    /**
     * @brief
     *
     */
    virtual ~Record();


    ///////////////////////////////////////////////////////////////////////////
    /// New
    ///////////////////////////////////////////////////////////////////////////

    /**
     * @brief Constructs a new empty Individual Record with a unique identifier
     *
     * @return Identifier   Unique identifier of the constructed Individual
     */
    virtual Identifier newIndividual() = 0;

    /**
     * @brief Constructs a new empty Family Record with a unique identifier
     *
     * @return Identifier   Unique identifier of the constructed Family
     */
    virtual Identifier newFamily() = 0;

    virtual Identifier newSubmitter() = 0;

    virtual Identifier newSource() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Validators
    ///////////////////////////////////////////////////////////////////////////

    /**
     * @brief Core validator whether an identifier belongs to a known Individual
     *
     * @param ref       Identifier of an individual
     * @return bool     Does the identifier belong to a known individual?
     */
    virtual bool isIndividual(const Identifier indi) const = 0;

    /**
     * @brief Core validator whether an identifier belongs to a known Family
     *
     * @param ref       Identifier of a family
     * @return bool     Does the identifier belong to a known family?
     */
    virtual bool isFamily(const Identifier fam) const = 0;

    virtual bool isSubmitter(const Identifier subm) const = 0;

    virtual bool isSource(const Identifier src) const = 0;

    virtual bool isSubmitterEmpty(Identifier subm) const = 0;


    ///////////////////////////////////////////////////////////////////////////
    /// First - Last Identifier Getters
    ///////////////////////////////////////////////////////////////////////////

    virtual Identifier getIdentifierIndividualFirst() const = 0;
    virtual Identifier getIdentifierIndividualLast() const = 0;
    virtual Identifier getIdentifierIndividualNext(Identifier &indi) const = 0;

    virtual Identifier getIdentifierFamilyFirst() const = 0;
    virtual Identifier getIdentifierFamilyLast() const = 0;
    virtual Identifier getIdentifierFamilyNext(Identifier &fam) const = 0;

    virtual Identifier getIdentifierSubmitterFirst() const = 0;
    virtual Identifier getIdentifierSubmitterLast() const = 0;
    virtual Identifier getIdentifierSubmitterNext(Identifier &subm) const = 0;

    virtual Identifier getIdentifierSourceFirst() const = 0;
    virtual Identifier getIdentifierSourceLast() const = 0;
    virtual Identifier getIdentifierSourceNext(Identifier &src) const = 0;


    ///////////////////////////////////////////////////////////////////////////

    virtual bool isIndividualBorn(const Identifier indi) const = 0;
    virtual bool isIndividualChristened(const Identifier indi) const = 0;
    virtual bool isIndividualBuried(const Identifier indi) const = 0;

    /**
     * @brief Returns a boolean indicating whether the Individual is deceased
     *
     * If the Individual is invalid, function returns false
     *
     * @param ref       Identifier of the Individual
     * @return bool     A boolean indicating whether the Individual is deceased
     */
    virtual bool isIndividualDeceased(const Identifier indi) const = 0;

    /**
     * @brief Returns a boolean indicating whether the Family is married
     *
     * If the Family is invalid, function returns false
     *
     * @param ref       Identifier of the Family record
     * @return bool     A boolean indicating whether the Family is married
     */
    virtual bool isFamilyMarried(const Identifier fam) const = 0;

    /**
     * @brief Returns a boolean indicating whether the Family is divorced
     *
     * If the Family is invalid, function returns false
     *
     * @param ref       Identifier of the Family record
     * @return bool     A boolean indicating whether the Family is divorced
     */
    virtual bool isFamilyDivorced(const Identifier fam) const = 0;



    virtual bool isSourceCited(const Identifier src) const = 0;


    virtual void setIndividualDeceased(const Identifier indi, const bool deceased) = 0;
    virtual void setFamilyMarried(const Identifier fam, const bool married) = 0;
    virtual void setFamilyDivorced(const Identifier fam, const bool divorced) = 0;


    ///////////////////////////////////////////////////////////////////////////
    /// Default members
    ///////////////////////////////////////////////////////////////////////////

//    virtual Identifier getIndividualProband() const = 0;
//    virtual void setIndividualProband(const Identifier indi) = 0;
//    virtual void clearIndividualProband() = 0;

//    virtual Identifier getIndividualCurrent() const = 0;
//    virtual void setIndividualCurrent(const Identifier indi) = 0;
//    virtual void clearIndividualCurrent() = 0;


    ///////////////////////////////////////////////////////////////////////////
    /// Getters
    ///////////////////////////////////////////////////////////////////////////

    /// HEAD - DONE

    virtual QString getHeadSrc() const = 0;
    virtual QString getHeadSrcVersion() const = 0;
    virtual QString getHeadSrcName() const = 0;
    virtual QString getHeadSrcCorp() const = 0;
    virtual QString getHeadSrcAddrAddress() const = 0;
    virtual QString getHeadSrcAddrCity() const = 0;
    virtual QString getHeadSrcAddrState() const = 0;
    virtual QString getHeadSrcAddrPhone() const = 0;
    virtual QString getHeadSrcAddrEmail() const = 0;
    virtual QString getHeadSrcAddrWww() const = 0;
    virtual QString getHeadSrcData() const = 0;
    virtual Date getHeadSrcDataDate() const = 0;
    virtual QString getHeadDest() const = 0;
    virtual Date getHeadDate() const = 0;
    virtual QTime getHeadTime() const = 0;
    virtual Identifier getHeadRefSubm() const = 0;
    virtual QString getHeadFile() const = 0;
    virtual QString getHeadCopr() const = 0;
    virtual QString getHeadGedVers() const = 0;
    virtual QString getHeadGedForm() const = 0;
    virtual QString getHeadCharSet() const = 0;
    virtual QString getHeadCharVers() const = 0;
    virtual QString getHeadLang() const = 0;
    virtual QString getHeadPlac() const = 0;
    virtual QString getHeadNote() const = 0;


    /// SUBMITTER - DONE

    /**
     * @brief Returns Identifier od first created Submitter
     *
     * If no Submitter was created, returns Invalid Identifier
     *
     * @return  Identifier of first Submitter or Identifier Invalid
     */
    virtual Identifier getFirstSubmitterRef() const = 0;
    virtual QString getSubmitterName(const Identifier subm) const = 0;
    virtual QString getSubmitterLang(const Identifier subm) const = 0;
    virtual QString getSubmitterNote(const Identifier subm) const = 0;
    virtual Date getSubmitterDate(const Identifier subm) const = 0;
    virtual QTime getSubmitterTime(const Identifier subm) const = 0;


    /// SOURCE RECORD - DONE

    /**
     * @brief Gets vector of Identifiers of sources with said parameters
     *
     * @param t         Type of source record
     * @param date      Date contained in the source
     * @param place     Place of source
     * @return          Vector of Identifiers of suitable Sources
     */
    virtual QVector<Identifier> getSourceRefs(const CommonEventType t, const Date date = Date(), const QString place = QString()) const = 0;
    Date getSourceCommonDateFrom(Identifier src) const;
    Date getSourceCommonDateTo(Identifier src) const;

    virtual QVector<CommonEventType> getSourceData(const Identifier src) const = 0;
    virtual unsigned int getSourceDataCount(const Identifier src, const CommonEventType t) const = 0;

    virtual Date getSourceDataDateFrom(const Identifier src, const CommonEventType t, unsigned int index) const = 0;
    virtual Date getSourceDataDateTo(const Identifier src, const CommonEventType t, unsigned int index) const = 0;
    virtual QString getSourceDataPlac(const Identifier src, const CommonEventType t, unsigned int index) const = 0;
    virtual QString getSourceDataPage1(const Identifier src, const CommonEventType t, unsigned int index) const = 0;
    virtual QString getSourceDataPage2(const Identifier src, const CommonEventType t, unsigned int index) const = 0;
    virtual QString getSourceDataUrl(const Identifier src, const CommonEventType t, unsigned int index) const = 0;

    virtual QString getSourceArchive(const Identifier src) const = 0;
    virtual QString getSourceTitle(const Identifier src) const = 0;
    virtual QString getSourceOriginator(const Identifier src) const = 0;
    virtual QString getSourceUrl(const Identifier src) const = 0;


    /// INDIVIDUAL

    /**
     * @brief Returns Identifier od first created Individual
     *
     * If no Individual was created, returns Invalid Identifier
     *
     * @return  Identifier of proband or Identifier Invalid
     */
    virtual Identifier getIndividualProbandRef() const = 0;

    virtual QString getIndividualNamePrefix(const Identifier indi) const = 0;

    /**
     * @brief Returns given name of an Individual
     *
     * @param ref       Identifier of the Individual
     * @return QString  Given name of the Individual
     */
    virtual QString getIndividualNameGiven(const Identifier indi) const = 0;

    /**
     * @brief Returns birth surname of an Individual
     *
     * @param ref       Identifier of the Individual
     * @return QString  Birth surname of the Individual
     */
    virtual QString getIndividualNameSurnameBirth(const Identifier indi) const = 0;

    /**
     * @brief Returns married surname of an Individual
     *
     * @param ref       Identifier of the Individual
     * @return QString  Married surname of the Individual
     */
    virtual QString getIndividualNameSurnameMarried(const Identifier indi) const = 0;

    virtual QString getIndividualNameSuffix(const Identifier indi) const = 0;

    /**
     * @brief Returns the gender enum value of an Individual
     *
     * @param indi      Identifier of the Individual
     * @return Gender   Gender of the Individual
     */
    virtual Gender getIndividualGender(const Identifier indi) const = 0;

    /**
     * @brief Returns date of birth of an Individual
     *
     * @param ref       Identifier of the Individual
     * @return Date    Date of birth of the Individual
     */
    virtual DateType getIndividualBirthDateType(const Identifier indi) const = 0;
    virtual Date getIndividualBirthDate1(const Identifier indi) const = 0;
    virtual Date getIndividualBirthDate2(const Identifier indi) const = 0;
    virtual QString getIndividualBirthPlaceName(const Identifier indi) const = 0;
    virtual Identifier getIndividualBirthObstetrix(const Identifier indi) const = 0;
    virtual Identifier getIndividualBirthSourceRef(const Identifier indi) const = 0;
    virtual QString getIndividualBirthSourceCitationPage(const Identifier indi) const = 0;
    virtual QString getIndividualBirthSourceCitationUrl(const Identifier indi) const = 0;

    virtual DateType getIndividualChristeningDateType(const Identifier indi) const = 0;
    virtual Date getIndividualChristeningDate1(const Identifier indi) const = 0;
    virtual Date getIndividualChristeningDate2(const Identifier indi) const = 0;
    virtual Identifier getIndividualChristeningPriest(const Identifier indi) const = 0;
    virtual Identifier getIndividualChristeningGodfather(const Identifier indi) const = 0;
    virtual Identifier getIndividualChristeningGodmother(const Identifier indi) const = 0;

    /**
     * @brief Returns date of death of an Individual
     *
     * @param ref       Identifier of the Individual
     * @return Date    Date of death of the Individual
     */
    virtual DateType getIndividualDeathDateType(const Identifier indi) const = 0;
    virtual Date getIndividualDeathDate1(const Identifier indi) const = 0;
    virtual Date getIndividualDeathDate2(const Identifier indi) const = 0;
    virtual QString getIndividualDeathPlaceName(const Identifier indi) const = 0;
    virtual QString getIndividualDeathCause(const Identifier indi) const = 0;
    virtual Identifier getIndividualDeathSourceRef(const Identifier indi) const = 0;
    virtual QString getIndividualDeathSourceCitationPage(const Identifier indi) const = 0;
    virtual QString getIndividualDeathSourceCitationUrl(const Identifier indi) const = 0;

    virtual DateType getIndividualBurialDateType(const Identifier indi) const = 0;
    virtual Date getIndividualBurialDate1(const Identifier indi) const = 0;
    virtual Date getIndividualBurialDate2(const Identifier indi) const = 0;
    virtual QString getIndividualBurialPlaceName(const Identifier indi) const = 0;
    virtual Identifier getIndividualBurialPriest(const Identifier indi) const = 0;

    virtual unsigned int getIndividualOccuCount(const Identifier indi) const = 0;
    virtual QString getIndividualOccuDescription(const Identifier indi, const unsigned int index) const = 0;
    virtual DateType getIndividualOccuDateType(const Identifier indi, const unsigned int index) const = 0;
    virtual Date getIndividualOccuDate1(const Identifier indi, const unsigned int index) const = 0;
    virtual Date getIndividualOccuDate2(const Identifier indi, const unsigned int index) const = 0;

    // EDUC
    virtual unsigned int getIndividualEducCount(const Identifier indi) const = 0;
    virtual QString getIndividualEducDescription(const Identifier indi, const unsigned int index) const = 0;
    virtual DateType getIndividualEducDateType(const Identifier indi, const unsigned int index) const = 0;
    virtual Date getIndividualEducDate1(const Identifier indi, const unsigned int index) const = 0;
    virtual Date getIndividualEducDate2(const Identifier indi, const unsigned int index) const = 0;

    // RESI
    virtual unsigned int getIndividualResiCount(const Identifier indi) const = 0;
    virtual DateType getIndividualResiDateType(const Identifier indi, const unsigned int index) const = 0;
    virtual Date getIndividualResiDate1(const Identifier indi, const unsigned int index) const = 0;
    virtual Date getIndividualResiDate2(const Identifier indi, const unsigned int index) const = 0;
    virtual QString getIndividualResiAddrCity(const Identifier indi, const unsigned int index) const = 0;
    virtual QString getIndividualResiAddrAddr(const Identifier indi, const unsigned int index) const = 0;

    // Reli
    virtual unsigned int getIndividualReliCount(const Identifier indi) const = 0;
    virtual QString getIndividualReliDescription(const Identifier indi, const unsigned int index) const = 0;
    virtual DateType getIndividualReliDateType(const Identifier indi, const unsigned int index) const = 0;
    virtual Date getIndividualReliDate1(const Identifier indi, const unsigned int index) const = 0;
    virtual Date getIndividualReliDate2(const Identifier indi, const unsigned int index) const = 0;


    virtual QString getIndividualPhone(const Identifier indi) const = 0;
    virtual QString getIndividualEmail(const Identifier indi) const = 0;
    virtual QString getIndividualWww(const Identifier indi) const = 0;

    // Note
    virtual QString getIndividualNote(const Identifier indi) const = 0;


    /// FAMILY

    virtual Identifier getFamilyHusband(const Identifier fam) const = 0;
    virtual Identifier getFamilyWife(const Identifier fam) const = 0;
    virtual QVector<Identifier> getFamilyChildren(const Identifier fam) const = 0;

    // Marriage
    /**
     * @brief Returns date od marriage from an Identifier of Family record
     *
     * If no marriage took place or the date is unknown, Null date is returned
     *
     * @param ref       Identifier od the Family record
     * @return Date    Date of marriage
     */
    virtual DateType getFamilyMarriageDateType(const Identifier fam) const = 0;
    virtual Date getFamilyMarriageDate1(const Identifier fam) const = 0;
    virtual Date getFamilyMarriageDate2(const Identifier fam) const = 0;
    virtual QString getFamilyMarriagePlaceName(const Identifier fam) const = 0;
    virtual Identifier getFamilyMarriagePriest(const Identifier fam) const = 0;
    virtual Identifier getFamilyMarriageWitness1(const Identifier fam) const = 0;
    virtual Identifier getFamilyMarriageWitness2(const Identifier fam) const = 0;
    virtual Identifier getFamilyMarriageSourceRef(const Identifier fam) const = 0;
    virtual QString getFamilyMarriageSourceCitationPage(const Identifier fam) const = 0;
    virtual QString getFamilyMarriageSourceCitationUrl(const Identifier fam) const = 0;



    // Divorce
    /**
     * @brief Returns date od divorce from an Identifier of Family record
     *
     * If no divorce took place or the date is unknown, Null date is returned
     *
     * @param ref       Identifier od the Family record
     * @return Date    Date of divorce
     */
    virtual DateType getFamilyDivorceDateType(const Identifier fam) const = 0;
    virtual Date getFamilyDivorceDate1(const Identifier fam) const = 0;
    virtual Date getFamilyDivorceDate2(const Identifier fam) const = 0;


    /// LINKED INDI-FAM - DONE?

    /**
     * @brief Returns an Identifier of the father of the Individual
     *
     * If the father is not known, an invalid identifier is returned.
     *
     * @param ref           Identifier of the Individual
     * @return Identifier   Identifier of the father of the Individual
     */
    virtual Identifier getIndividualFather(const Identifier indi) const = 0;

    /**
     * @brief Returns an Identifier of the mother of the Individual
     *
     * If the mother is not known, an invalid identifier is returned.
     *
     * @param ref           Identifier of the Individual
     * @return Identifier   Identifier of the mother of the Individual
     */
    virtual Identifier getIndividualMother(const Identifier indi) const = 0;

    /**
     * @brief   Returns an Identifier of a Family where an Individual figures as a family child
     *
     * @param indi           Identifier of the Individual child
     * @return Identifier   Identifier of the Family (parental) of the Individual
     */
    virtual Identifier getIndividualParentalFamily(const Identifier indi) const = 0;

    virtual QVector<Identifier> getIndividualPartners(const Identifier indi) const = 0;

    /**
     * @brief Returns an Identifier of a Family where an Individual figures as a husband or a wife
     *
     * @param ref                   Identifier of the Individual
     * @return QVector<Identifier>  Vectors od Identifiers of the Families od the Individual
     */
    virtual QVector<Identifier> getFamiliesOfIndividualParent(const Identifier ref) const = 0;

    virtual Identifier getFamilyOfCouple(const Identifier indi1, const Identifier indi2) const = 0;

    /**
     * @brief Returns a vector of children of an Individual
     *
     * @param ref                   Identifier od the Individual parent
     * @return QVector<Identifier>  A vector of children of the Individual
     */
    virtual QVector<Identifier> getChildrenOfIndividual(const Identifier indi) const = 0;

    /**
     * @brief Returns a vector of children of a couple
     *
     * @param ref1                  Identifier od the Individual parent 1
     * @param ref2                  Identifier od the Individual parent 2
     * @return QVector<Identifier>  A vector of children of the Individuals' common children
     */
    virtual QVector<Identifier> getChildrenOfCouple(const Identifier indi1, const Identifier indi2) const = 0;

    /**
     * @brief Returns a vector of siblings and half siblings of a person
     *
     * @param ref                   Identifier of the Individual
     * @return QVector<Identifier>  Vector of Identifiers of the Individual's siblings
     */
    virtual QVector<Identifier> getIndividualSiblings(const Identifier indi) const = 0;


    ///////////////////////////////////////////////////////////////////////////
    /// Setters
    ///////////////////////////////////////////////////////////////////////////

    /// HEAD - DONE
    virtual void setHeadSrc(const QString src) = 0;
    virtual void setHeadSrcVersion(const QString vers) = 0;
    virtual void setHeadSrcName(const QString name) = 0;
    virtual void setHeadSrcCorp(const QString corp) = 0;
    virtual void setHeadSrcAddrAddress(const QString addr) = 0;
    virtual void setHeadSrcAddrCity(const QString city) = 0;
    virtual void setHeadSrcAddrState(const QString state) = 0;
    virtual void setHeadSrcAddrPhone(const QString phone) = 0;
    virtual void setHeadSrcAddrEmail(const QString email) = 0;
    virtual void setHeadSrcAddrWww(const QString www) = 0;
    virtual void setHeadSrcData(const QString data) = 0;
    virtual void setHeadSrcDataDate(const Date date) = 0;
    virtual void setHeadDest(const QString dest) = 0;
    virtual void setHeadDate(const Date date) = 0;
    virtual void setHeadTime(const QTime time) = 0;
    virtual void setHeadRefSubm(const Identifier subm) = 0;
    virtual void setHeadFile(const QString file) = 0;
    virtual void setHeadCopr(const QString copr) = 0;
    virtual void setHeadGedVers(const QString vers) = 0;
    virtual void setHeadGedForm(const QString form) = 0;
    virtual void setHeadCharSet(const QString charset) = 0;
    virtual void setHeadCharVers(const QString vers) = 0;
    virtual void setHeadLang(const QString subm) = 0;
    virtual void setHeadPlac(const QString subm) = 0;
    virtual void setHeadNote(const QString subm) = 0;


    /// SUBMITTER - DONE
    virtual void setSubmitterName(const Identifier subm, const QString name) = 0;
    virtual void setSubmitterLang(const Identifier subm, const QString lang) = 0;
    virtual void setSubmitterNote(const Identifier subm, const QString note) = 0;
    virtual void setSubmitterDate(const Identifier subm, const Date date) = 0;
    virtual void setSubmitterTime(const Identifier subm, const QTime time) = 0;


    /// SOURCE RECORD - DONE

    virtual unsigned int setSourceData(const Identifier src, const CommonEventType t) = 0;

    virtual void setSourceDataDateFrom(const Identifier src, const CommonEventType t, unsigned int index, const Date from) = 0;
    virtual void setSourceDataDateTo(const Identifier src, const CommonEventType t, unsigned int index, const Date to) = 0;
    virtual void setSourceDataPlac(const Identifier src, const CommonEventType t, unsigned int index, const QString plac) = 0;
    virtual void setSourceDataPage1(const Identifier src, const CommonEventType t, unsigned int index, const QString page) = 0;
    virtual void setSourceDataPage2(const Identifier src, const CommonEventType t, unsigned int index, const QString page) = 0;
    virtual void setSourceDataUrl(const Identifier src, const CommonEventType t, unsigned int index, const QString url) = 0;

    virtual void setSourceArchive(const Identifier src, const QString title) = 0;
    virtual void setSourceTitle(const Identifier src, const QString title) = 0;
    virtual void setSourceOriginator(const Identifier src, const QString title) = 0;
    virtual void setSourceUrl(const Identifier src, const QString url) = 0;


    /// INDIVIDUAL

    virtual void setIndividualNamePrefix(const Identifier indi, const QString name) = 0;

    /**
     * @brief
     *
     * @param ref
     * @param name
     */
    virtual void setIndividualNameGiven(const Identifier indi, const QString name) = 0;

    /**
     * @brief
     *
     * @param ref
     * @param name
     */
    virtual void setIndividualNameSurname(const Identifier indi, const QString name) = 0;
    virtual void setIndividualNameMarname(const Identifier indi, const QString name) = 0;
    virtual void setIndividualNameSuffix(const Identifier indi, const QString name) = 0;

    virtual void setIndividualGender(const Identifier indi, const Gender g) = 0;

    /**
     * @brief
     *
     * @param ref
     * @param date
     */
    virtual void setIndividualBirthDateType(Identifier indi, DateType type) = 0;
    virtual void setIndividualBirthDate1(Identifier indi, Date date) = 0;
    virtual void setIndividualBirthDate2(Identifier indi, Date date) = 0;
    virtual void setIndividualBirthPlaceName(Identifier indi, QString place) = 0;
    virtual void setIndividualBirthObstetrix(const Identifier indi, const Identifier obstetrix) = 0;
    virtual void setIndividualBirthSourceCitationRef(Identifier indi, Identifier src) = 0;
    virtual void setIndividualBirthSourceCitationPage(Identifier indi, QString page) = 0;
    virtual void setIndividualBirthSourceCitationUrl(Identifier indi, QString url) = 0;

    virtual void setIndividualChristeningDateType(const Identifier indi, const DateType datetype) = 0;
    virtual void setIndividualChristeningDate1(const Identifier indi, const Date date) = 0;
    virtual void setIndividualChristeningDate2(const Identifier indi, const Date date) = 0;
    virtual void setIndividualChristeningPriest(const Identifier indi, const Identifier priest) = 0;
    virtual void setIndividualChristeningGodfather(const Identifier indi, const Identifier godfather) = 0;
    virtual void setIndividualChristeningGodmother(const Identifier indi, const Identifier godmother) = 0;

    /**
     * @brief
     *
     * @param ref
     * @param date
     */
    virtual void setIndividualDeathDateType(Identifier indi, DateType date) = 0;
    virtual void setIndividualDeathDate1(Identifier indi, Date date) = 0;
    virtual void setIndividualDeathDate2(Identifier indi, Date date) = 0;
    virtual void setIndividualDeathPlaceName(Identifier indi, QString place) = 0;
    virtual void setIndividualDeathCause(Identifier indi, QString cause) = 0;
    virtual void setIndividualDeathSourceCitationRef(Identifier indi, Identifier src) = 0;
    virtual void setIndividualDeathSourceCitationPage(Identifier indi, QString page) = 0;
    virtual void setIndividualDeathSourceCitationUrl(Identifier indi, QString url) = 0;

    virtual void setIndividualBurialDateType(const Identifier indi, const DateType datetype) = 0;
    virtual void setIndividualBurialDate1(const Identifier indi, const Date date) = 0;
    virtual void setIndividualBurialDate2(const Identifier indi, const Date date) = 0;
    virtual void setIndividualBurialPlaceName(const Identifier indi, const QString place) = 0;
    virtual void setIndividualBurialPriest(const Identifier indi, const Identifier priest) = 0;

    // OCCU
    virtual unsigned int setIndividualOccu(const Identifier indi) = 0;
    virtual void setIndividualOccuDescription(const Identifier indi, const unsigned int index, const QString descr) = 0;
    virtual void setIndividualOccuDateType(const Identifier indi, const unsigned int index, const DateType datetype) = 0;
    virtual void setIndividualOccuDate1(const Identifier indi, const unsigned int index, const Date date) = 0;
    virtual void setIndividualOccuDate2(const Identifier indi, const unsigned int index, const Date date) = 0;

    // EDUC
    virtual unsigned int setIndividualEduc(const Identifier indi) = 0;
    virtual void setIndividualEducDescription(const Identifier indi, const unsigned int index, const QString descr) = 0;
    virtual void setIndividualEducDateType(const Identifier indi, const unsigned int index, const DateType datetype) = 0;
    virtual void setIndividualEducDate1(const Identifier indi, const unsigned int index, const Date date) = 0;
    virtual void setIndividualEducDate2(const Identifier indi, const unsigned int index, const Date date) = 0;

    // RESI
    virtual unsigned int setIndividualResi(const Identifier indi) = 0;
    virtual void setIndividualResiDateType(const Identifier indi, const unsigned int index, const DateType datetype) = 0;
    virtual void setIndividualResiDate1(const Identifier indi, const unsigned int index, const Date date) = 0;
    virtual void setIndividualResiDate2(const Identifier indi, const unsigned int index, const Date date) = 0;
    virtual void setIndividualResiAddrCity(const Identifier indi, const unsigned int index, const QString city) = 0;
    virtual void setIndividualResiAddrAddr(const Identifier indi, const unsigned int index, const QString addr) = 0;

    // RELI
    virtual unsigned int setIndividualReli(const Identifier indi) = 0;
    virtual void setIndividualReliDescription(const Identifier indi, const unsigned int index, const QString descr) = 0;
    virtual void setIndividualReliDateType(const Identifier indi, const unsigned int index, const DateType datetype) = 0;
    virtual void setIndividualReliDate1(const Identifier indi, const unsigned int index, const Date date) = 0;
    virtual void setIndividualReliDate2(const Identifier indi, const unsigned int index, const Date date) = 0;

    // LIVING INDIVIDUAL'S CONTACT INFORMATION
    virtual void setIndividualPhone(const Identifier indi, const QString phone) = 0;
    virtual void setIndividualEmail(const Identifier indi, const QString email) = 0;
    virtual void setIndividualWww(const Identifier indi, const QString www) = 0;


    virtual void setIndividualNote(const Identifier indi, const QString note) = 0;



    /// FAMILY

    void setFamilySpouse(Identifier fam, Identifier spouse);
    virtual void setFamilyHusband(Identifier fam, Identifier husb) = 0;
    virtual void setFamilyWife(Identifier fam, Identifier wife) = 0;
    virtual void setFamilyChild(Identifier fam, Identifier chi) = 0;

    virtual void setFamilyMarried(Identifier fam) = 0;
    virtual void setFamilyMarriageDateType(Identifier fam, DateType type) = 0;
    virtual void setFamilyMarriageDate1(Identifier fam, Date date) = 0;
    virtual void setFamilyMarriageDate2(Identifier fam, Date date) = 0;
    virtual void setFamilyMarriagePlaceName(Identifier fam, QString plac) = 0;
    virtual void setFamilyMarriagePriest(const Identifier fam, const Identifier priest) = 0;
    virtual void setFamilyMarriageWitness1(const Identifier fam, const Identifier witness) = 0;
    virtual void setFamilyMarriageWitness2(const Identifier fam, const Identifier witness) = 0;
    virtual void setFamilyMarriageSourceCitationRef(const Identifier indi, const Identifier src) = 0;
    virtual void setFamilyMarriageSourceCitationPage(const Identifier indi, const QString page) = 0;
    virtual void setFamilyMarriageSourceCitationUrl(const Identifier indi, const QString url) = 0;

    virtual void setFamilyDivorced(Identifier fam) = 0;
    virtual void setFamilyDivorceDateType(Identifier fam, DateType type) = 0;
    virtual void setFamilyDivorceDate1(Identifier fam, Date date) = 0;
    virtual void setFamilyDivorceDate2(Identifier fam, Date date) = 0;
    virtual void setFamilyDivorcePlaceName(Identifier fam, QString plac) = 0;


    /// LINKED INDI-FAM - DONE?

    /**
     * @brief
     *
     * @param indi
     * @param father
     */
    virtual void setIndividualFather(Identifier indi, Identifier father) = 0; // Find or create familz, assign child and husb

    /**
     * @brief
     *
     * @param indi
     * @param mother
     */
    virtual void setIndividualMother(Identifier indi, Identifier mother) = 0;

    virtual void setIndividualCouple(const Identifier husb, const Identifier wife) = 0;

    virtual void setIndividualChild(const Identifier indi, const Identifier chi) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Swappers
    ///////////////////////////////////////////////////////////////////////////

    virtual void swapIndividualOccu(Identifier indi, const unsigned int index1, const unsigned int index2) = 0;
    virtual void swapIndividualEduc(Identifier indi, const unsigned int index1, const unsigned int index2) = 0;
    virtual void swapIndividualResi(Identifier indi, const unsigned int index1, const unsigned int index2) = 0;
    virtual void swapIndividualReli(Identifier indi, const unsigned int index1, const unsigned int index2) = 0;

    virtual void swapFamilies(const Identifier fam1, const Identifier fam2) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Remove records
    ///////////////////////////////////////////////////////////////////////////

    virtual void removeIndividualBirth(Identifier indi) = 0;
    virtual void removeIndividualChristening(Identifier indi) = 0;
    virtual void removeIndividualDeath(Identifier indi) = 0;
    virtual void removeIndividualBurial(Identifier indi) = 0;
    virtual void removeIndividualBirthSource(const Identifier indi) = 0;
    virtual void removeIndividualDeathSource(const Identifier indi) = 0;
    virtual void removeIndividualOccu(const Identifier indi, const unsigned int index) = 0;
    virtual void removeIndividualEduc(const Identifier indi, const unsigned int index) = 0;
    virtual void removeIndividualResi(const Identifier indi, const unsigned int index) = 0;
    virtual void removeIndividualReli(const Identifier indi, const unsigned int index) = 0;

    void removeFamilySpouse(Identifier fam, Identifier spouse);
    virtual void removeFamilyHusband(Identifier fam) = 0;
    virtual void removeFamilyWife(Identifier fam) = 0;
    virtual void removeFamilyChild(Identifier fam, Identifier chi) = 0;
    virtual void removeFamilyMarriage(Identifier fam) = 0;
    virtual void removeFamilyDivorce(Identifier fam) = 0;
    virtual void removeFamilyMarriageSource(const Identifier fam) = 0;

    virtual void removeSourceData(const Identifier& src, const CommonEventType t, unsigned int index) = 0;



    ///////////////////////////////////////////////////////////////////////////
    /// Delete records
    ///////////////////////////////////////////////////////////////////////////

    /**
     * @brief Deletes record of the Individual from Records
     *
     * Removes also all references to this individual
     *
     * @param ref   Reference to the Individual to be deleted
     */
    virtual void deleteIndividual(Identifier fam) = 0;

    /**
     * @brief Deletes record of the Family from Records
     *
     * @param ref   Reference to the Family to be deleted
     */
    virtual void deleteFamily(Identifier fam) = 0;

    virtual void deleteSubmitter(Identifier subm) = 0;

    virtual void deleteSource(Identifier src) = 0;

    virtual void deleteDatabase() = 0;

    ////////////////////////////////////////////////////
    /// NON-VIRTUAL METHODS
    ////////////////////////////////////////////////////

    BoolExtended isIndividualAlive(const Identifier indi, int maxAge, const Date date = Date::currentDate());

    /**
     * @brief Returns current surname of an Individual
     *
     * Returns married name, if married name is empty, surname is returned
     *
     * @param ref       Identifier of the Individual
     * @return QString  Current surname of the Individual
     */
    QString getIndividualNameSurnameMarriedBirth(const Identifier indi) const;

    /**
     * @brief Returns birth surname of an Individual
     *
     * Returns birth surname, if birth surname is empty, married surname is returned
     *
     * @param ref       Identifier of the Individual
     * @return QString  Current surname of the Individual
     */
    QString getIndividualNameSurnameBirthMarried(const Identifier indi) const;

    Age getIndividualAge(const Identifier indi) const;

    QVector<Identifier> getIndividualDescendants(Identifier indi) const;
    QVector<Identifier> getIndividualAncestors(Identifier indi) const;

    QStringList getStringsGivenNames(Gender g) const;
    QStringList getStringsSurnames(Gender g) const;
    QStringList getStringsPrefixes() const;
    QStringList getStringsSuffixes() const;

    QStringList getStringsPlaces() const;

    QStringList getStringsDeathCause() const;

    QStringList getStringsCities() const;
    QStringList getStringsAddress(const QString& city) const;
    QStringList getStringsEducation() const;
    QStringList getStringsOccupation() const;
    QStringList getStringsReligion() const;

private:

    QStringList getStringsEventPlaces(const CommonEventType t) const;

};


#endif // RECORD_H
