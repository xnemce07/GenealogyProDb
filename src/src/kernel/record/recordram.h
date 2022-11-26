/*!
 *  \file   recordram.h
 *  \author Eva Navratilova
 */

#ifndef RECORDRAM_H
#define RECORDRAM_H

#include <QHash>
#include <QVector>
#include <QString>
#include <algorithm>

#include "../record.h"
#include "recordRAM/primitives.h"
#include "recordRAM/head.h"
#include "recordRAM/individual.h"
#include "recordRAM/family.h"
#include "recordRAM/submitter.h"
#include "recordRAM/sourcerecord.h"
#include "recordRAM/identifier/identifierfactory.h"

/// TODO - change data to pointers - less memory usage


/**
 * @brief A main structure to store the genealogical data
 *
 * This class provides an implementation for the Record interface
 *
 * This structure is designed to be very similar to the structure of GEDCOM.
 *
 */
class RecordRAM : public Record
{


protected:
    struct compareBirthDates
    {
        compareBirthDates(const RecordRAM &data) : _data(data) {}
        const RecordRAM& _data;

        bool operator()(Identifier ref1, Identifier ref2) const;
    };

    Identifier newIndividual(Identifier ref) override;

    Identifier newFamily(Identifier ref) override;

    Identifier newSubmitter(Identifier ref) override;

    Identifier newSource(Identifier ref) override;

    ///////////////////////////////////
    /// VARIABLES

    /// Identifier Factories
    IdentifierFactory _identifierFactoryIndividual = IdentifierFactory(IdentifierType::ID_INDI); /**< Factory for Individual Identifiers */
    IdentifierFactory _identifierFactoryFamily = IdentifierFactory(IdentifierType::ID_FAM); /**< Factory for Family Identifiers */
    IdentifierFactory _identifierFactorySubmitter = IdentifierFactory(IdentifierType::ID_SUBM); /**< Factory for Submitter Identifiers */
    IdentifierFactory _identifierFactorySource = IdentifierFactory(IdentifierType::ID_SOUR); /**< Factory for Source Record Identifiers */

    /// Genealogical Data Containers
    Head head;
    //Identifier _proband; /**< Proband */
    //Identifier _current; /**< Current individual selected */
    QHash<Identifier, Individual> _individuals; /**< List of Individuals and their Identifiers as keys */
    QHash<Identifier, Family> _families; /**< List of Families and their Identifiers as keys */
    QHash<Identifier, Submitter> _submitters; /**< List of Submitters and their Identifiers as keys */
    QHash<Identifier, SourceRecord> _sources; /**< List of Source Records and their Identifiers as keys */

    // No multimedia support

    /// Family tree note
    QString _note; /**< Note to Family tree */

    // No repository support
    // No source record support


    //////////////////////////////////
    /// METHODS


    Individual constIndividual(Identifier ref) const;

    /**
     * @brief Returns reference to an Individual from the individual's identifier
     *
     * Always expects a valid individual ref! For invalid ref non-determined behaviour.
     *
     * @param ref           Valid individual identifier
     * @return Individual   Reference ro individual
     */
    Individual& individual(Identifier ref);


    Family constFamily(Identifier ref) const;

    /**
     * @brief Returns reference to a Family from the family's identifier
     *
     * Always expects a valid family ref! For invalid ref non-determined behaviour.
     *
     * @param ref       Valid family identifier
     * @return Family   Reference to family
     */
    Family &family(Identifier ref);


    Submitter constSubmitter(Identifier ref) const;
    Submitter& submitter(Identifier ref);

    SourceRecord constSource(Identifier ref) const;
    SourceRecord& source(Identifier ref);

    void setIndividualParent(Identifier chi, Identifier parent, Gender g);

    void sortByBirthDate(QVector<Identifier> &individuals) const;



public:
    /**
     * @brief Constructor
     *
     */
    RecordRAM();

    /**
     * @brief Destructor
     *
     */
    ~RecordRAM() override;


    ///////////////////////////////////////////////////////////////////////////
    /// New records (returns new id)

    Identifier newIndividual() override;
    Identifier newFamily() override;
    Identifier newSubmitter() override;
    Identifier newSource() override;

    ///////////////////////////////////////////////////////////////////////////
    /// Validators

    bool isIndividual(const Identifier indi) const override;
    bool isFamily(const Identifier fam) const override;
    bool isSubmitter(const Identifier subm) const override;
    bool isSource(const Identifier src) const override;

    bool isSubmitterEmpty(Identifier subm) const override;

    ///////////////////////////////////////////////////////////////////////////
    /// First - Last Identifier Getters

    Identifier getIdentifierIndividualFirst() const override;
    Identifier getIdentifierIndividualLast() const override;
    Identifier getIdentifierIndividualNext(Identifier &indi) const override;

    Identifier getIdentifierFamilyFirst() const override;
    Identifier getIdentifierFamilyLast() const override;
    Identifier getIdentifierFamilyNext(Identifier &fam) const override;

    Identifier getIdentifierSubmitterFirst() const override;
    Identifier getIdentifierSubmitterLast() const override;
    Identifier getIdentifierSubmitterNext(Identifier &subm) const override;

    Identifier getIdentifierSourceFirst() const override;
    Identifier getIdentifierSourceLast() const override;
    Identifier getIdentifierSourceNext(Identifier &src) const override;


    ///////////////////////////////////////////////////////////////////////////

    bool isIndividualBorn(const Identifier indi) const override;
    bool isIndividualChristened(const Identifier indi) const override;
    bool isIndividualBuried(const Identifier indi) const override;
    bool isIndividualDeceased(const Identifier indi) const override;

    bool isFamilyMarried(const Identifier fam) const override;
    bool isFamilyDivorced(const Identifier fam) const override;

    bool isSourceCited(const Identifier src) const override;


    void setIndividualDeceased(const Identifier indi, const bool deceased) override;
    void setFamilyMarried(const Identifier fam, const bool married) override;
    void setFamilyDivorced(const Identifier fam, const bool divorced) override;


    ///////////////////////////////////////////////////////////////////////////
    /// Default members

//    Identifier getIndividualProband() const;
//    void setIndividualProband(const Identifier indi);
//    void clearIndividualProband();

//    Identifier getIndividualCurrent() const;
//    void setIndividualCurrent(const Identifier indi);
//    void clearIndividualCurrent();

    ///////////////////////////////////////////////////////////////////////////
    /// Get records

    /// Head
    QString getHeadSrc() const override;
    QString getHeadSrcVersion() const override;
    QString getHeadSrcName() const override;
    QString getHeadSrcCorp() const override;
    QString getHeadSrcAddrAddress() const override;
    QString getHeadSrcAddrCity() const override;
    QString getHeadSrcAddrState() const override;
    QString getHeadSrcAddrPhone() const override;
    QString getHeadSrcAddrEmail() const override;
    QString getHeadSrcAddrWww() const override;
    QString getHeadSrcData() const override;
    Date getHeadSrcDataDate() const override;
    QString getHeadDest() const override;
    Date getHeadDate() const override;
    QTime getHeadTime() const override;
    Identifier getHeadRefSubm() const override;
    QString getHeadFile() const override;
    QString getHeadCopr() const override;
    QString getHeadGedVers() const override;
    QString getHeadGedForm() const override;
    QString getHeadCharSet() const override;
    QString getHeadCharVers() const override;
    QString getHeadLang() const override;
    QString getHeadPlac() const override;
    QString getHeadNote() const override;

    /// Submitter
    Identifier getFirstSubmitterRef() const override;
    QString getSubmitterName(const Identifier subm) const override;
    QString getSubmitterLang(const Identifier subm) const override;
    QString getSubmitterNote(const Identifier subm) const override;
    Date getSubmitterDate(const Identifier subm) const override;
    QTime getSubmitterTime(const Identifier subm) const override;

    /// Source record
    QVector<Identifier> getSourceRefs(const CommonEventType t, const Date date = Date(), const QString place = QString()) const override;

    QVector<CommonEventType> getSourceData(const Identifier src) const override;
    unsigned int getSourceDataCount(const Identifier src, const CommonEventType t) const override;

    Date getSourceDataDateFrom(const Identifier src, const CommonEventType t, unsigned int index) const override;
    Date getSourceDataDateTo(const Identifier src, const CommonEventType t, unsigned int index) const override;
    QString getSourceDataPlac(const Identifier src, const CommonEventType t, unsigned int index) const override;
    QString getSourceDataPage1(const Identifier src, const CommonEventType t, unsigned int index) const override;
    QString getSourceDataPage2(const Identifier src, const CommonEventType t, unsigned int index) const override;
    QString getSourceDataUrl(const Identifier src, const CommonEventType t, unsigned int index) const override;

    QString getSourceArchive(const Identifier src) const override;
    QString getSourceTitle(const Identifier src) const override;
    QString getSourceOriginator(const Identifier src) const override;
    QString getSourceUrl(const Identifier src) const override;


    /// Individual

    Identifier getIndividualProbandRef() const override;
    QString getIndividualNamePrefix(const Identifier indi) const override;
    QString getIndividualNameGiven(const Identifier indi) const override;
    QString getIndividualNameSurnameBirth(const Identifier indi) const override;
    QString getIndividualNameSurnameMarried(const Identifier indi) const override;
    QString getIndividualNameSuffix(const Identifier indi) const override;

    Gender getIndividualGender(const Identifier indi) const override;

    DateType getIndividualBirthDateType(const Identifier indi) const override;
    Date getIndividualBirthDate1(const Identifier indi) const override;
    Date getIndividualBirthDate2(const Identifier indi) const override;
    QString getIndividualBirthPlaceName(const Identifier indi) const override;
    Identifier getIndividualBirthObstetrix(const Identifier indi) const override;
    Identifier getIndividualBirthSourceRef(const Identifier indi) const override;
    QString getIndividualBirthSourceCitationPage(const Identifier indi) const override;
    QString getIndividualBirthSourceCitationUrl(const Identifier indi) const override;

    DateType getIndividualChristeningDateType(const Identifier indi) const override;
    Date getIndividualChristeningDate1(const Identifier indi) const override;
    Date getIndividualChristeningDate2(const Identifier indi) const override;
    Identifier getIndividualChristeningPriest(const Identifier indi) const override;
    Identifier getIndividualChristeningGodfather(const Identifier indi) const override;
    Identifier getIndividualChristeningGodmother(const Identifier indi) const override;

    DateType getIndividualDeathDateType(const Identifier indi) const override;
    Date getIndividualDeathDate1(const Identifier indi) const override;
    Date getIndividualDeathDate2(const Identifier indi) const override;
    QString getIndividualDeathPlaceName(const Identifier indi) const override;
    QString getIndividualDeathCause(const Identifier indi) const override;
    Identifier getIndividualDeathSourceRef(const Identifier indi) const override;
    QString getIndividualDeathSourceCitationPage(const Identifier indi) const override;
    QString getIndividualDeathSourceCitationUrl(const Identifier indi) const override;

    DateType getIndividualBurialDateType(const Identifier indi) const override;
    Date getIndividualBurialDate1(const Identifier indi) const override;
    Date getIndividualBurialDate2(const Identifier indi) const override;
    QString getIndividualBurialPlaceName(const Identifier indi) const override;
    Identifier getIndividualBurialPriest(const Identifier indi) const override;

    // OCCU
    unsigned int getIndividualOccuCount(const Identifier indi) const override;
    QString getIndividualOccuDescription(const Identifier indi, const unsigned int index) const override;
    DateType getIndividualOccuDateType(const Identifier indi, const unsigned int index) const  override;
    Date getIndividualOccuDate1(const Identifier indi, const unsigned int index) const override;
    Date getIndividualOccuDate2(const Identifier indi, const unsigned int index) const override;

    // EDUC
    unsigned int getIndividualEducCount(const Identifier indi) const override;
    QString getIndividualEducDescription(const Identifier indi, const unsigned int index) const override;
    DateType getIndividualEducDateType(const Identifier indi, const unsigned int index) const override;
    Date getIndividualEducDate1(const Identifier indi, const unsigned int index) const override;
    Date getIndividualEducDate2(const Identifier indi, const unsigned int index) const override;

    // RESI
    unsigned int getIndividualResiCount(const Identifier indi) const override;
    DateType getIndividualResiDateType(const Identifier indi, const unsigned int index) const override;
    Date getIndividualResiDate1(const Identifier indi, const unsigned int index) const override;
    Date getIndividualResiDate2(const Identifier indi, const unsigned int index) const override;
    QString getIndividualResiAddrCity(const Identifier indi, const unsigned int index) const override;
    QString getIndividualResiAddrAddr(const Identifier indi, const unsigned int index) const override;

    // RELI
    unsigned int getIndividualReliCount(const Identifier indi) const override;
    QString getIndividualReliDescription(const Identifier indi, const unsigned int index) const override;
    DateType getIndividualReliDateType(const Identifier indi, const unsigned int index) const override;
    Date getIndividualReliDate1(const Identifier indi, const unsigned int index) const override;
    Date getIndividualReliDate2(const Identifier indi, const unsigned int index) const override;

    // LIVING INDIVIDUAL'S CONTACT INFORMATION
    QString getIndividualPhone(const Identifier indi) const override;
    QString getIndividualEmail(const Identifier indi) const override;
    QString getIndividualWww(const Identifier indi) const override;

    QString getIndividualNote(const Identifier indi) const override;


    /// Family

    Identifier getFamilyHusband(Identifier fam) const override;
    Identifier getFamilyWife(Identifier fam) const override;
    QVector<Identifier> getFamilyChildren(Identifier fam) const override;

    // Marriage
    DateType getFamilyMarriageDateType(const Identifier fam) const override;
    Date getFamilyMarriageDate1(const Identifier fam) const override;
    Date getFamilyMarriageDate2(const Identifier fam) const override;
    QString getFamilyMarriagePlaceName(const Identifier fam) const override;
    Identifier getFamilyMarriagePriest(const Identifier fam) const override;
    Identifier getFamilyMarriageWitness1(const Identifier fam) const override;
    Identifier getFamilyMarriageWitness2(const Identifier fam) const override;
    Identifier getFamilyMarriageSourceRef(const Identifier fam) const override;
    QString getFamilyMarriageSourceCitationPage(const Identifier fam) const override;
    QString getFamilyMarriageSourceCitationUrl(const Identifier fam) const override;

    // Divorce
    DateType getFamilyDivorceDateType(const Identifier fam) const override;
    Date getFamilyDivorceDate1(const Identifier fam) const override;
    Date getFamilyDivorceDate2(const Identifier fam) const override;


    /// Linked indi-fam

    Identifier getIndividualFather(const Identifier indi) const override;
    Identifier getIndividualMother(const Identifier indi) const override;
    Identifier getIndividualParentalFamily(const Identifier indi) const override;
    QVector<Identifier> getIndividualPartners(const Identifier indi) const override;
    QVector<Identifier> getFamiliesOfIndividualParent(const Identifier ref) const override;
    Identifier getFamilyOfCouple(const Identifier indi1, const Identifier indi2) const override;
    QVector<Identifier> getChildrenOfIndividual(const Identifier indi) const override;
    QVector<Identifier> getChildrenOfCouple(const Identifier indi1, const Identifier indi2) const override;
    QVector<Identifier> getIndividualSiblings(const Identifier indi) const override;


    ///////////////////////////////////////////////////////////////////////////
    /// Set records

    void setHeadSrc(const QString src) override;
    void setHeadSrcVersion(const QString vers) override;
    void setHeadSrcName(const QString name) override;
    void setHeadSrcCorp(const QString corp) override;
    void setHeadSrcAddrAddress(const QString addr) override;
    void setHeadSrcAddrCity(const QString city) override;
    void setHeadSrcAddrState(const QString state) override;
    void setHeadSrcAddrPhone(const QString phone) override;
    void setHeadSrcAddrEmail(const QString email) override;
    void setHeadSrcAddrWww(const QString www) override;
    void setHeadSrcData(const QString data) override;
    void setHeadSrcDataDate(const Date date) override;
    void setHeadDest(const QString dest) override;
    void setHeadDate(const Date date) override;
    void setHeadTime(const QTime time) override;
    void setHeadRefSubm(const Identifier subm) override;
    void setHeadFile(const QString file) override;
    void setHeadCopr(const QString copr) override;
    void setHeadGedVers(const QString vers) override;
    void setHeadGedForm(const QString form) override;
    void setHeadCharSet(const QString charset) override;
    void setHeadCharVers(const QString vers) override;
    void setHeadLang(const QString lang) override;
    void setHeadPlac(const QString plac) override;
    void setHeadNote(const QString note) override;


    /// Submitter
    void setSubmitterName(const Identifier subm, const QString name) override;
    void setSubmitterLang(const Identifier subm, const QString lang) override;
    void setSubmitterNote(const Identifier subm, const QString note) override;
    void setSubmitterDate(const Identifier subm, const Date date) override;
    void setSubmitterTime(const Identifier subm, const QTime time) override;


    /// Source

    unsigned int setSourceData(const Identifier src, const CommonEventType t) override;

    void setSourceDataDateFrom(const Identifier src, const CommonEventType t, unsigned int index, const Date from) override;
    void setSourceDataDateTo(const Identifier src, const CommonEventType t, unsigned int index, const Date to) override;
    void setSourceDataPlac(const Identifier src, const CommonEventType t, unsigned int index, const QString plac) override;
    void setSourceDataPage1(const Identifier src, const CommonEventType t, unsigned int index, const QString page) override;
    void setSourceDataPage2(const Identifier src, const CommonEventType t, unsigned int index, const QString page) override;
    void setSourceDataUrl(const Identifier src, const CommonEventType t, unsigned int index, const QString url) override;

    void setSourceArchive(const Identifier src, const QString title) override;
    void setSourceTitle(const Identifier src, const QString title) override;
    void setSourceOriginator(const Identifier src, const QString title) override;
    void setSourceUrl(const Identifier src, const QString url) override;



    /// Individual

    void setIndividualNamePrefix(Identifier indi, QString name) override;
    void setIndividualNameGiven(Identifier indi, QString name) override;
    void setIndividualNameSurname(Identifier indi, QString name) override;
    void setIndividualNameMarname(Identifier indi, QString name) override;
    void setIndividualNameSuffix(Identifier indi, QString name) override;

    void setIndividualGender(Identifier indi, Gender g) override;

    void setIndividualBirthDateType(Identifier indi, DateType type) override;
    void setIndividualBirthDate1(Identifier indi, Date date) override;
    void setIndividualBirthDate2(Identifier indi, Date date) override;
    void setIndividualBirthPlaceName(const Identifier indi, const QString place) override;
    void setIndividualBirthObstetrix(const Identifier indi, const Identifier obstetrix) override;
    void setIndividualBirthSourceCitationRef(Identifier indi, Identifier src) override;
    void setIndividualBirthSourceCitationPage(Identifier indi, QString page) override;
    void setIndividualBirthSourceCitationUrl(Identifier indi, QString url) override;

    void setIndividualChristeningDateType(const Identifier indi, const DateType datetype) override;
    void setIndividualChristeningDate1(const Identifier indi, const Date date) override;
    void setIndividualChristeningDate2(const Identifier indi, const Date date) override;
    void setIndividualChristeningPriest(const Identifier indi, const Identifier priest) override;
    void setIndividualChristeningGodfather(const Identifier indi, const Identifier godfather) override;
    void setIndividualChristeningGodmother(const Identifier indi, const Identifier godmother) override;

    void setIndividualDeathDateType(Identifier indi, DateType date) override;
    void setIndividualDeathDate1(Identifier indi, Date date) override;
    void setIndividualDeathDate2(Identifier indi, Date date) override;
    void setIndividualDeathPlaceName(Identifier indi, QString place) override;
    void setIndividualDeathCause(Identifier indi, QString cause) override;
    void setIndividualDeathSourceCitationRef(Identifier indi, Identifier src) override;
    void setIndividualDeathSourceCitationPage(Identifier indi, QString page) override;
    void setIndividualDeathSourceCitationUrl(Identifier indi, QString url) override;

    void setIndividualBurialDateType(const Identifier indi, const DateType datetype) override;
    void setIndividualBurialDate1(const Identifier indi, const Date date) override;
    void setIndividualBurialDate2(const Identifier indi, const Date date) override;
    void setIndividualBurialPlaceName(const Identifier indi, const QString place) override;
    void setIndividualBurialPriest(const Identifier indi, const Identifier priest) override;

    // OCCU
    unsigned int setIndividualOccu(const Identifier indi) override;
    void setIndividualOccuDescription(const Identifier indi, const unsigned int index, const QString descr) override;
    void setIndividualOccuDateType(const Identifier indi, const unsigned int index, const DateType datetype) override;
    void setIndividualOccuDate1(const Identifier indi, const unsigned int index, const Date date) override;
    void setIndividualOccuDate2(const Identifier indi, const unsigned int index, const Date date) override;

    // EDUC
    unsigned int setIndividualEduc(const Identifier indi) override;
    void setIndividualEducDescription(const Identifier indi, const unsigned int index, const QString descr) override;
    void setIndividualEducDateType(const Identifier indi, const unsigned int index, const DateType datetype) override;
    void setIndividualEducDate1(const Identifier indi, const unsigned int index, const Date date) override;
    void setIndividualEducDate2(const Identifier indi, const unsigned int index, const Date date) override;

    // RESI
    unsigned int setIndividualResi(const Identifier indi) override;
    void setIndividualResiDateType(const Identifier indi, const unsigned int index, const DateType datetype) override;
    void setIndividualResiDate1(const Identifier indi, const unsigned int index, const Date date) override;
    void setIndividualResiDate2(const Identifier indi, const unsigned int index, const Date date) override;
    void setIndividualResiAddrCity(const Identifier indi, const unsigned int index, const QString city) override;
    void setIndividualResiAddrAddr(const Identifier indi, const unsigned int index, const QString addr) override;

    // RELI
    unsigned int setIndividualReli(const Identifier indi) override;
    void setIndividualReliDescription(const Identifier indi, const unsigned int index, const QString descr) override;
    void setIndividualReliDateType(const Identifier indi, const unsigned int index, const DateType datetype) override;
    void setIndividualReliDate1(const Identifier indi, const unsigned int index, const Date date) override;
    void setIndividualReliDate2(const Identifier indi, const unsigned int index, const Date date) override;

    // LIVING INDIVIDUAL'S CONTACT INFORMATION
    void setIndividualPhone(const Identifier indi, const QString phone) override;
    void setIndividualEmail(const Identifier indi, const QString email) override;
    void setIndividualWww(const Identifier indi, const QString www) override;

    // Note
    void setIndividualNote(const Identifier indi, const QString note) override;


    /// Family

    void setFamilyHusband(const Identifier fam, const Identifier husb) override;
    void setFamilyWife(const Identifier fam, const Identifier wife) override;
    void setFamilyChild(const Identifier fam, const Identifier chi) override;

    void setFamilyMarried(const Identifier fam) override;
    void setFamilyMarriageDateType(const Identifier fam, const DateType type) override;
    void setFamilyMarriageDate1(const Identifier fam, const Date date) override;
    void setFamilyMarriageDate2(const Identifier fam, const Date date) override;
    void setFamilyMarriagePlaceName(const Identifier fam, const QString plac) override;
    void setFamilyMarriagePriest(const Identifier fam, const Identifier priest) override;
    void setFamilyMarriageWitness1(const Identifier fam, const Identifier witness) override;
    void setFamilyMarriageWitness2(const Identifier fam, const Identifier witness) override;
    void setFamilyMarriageSourceCitationRef(const Identifier fam, const Identifier src) override;
    void setFamilyMarriageSourceCitationPage(const Identifier fam, const QString page) override;
    void setFamilyMarriageSourceCitationUrl(const Identifier fam, const QString url) override;

    void setFamilyDivorced(const Identifier fam) override;
    void setFamilyDivorceDateType(const Identifier fam, const DateType type) override;
    void setFamilyDivorceDate1(const Identifier fam, const Date date) override;
    void setFamilyDivorceDate2(const Identifier fam, const Date date) override;
    void setFamilyDivorcePlaceName(const Identifier fam, const QString plac) override;


    /// Linked indi-fam
    void setIndividualFather(const Identifier chi, const Identifier father) override;
    void setIndividualMother(const Identifier chi, const Identifier mother) override;
    void setIndividualCouple(const Identifier husb, const Identifier wife) override;
    void setIndividualChild(const Identifier indi, const Identifier chi) override;


    ///////////////////////////////////////////////////////////////////////////
    /// Swap record order
    ///////////////////////////////////////////////////////////////////////////

    void swapIndividualOccu(Identifier indi, const unsigned int index1, const unsigned int index2) override;
    void swapIndividualEduc(Identifier indi, const unsigned int index1, const unsigned int index2) override;
    void swapIndividualResi(Identifier indi, const unsigned int index1, const unsigned int index2) override;
    void swapIndividualReli(Identifier indi, const unsigned int index1, const unsigned int index2) override;

    void swapFamilies(const Identifier fam1, const Identifier fam2) override;

    ///////////////////////////////////////////////////////////////////////////
    /// Remove records

    void removeIndividualBirth(Identifier indi) override;
    void removeIndividualChristening(Identifier indi) override;
    void removeIndividualDeath(Identifier indi) override;
    void removeIndividualBurial(Identifier indi) override;
    void removeIndividualBirthSource(const Identifier indi) override;
    void removeIndividualDeathSource(const Identifier indi) override;
    void removeIndividualOccu(const Identifier indi, const unsigned int index) override;
    void removeIndividualEduc(const Identifier indi, const unsigned int index) override;
    void removeIndividualResi(const Identifier indi, const unsigned int index) override;
    void removeIndividualReli(const Identifier indi, const unsigned int index) override;

    void removeFamilyHusband(Identifier fam) override;
    void removeFamilyWife(Identifier fam) override;
    void removeFamilyChild(Identifier fam, Identifier chi) override;
    void removeFamilyMarriage(Identifier fam) override;
    void removeFamilyDivorce(Identifier fam) override;
    void removeFamilyMarriageSource(const Identifier fam) override;

    void removeSourceData(const Identifier& src, const CommonEventType t, unsigned int index) override;

    ///////////////////////////////////////////////////////////////////////////
    /// Delete records
    /**
     * @brief
     *
     * @param ref
     */
    void deleteIndividual(Identifier indi) override;
    /**
     * @brief
     *
     * @param ref
     */
    void deleteFamily(Identifier fam) override;

    void deleteSubmitter(Identifier subm) override;

    void deleteSource(Identifier src) override;

    void deleteDatabase() override;

};


#endif // RECORDRAM_H
