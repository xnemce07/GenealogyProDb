/*!
 *  \file   recordram.cpp
 *  \author Eva Navratilova
 */

#include "recordram.h"

///////////////////////////////////////////////////////////////////////////////
/// PRIVATE

Identifier RecordRAM::newIndividual(Identifier ref)
{
    if(!this->isIndividual(ref))
    {
        ref = this->_identifierFactoryIndividual.importIdentifier(ref);

        if(ref.isValid())
        {
            Individual indi(ref);
//            if(this->_individuals.isEmpty())
//            {
//                this->setIndividualProband(ref);
//            }
            this->_individuals.insert(ref, indi);
        }
    }
    return ref;
}

Identifier RecordRAM::newFamily(Identifier ref)
{
    if(!this->isFamily(ref))
    {
        ref = this->_identifierFactoryFamily.importIdentifier(ref);

        if(ref.isValid())
        {
            Family fam(ref);
            this->_families.insert(ref, fam);
        }
    }
    return ref;
}

Identifier RecordRAM::newSubmitter(Identifier ref)
{
    if(!this->isSubmitter(ref))
    {
        ref = this->_identifierFactorySubmitter.importIdentifier(ref);

        if(ref.isValid())
        {
            Submitter subm(ref);
            this->_submitters.insert(ref, subm);
        }
    }
    return ref;
}

Identifier RecordRAM::newSource(Identifier ref)
{
    if(!this->isSource(ref))
    {
        ref = this->_identifierFactorySource.importIdentifier(ref);

        if(ref.isValid())
        {
            SourceRecord src(ref);
            this->_sources.insert(ref, src);
        }
    }
    return ref;
}

Individual RecordRAM::constIndividual(Identifier ref) const
{
    QHash<Identifier, Individual>::const_iterator it = this->_individuals.find(ref);
    // If not found, returns this->individuals.end()!!!
    return *it;
}

Individual& RecordRAM::individual(Identifier ref)
{
    QHash<Identifier, Individual>::iterator it = this->_individuals.find(ref);
    // If not found, returns this->individuals.end()!!!
    return *it;
}

Family RecordRAM::constFamily(Identifier ref) const
{
    QHash<Identifier, Family>::const_iterator it = this->_families.find(ref);
    // If not found, returns this->families.end()!!!
    return *it;
}

Family& RecordRAM::family(Identifier ref)
{
    QHash<Identifier, Family>::iterator it = this->_families.find(ref);
    // If not found, returns this->families.end()!!!
    return *it;
}

Submitter RecordRAM::constSubmitter(Identifier ref) const
{
    return *this->_submitters.constFind(ref);
}

Submitter &RecordRAM::submitter(Identifier ref)
{
    return *this->_submitters.find(ref);
}

SourceRecord RecordRAM::constSource(Identifier ref) const
{
    return *this->_sources.constFind(ref);
}

SourceRecord &RecordRAM::source(Identifier ref)
{
    return *this->_sources.find(ref);
}

QVector<Identifier> RecordRAM::getFamiliesOfIndividualParent(const Identifier ref) const
{
    QVector<Identifier> fams;
    for(auto it=this->_families.cbegin(); it!=this->_families.cend(); it++)
    {
        if(it->getHusband() == ref)
        {
            fams.push_back(it->getRef());
        }
        else if(it->getWife() == ref)
        {
            fams.push_back(it->getRef());
        }
    }
    return fams;
}

Identifier RecordRAM::getFamilyOfCouple(const Identifier indi1, const Identifier indi2) const
{
    for(auto it=this->_families.cbegin(); it!=this->_families.cend(); it++)
    {
        if(it->getHusband() == indi1)
        {
            if(it->getWife() == indi2)
                return it->getRef();
        }
        else if(it->getHusband() == indi2)
        {
            if(it->getWife() == indi1)
                return it->getRef();
        }
    }
    return Identifier();
}

void RecordRAM::setIndividualParent(Identifier chi, Identifier parent, Gender g)
{
    /// TODO - CHECKUJ, zda v jiz existujici rodine neexistuji zadne deti - pokud ne, je mozne editovat priimo na miste bez dodatecneho mazani!!!
    /// !!!!!!!!!!!!!!!!!!!! ALE NEJPRVE KROK ZA KROKEM DEBUG !!!!!!!!!!!!!!!!!!!!!!!!!!


    // Child or Father are not valid Individuals -> Do nothing
    if(this->isIndividual(chi) && (this->isIndividual(parent) || !parent.isValid()))
    {
        bool isParentFather = (g == Gender::MALE);
        bool isParentMother = (g == Gender::FEMALE);
        Identifier father, mother;
        Identifier currFam, newFam;
        Family *newFamInst;
        currFam = this->getIndividualParentalFamily(chi);
        // Child is not assigned to a family ( => this is the first parent to be asigned )
        if(this->isFamily(currFam))
        {
            // Parent and child are already a family
            if(isParentFather)
            {
                if(this->family(currFam).getHusband() == parent)
                    return;
            }
            else if(isParentMother)
            {
                if(this->family(currFam).getWife() == parent)
                    return;
            }
            // Remove child from family and check for its emptiness
            if(isParentFather)
            {
                father = parent;
                mother = this->constFamily(currFam).getWife();
            }else if(isParentMother)
            {
                father = this->constFamily(currFam).getHusband();
                mother = parent;
            }
            this->family(currFam).removeChild(chi);
            if(this->family(currFam).isEmpty())
                this->deleteFamily(currFam);
            // Look for a family with Husband and Wife
            currFam = this->getFamilyOfCouple(father, mother);
            // Family does not yet exist -> Create and initialize a new one
            // (but only if at least one of the parents is a valid person)
            if(! this->isFamily(currFam))
            {
                currFam = this->newFamily();
                newFamInst = &this->family(currFam);
                newFamInst->setHusband(father);
                newFamInst->setWife(mother);
                newFamInst->setChild(chi);
                if(newFamInst->isEmpty())
                {
                    this->deleteFamily(currFam);
                }
            }
            // Family already exists -> add child
            else
                this->family(currFam).setChild(chi);
        }
        // Child is assigned to a family
        else
        {
            // Find an existing family with said parent
            if(isParentFather)
            {
                father = parent;
            }
            else if(isParentMother)
            {
                mother = parent;
            }
            newFam = this->getFamilyOfCouple(father, mother);
            // Family was found -> add child to family
            if(this->isFamily(newFam))
            {
                this->family(newFam).setChild(chi);
            }
            // Family was not found -> construct new one (if parent is a person (eg. not removing parent))
            else if(this->isIndividual(parent))
            {
                newFamInst = &this->family(this->newFamily());
                if(isParentFather)
                {
                    newFamInst->setHusband(parent);
                }
                else if(isParentMother)
                {
                    newFamInst->setWife(parent);
                }
                newFamInst->setChild(chi);
            }
            // Removing nonexistent father - do nothing
            else {}
        }
    }
}

void RecordRAM::sortByBirthDate(QVector<Identifier> &individuals) const
{
    std::sort(individuals.begin(), individuals.end(), compareBirthDates(*this));
}


///////////////////////////////////////////////////////////////////////////////
/// PUBLIC
RecordRAM::RecordRAM()
{

}

RecordRAM::~RecordRAM()
{

}


/// New records
Identifier RecordRAM::newIndividual()
{
    Identifier ref = _identifierFactoryIndividual.newIdentifier();
    return this->newIndividual(ref);
}

Identifier RecordRAM::newFamily()
{
    Identifier ref = _identifierFactoryFamily.newIdentifier();
    return this->newFamily(ref);
}

Identifier RecordRAM::newSubmitter()
{
    Identifier ref = _identifierFactorySubmitter.newIdentifier();
    return this->newSubmitter(ref);
}

Identifier RecordRAM::newSource()
{
    Identifier ref = _identifierFactorySource.newIdentifier();
    return this->newSource(ref);
}


/// Validators

bool RecordRAM::isIndividual(const Identifier indi) const{
    QHash<Identifier, Individual>::const_iterator it = this->_individuals.find(indi);
    return it != this->_individuals.end();
}

bool RecordRAM::isFamily(const Identifier fam) const{
    QHash<Identifier, Family>::const_iterator it = this->_families.find(fam);
    return it != this->_families.end();
}

bool RecordRAM::isSubmitter(const Identifier subm) const
{
    QHash<Identifier, Submitter>::const_iterator it = this->_submitters.find(subm);
    return it != this->_submitters.end();
}

bool RecordRAM::isSource(const Identifier src) const
{
    QHash<Identifier, SourceRecord>::const_iterator it = this->_sources.find(src);
    return it != this->_sources.end();
}

bool RecordRAM::isSubmitterEmpty(Identifier subm) const
{
    if(this->isSubmitter(subm))
    {
        return this->constSubmitter(subm).isEmpty();
    }
    return true;
}

Identifier RecordRAM::getIdentifierIndividualFirst() const
{
    return _identifierFactoryIndividual.firstIdentifier();
}

Identifier RecordRAM::getIdentifierIndividualLast() const
{
    return _identifierFactoryIndividual.lastIdentifier();
}

Identifier RecordRAM::getIdentifierIndividualNext(Identifier &indi) const
{
    return _identifierFactoryIndividual.nextIdentifier(indi);
}

Identifier RecordRAM::getIdentifierFamilyFirst() const
{
    return _identifierFactoryFamily.firstIdentifier();
}

Identifier RecordRAM::getIdentifierFamilyLast() const
{
    return _identifierFactoryFamily.lastIdentifier();
}

Identifier RecordRAM::getIdentifierFamilyNext(Identifier &fam) const
{
    return _identifierFactoryFamily.nextIdentifier(fam);
}

Identifier RecordRAM::getIdentifierSubmitterFirst() const
{
    return _identifierFactorySubmitter.firstIdentifier();
}

Identifier RecordRAM::getIdentifierSubmitterLast() const
{
    return _identifierFactorySubmitter.lastIdentifier();
}

Identifier RecordRAM::getIdentifierSubmitterNext(Identifier &subm) const
{
    return _identifierFactorySubmitter.nextIdentifier(subm);
}

Identifier RecordRAM::getIdentifierSourceFirst() const
{
    return _identifierFactorySource.firstIdentifier();
}

Identifier RecordRAM::getIdentifierSourceLast() const
{
    return _identifierFactorySource.lastIdentifier();
}

Identifier RecordRAM::getIdentifierSourceNext(Identifier &src) const
{
    return _identifierFactorySource.nextIdentifier(src);
}

bool RecordRAM::isIndividualBorn(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).isBorn();
    }
    else
        return false;
}

bool RecordRAM::isIndividualChristened(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).isChristened();
    }
    else
        return false;
}

bool RecordRAM::isIndividualBuried(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).isBuried();
    }
    else
        return false;
}

bool RecordRAM::isIndividualDeceased(const Identifier indi) const
{
    if(this->isIndividual(indi))
        return this->constIndividual(indi).isDeceased();
    else
        return false;
}

bool RecordRAM::isFamilyMarried(const Identifier fam) const
{
    if(this->isFamily(fam))
        return this->constFamily(fam).isMarried();
    else
        return false;
}

bool RecordRAM::isFamilyDivorced(const Identifier fam) const
{
    if(this->isFamily(fam))
        return this->constFamily(fam).isDivorced();
    else
        return false;
}

bool RecordRAM::isSourceCited(const Identifier src) const
{
    for(auto it = this->_individuals.constBegin(); it != this->_individuals.constEnd(); it++)
    {
        if(it->isBorn())
        {
            auto cit = it->constBirth().constDetail().constSourceCitation();
            if(cit.getRef() == src)
            {
                return true;
            }
        }
        if(it->isDeceased())
        {
            auto cit = it->constDeath().constDetail().constSourceCitation();
            if(cit.getRef() == src)
            {
                return true;
            }
        }
    }
    for(auto it = this->_families.constBegin(); it != this->_families.constEnd(); it++)
    {
        if(it->isMarried())
        {
            auto cit = it->constMarriage().constDetail().constSourceCitation();
            if(cit.getRef() == src)
            {
                return true;
            }
        }
    }
    return false;
}

void RecordRAM::setIndividualDeceased(const Identifier indi, const bool deceased)
{
    if(this->isIndividual(indi))
    {
        if(deceased)
        {
            this->individual(indi).setDeath();
        }
        else
        {
            this->individual(indi).removeDeath();
        }
    }
}

void RecordRAM::setFamilyMarried(const Identifier fam, const bool married)
{
    if(this->isFamily(fam))
    {
        if(married)
        {
            this->family(fam).setMarriage();
        }
        else
        {
            this->family(fam).removeMarriage();
        }
    }
}

void RecordRAM::setFamilyDivorced(const Identifier fam, const bool divorced)
{
    if(this->isFamily(fam))
    {
        if(divorced)
        {
            this->family(fam).setDivorce();
        }
        else
        {
            this->family(fam).removeDivorce();
        }
    }
}

//Identifier RecordRAM::getIndividualProband() const
//{
//    return this->_proband;
//}

//void RecordRAM::setIndividualProband(const Identifier indi)
//{
//    // Check if isIndividual?
//    this->_proband = indi;
//}

//void RecordRAM::clearIndividualProband()
//{
//    this->_proband = Identifier();
//}

//Identifier RecordRAM::getIndividualCurrent() const
//{
//    return this->_current;
//}

//void RecordRAM::setIndividualCurrent(const Identifier indi)
//{
//    // Check if isIndividual?
//    this->_current = indi;
//}

//void RecordRAM::clearIndividualCurrent()
//{
//    this->_current = Identifier();
//}

QString RecordRAM::getHeadSrc() const
{
    return this->head.getSrc();
}

QString RecordRAM::getHeadSrcVersion() const
{
    return this->head.getSrcVersion();
}

QString RecordRAM::getHeadSrcName() const
{
    return this->head.getSrcName();
}

QString RecordRAM::getHeadSrcCorp() const
{
    return this->head.getSrcCorp();
}

QString RecordRAM::getHeadSrcAddrAddress() const
{
    return this->head.constSrcCorpAddr().getAddress();
}

QString RecordRAM::getHeadSrcAddrCity() const
{
    return this->head.constSrcCorpAddr().getCity();
}

QString RecordRAM::getHeadSrcAddrState() const
{
    return this->head.constSrcCorpAddr().getState();
}

QString RecordRAM::getHeadSrcAddrPhone() const
{
    return this->head.constSrcCorpAddr().getPhone();
}

QString RecordRAM::getHeadSrcAddrEmail() const
{
    return this->head.constSrcCorpAddr().getEmail();
}

QString RecordRAM::getHeadSrcAddrWww() const
{
    return this->head.constSrcCorpAddr().getWww();
}

QString RecordRAM::getHeadSrcData() const
{
    return this->head.getSrcData();
}

Date RecordRAM::getHeadSrcDataDate() const
{
    return this->head.getSrcDataDate();
}

QString RecordRAM::getHeadDest() const
{
    return this->head.getDest();
}

Date RecordRAM::getHeadDate() const
{
    return this->head.getDate();
}

QTime RecordRAM::getHeadTime() const
{
    return this->head.getTime();
}

Identifier RecordRAM::getHeadRefSubm() const
{
    return this->head.getRefSubm();
}

QString RecordRAM::getHeadFile() const
{
    return this->head.getFile();
}

QString RecordRAM::getHeadCopr() const
{
    return this->head.getCopr();
}

QString RecordRAM::getHeadGedVers() const
{
    return this->head.getGedVers();
}

QString RecordRAM::getHeadGedForm() const
{
    return this->head.getGedForm();
}

QString RecordRAM::getHeadCharSet() const
{
    return this->head.getCharSet();
}

QString RecordRAM::getHeadCharVers() const
{
    return this->head.getCharVers();
}

QString RecordRAM::getHeadLang() const
{
    return this->head.getLang();
}

QString RecordRAM::getHeadPlac() const
{
    return this->head.getPlac();
}

QString RecordRAM::getHeadNote() const
{
    return this->head.getNote();
}

Identifier RecordRAM::getFirstSubmitterRef() const
{
    if(this->_submitters.empty())
        return Identifier();
    else
        return this->_submitters.begin().key();
}

QString RecordRAM::getSubmitterName(const Identifier subm) const
{
    if(this->isSubmitter(subm))
        return this->constSubmitter(subm).getName();
    else
        return QString();
}

QString RecordRAM::getSubmitterLang(const Identifier subm) const
{
    if(this->isSubmitter(subm))
        return this->constSubmitter(subm).getLang();
    else
        return QString();
}

QString RecordRAM::getSubmitterNote(const Identifier subm) const
{
    if(this->isSubmitter(subm))
        return this->constSubmitter(subm).getNote();
    else
        return QString();
}

Date RecordRAM::getSubmitterDate(const Identifier subm) const
{
    if(this->isSubmitter(subm))
        return this->constSubmitter(subm).getDate();
    else
        return Date();
}

QTime RecordRAM::getSubmitterTime(const Identifier subm) const
{
    if(this->isSubmitter(subm))
        return this->constSubmitter(subm).getTime();
    else
        return QTime();
}

QVector<Identifier> RecordRAM::getSourceRefs(const CommonEventType t, const Date date, const QString place) const
{
    QVector<Identifier> validSources;
    for(auto src = this->_sources.constBegin(); src != this->_sources.constEnd(); src++)
    {
        // If Source contains data of suitable type
        unsigned int count = this->getSourceDataCount(src.key(), t);
        for(unsigned int index = 0; index < count; index++)
        {
            if(src->isDateContained(t, index, date) &&
               ((src->getDataPlac(t, index) == place) || (place.isEmpty())))
            {
                validSources.append(src->getRef());
                break;
            }
        }
    }
    return validSources;
}

QVector<CommonEventType> RecordRAM::getSourceData(const Identifier src) const
{
    QVector <CommonEventType> data;
    if(this->isSource(src))
    {
        data = this->constSource(src).getData();
    }
    return data;
}

unsigned int RecordRAM::getSourceDataCount(const Identifier src, const CommonEventType t) const
{
    if(this->isSource(src))
    {
        return this->constSource(src).getDataCount(t);
    }
    return 0;
}



Date RecordRAM::getSourceDataDateFrom(const Identifier src, const CommonEventType t, unsigned int index) const
{
    Date d;
    if(this->isSource(src))
    {
        d = this->constSource(src).getDataDateFrom(t, index);
    }
    return d;
}


Date RecordRAM::getSourceDataDateTo(const Identifier src, const CommonEventType t, unsigned int index) const
{
    Date d;
    if(this->isSource(src))
    {
        d = this->constSource(src).getDataDateTo(t, index);
    }
    return d;
}

QString RecordRAM::getSourceDataPlac(const Identifier src, const CommonEventType t, unsigned int index) const
{
    QString plac;
    if(this->isSource(src))
    {
        plac = this->constSource(src).getDataPlac(t, index);
    }
    return plac;
}

QString RecordRAM::getSourceDataPage1(const Identifier src, const CommonEventType t, unsigned int index) const
{
    QString page;
    if(this->isSource(src))
    {
        page = this->constSource(src).getDataPage1(t, index);
    }
    return page;
}

QString RecordRAM::getSourceDataPage2(const Identifier src, const CommonEventType t, unsigned int index) const
{
    QString page;
    if(this->isSource(src))
    {
        page = this->constSource(src).getDataPage2(t, index);
    }
    return page;
}

QString RecordRAM::getSourceDataUrl(const Identifier src, const CommonEventType t, unsigned int index) const
{
    QString url;
    if(this->isSource(src))
    {
        url = this->constSource(src).getDataUrl(t, index);
    }
    return url;
}

QString RecordRAM::getSourceArchive(const Identifier src) const
{
    QString archive;
    if(this->isSource(src))
    {
        archive = this->constSource(src).getArchive();
    }
    return archive;
}

QString RecordRAM::getSourceTitle(const Identifier src) const
{
    QString title;
    if(this->isSource(src))
    {
        title = this->constSource(src).getSignature();
    }
    return title;
}

QString RecordRAM::getSourceOriginator(const Identifier src) const
{
    QString originator;
    if(this->isSource(src))
    {
        originator = this->constSource(src).getOriginator();
    }
    return originator;
}

QString RecordRAM::getSourceUrl(const Identifier src) const
{
    QString url;
    if(this->isSource(src))
        url = this->constSource(src).getUrl();
    return url;
}

Identifier RecordRAM::getIndividualProbandRef() const
{
    /// TODO - test if this is really first inserted!!!!
    /// TODO - is this really necessary???
    return this->_individuals.constBegin().key();
}

QString RecordRAM::getIndividualNamePrefix(const Identifier indi) const
{
    if(this->isIndividual(indi))
        return this->constIndividual(indi).constName().getPrefix();
    return QString();
}



/// Get records
QString RecordRAM::getIndividualNameGiven(const Identifier indi) const
{
    if(this->isIndividual(indi))
        return this->constIndividual(indi).constName().getGiven();
    return QString();
}

QString RecordRAM::getIndividualNameSurnameBirth(const Identifier indi) const
{
    if(this->isIndividual(indi))
        return this->constIndividual(indi).constName().getSurname();
    return QString();
}

QString RecordRAM::getIndividualNameSurnameMarried(const Identifier indi) const
{
    if(this->isIndividual(indi))
        return this->constIndividual(indi).constName().getMarname();
    return QString();
}

QString RecordRAM::getIndividualNameSuffix(const Identifier indi) const
{
    if(this->isIndividual(indi))
        return this->constIndividual(indi).constName().getSuffix();
    return QString();
}

Gender RecordRAM::getIndividualGender(const Identifier indi) const
{
    if(this->isIndividual(indi))
        return this->constIndividual(indi).getGender();
    return Gender::UNDET;
}

DateType RecordRAM::getIndividualBirthDateType(const Identifier indi) const
{
    if(this->isIndividual(indi))
        return this->constIndividual(indi).constBirth().constDetail().getDateType();
    return DateType::EMPT;
}

Date RecordRAM::getIndividualBirthDate1(const Identifier indi) const
{
    if(this->isIndividual(indi))
        return this->constIndividual(indi).constBirth().constDetail().getDate1();
    return Date();
}

Date RecordRAM::getIndividualBirthDate2(const Identifier indi) const
{
    if(this->isIndividual(indi))
        return this->constIndividual(indi).constBirth().constDetail().getDate2();
    return Date();
}

QString RecordRAM::getIndividualBirthPlaceName(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constBirth().constDetail().constPlace().getName();
    }
    return QString();
}

Identifier RecordRAM::getIndividualBirthObstetrix(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constBirth().constDetail().getWitness1();
    }
    return Identifier();
}

Identifier RecordRAM::getIndividualBirthSourceRef(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constBirth().constDetail().constSourceCitation().getRef();
    }
    return Identifier();
}

QString RecordRAM::getIndividualBirthSourceCitationPage(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        auto src = this->constIndividual(indi).constBirth().constDetail().constSourceCitation();
        if(this->isSource(src.getRef()))
            return src.getPage();
    }
    return QString();
}

QString RecordRAM::getIndividualBirthSourceCitationUrl(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        auto src = this->constIndividual(indi).constBirth().constDetail().constSourceCitation();
        if(this->isSource(src.getRef()))
            return src.getUrl();
    }
    return QString();
}

DateType RecordRAM::getIndividualChristeningDateType(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constChristening().constDetail().getDateType();
    }
    return DateType::EMPT;
}

Date RecordRAM::getIndividualChristeningDate1(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constChristening().constDetail().getDate1();
    }
    return Date();
}

Date RecordRAM::getIndividualChristeningDate2(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constChristening().constDetail().getDate2();
    }
    return Date();
}

Identifier RecordRAM::getIndividualChristeningPriest(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constChristening().constDetail().getPriest();
    }
    return Identifier();
}

Identifier RecordRAM::getIndividualChristeningGodfather(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constChristening().constDetail().getWitness1();
    }
    return Identifier();
}

Identifier RecordRAM::getIndividualChristeningGodmother(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constChristening().constDetail().getWitness2();
    }
    return Identifier();
}

DateType RecordRAM::getIndividualDeathDateType(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constDeath().constDetail().getDateType();
    }
    return DateType::EMPT;
}

Date RecordRAM::getIndividualDeathDate1(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constDeath().constDetail().getDate1();
    }
    return Date();
}

Date RecordRAM::getIndividualDeathDate2(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constDeath().constDetail().getDate2();
    }
    return Date();
}

QString RecordRAM::getIndividualDeathPlaceName(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constDeath().constDetail().constPlace().getName();
    }
    return QString();
}

QString RecordRAM::getIndividualDeathCause(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constDeath().constDetail().getCause();
    }
    return QString();
}

Identifier RecordRAM::getIndividualDeathSourceRef(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constDeath().constDetail().constSourceCitation().getRef();
    }
    return  Identifier();
}

QString RecordRAM::getIndividualDeathSourceCitationPage(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        auto src = this->constIndividual(indi).constDeath().constDetail().constSourceCitation();
        if(this->isSource(src.getRef()))
            return src.getPage();
    }
    return QString();
}

QString RecordRAM::getIndividualDeathSourceCitationUrl(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        auto src = this->constIndividual(indi).constDeath().constDetail().constSourceCitation();
        if(this->isSource(src.getRef()))
            return src.getUrl();
    }
    return QString();
}

DateType RecordRAM::getIndividualBurialDateType(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constBurial().constDetail().getDateType();
    }
    return DateType::EMPT;
}

Date RecordRAM::getIndividualBurialDate1(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constBurial().constDetail().getDate1();
    }
    return Date();
}

Date RecordRAM::getIndividualBurialDate2(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constBurial().constDetail().getDate2();
    }
    return Date();
}

QString RecordRAM::getIndividualBurialPlaceName(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constBurial().constDetail().constPlace().getName();
    }
    return QString();
}

Identifier RecordRAM::getIndividualBurialPriest(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constBurial().constDetail().getPriest();
    }
    return Identifier();
}

unsigned int RecordRAM::getIndividualOccuCount(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).getOccuCount();
    }
    return 0;
}

QString RecordRAM::getIndividualOccuDescription(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constOccupation(index).getDescription();
    }
    return QString();
}

DateType RecordRAM::getIndividualOccuDateType(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constOccupation(index).constDetail().getDateType();
    }
    return DateType::EMPT;
}

Date RecordRAM::getIndividualOccuDate1(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constOccupation(index).constDetail().getDate1();
    }
    return Date();
}

Date RecordRAM::getIndividualOccuDate2(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constOccupation(index).constDetail().getDate2();
    }
    return Date();
}

unsigned int RecordRAM::getIndividualEducCount(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).getEducCount();
    }
    return 0;
}

QString RecordRAM::getIndividualEducDescription(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constEducation(index).getDescription();
    }
    return QString();
}

DateType RecordRAM::getIndividualEducDateType(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constEducation(index).constDetail().getDateType();
    }
    return DateType::EMPT;
}

Date RecordRAM::getIndividualEducDate1(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constEducation(index).constDetail().getDate1();
    }
    return Date();
}

Date RecordRAM::getIndividualEducDate2(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constEducation(index).constDetail().getDate2();
    }
    return Date();
}

unsigned int RecordRAM::getIndividualResiCount(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).getResiCount();
    }
    return 0;
}

DateType RecordRAM::getIndividualResiDateType(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constResidence(index).constDetail().getDateType();
    }
    return DateType::EMPT;
}

Date RecordRAM::getIndividualResiDate1(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constResidence(index).constDetail().getDate1();
    }
    return Date();
}

Date RecordRAM::getIndividualResiDate2(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constResidence(index).constDetail().getDate2();
    }
    return Date();
}

QString RecordRAM::getIndividualResiAddrCity(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constResidence(index).constDetail().constAddress().getCity();
    }
    return QString();
}

QString RecordRAM::getIndividualResiAddrAddr(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constResidence(index).constDetail().constAddress().getAddress();
    }
    return QString();
}

unsigned int RecordRAM::getIndividualReliCount(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).getReliCount();
    }
    return 0;
}

QString RecordRAM::getIndividualReliDescription(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constReligion(index).getDescription();
    }
    return QString();
}

DateType RecordRAM::getIndividualReliDateType(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constReligion(index).constDetail().getDateType();
    }
    return DateType::EMPT;
}

Date RecordRAM::getIndividualReliDate1(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constReligion(index).constDetail().getDate1();
    }
    return Date();
}

Date RecordRAM::getIndividualReliDate2(const Identifier indi, const unsigned int index) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constReligion(index).constDetail().getDate2();
    }
    return Date();
}

QString RecordRAM::getIndividualPhone(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constAddress().getPhone();
    }
    return QString();
}

QString RecordRAM::getIndividualEmail(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constAddress().getEmail();
    }
    return QString();
}

QString RecordRAM::getIndividualWww(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).constAddress().getWww();
    }
    return QString();
}

QString RecordRAM::getIndividualNote(const Identifier indi) const
{
    if(this->isIndividual(indi))
    {
        return this->constIndividual(indi).getNote();
    }
    return QString();
}

Identifier RecordRAM::getFamilyHusband(Identifier fam) const
{
    if(this->isFamily(fam))
    {
        return this->constFamily(fam).getHusband();
    }
    return Identifier();
}

Identifier RecordRAM::getFamilyWife(Identifier fam) const
{
    if(this->isFamily(fam))
    {
        return this->constFamily(fam).getWife();
    }
    return Identifier();
}

QVector<Identifier> RecordRAM::getFamilyChildren(Identifier fam) const
{
    if(this->isFamily(fam))
    {
        QVector<Identifier> children = this->constFamily(fam).getChildren();
        this->sortByBirthDate(children);
        return children;
    }
    return QVector<Identifier>();
}

DateType RecordRAM::getFamilyMarriageDateType(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isMarried())
            return f.constMarriage().constDetail().getDateType();
    }
    return DateType::EMPT;
}


Date RecordRAM::getFamilyMarriageDate1(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isMarried())
            return f.constMarriage().constDetail().getDate1();
    }
    return Date();
}

Date RecordRAM::getFamilyMarriageDate2(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isMarried())
            return f.constMarriage().constDetail().getDate2();
    }
    return Date();
}

QString RecordRAM::getFamilyMarriagePlaceName(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isMarried())
            return f.constMarriage().constDetail().constPlace().getName();
    }
    return QString();
}

Identifier RecordRAM::getFamilyMarriagePriest(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isMarried())
            return f.constMarriage().constDetail().getPriest();
    }
    return Identifier();
}

Identifier RecordRAM::getFamilyMarriageWitness1(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isMarried())
            return f.constMarriage().constDetail().getWitness1();
    }
    return Identifier();
}

Identifier RecordRAM::getFamilyMarriageWitness2(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isMarried())
            return f.constMarriage().constDetail().getWitness2();
    }
    return Identifier();
}

Identifier RecordRAM::getFamilyMarriageSourceRef(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isMarried())
        {
            return f.constMarriage().constDetail().constSourceCitation().getRef();
        }
    }
    return Identifier();
}

QString RecordRAM::getFamilyMarriageSourceCitationPage(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isMarried())
        {
            auto src = f.constMarriage().constDetail().constSourceCitation();
            if(this->isSource(src.getRef()))
                return src.getPage();
        }
    }
    return QString();
}

QString RecordRAM::getFamilyMarriageSourceCitationUrl(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isMarried())
        {
            auto src = f.constMarriage().constDetail().constSourceCitation();
            if(this->isSource(src.getRef()))
                return src.getUrl();
        }
    }
    return QString();
}

DateType RecordRAM::getFamilyDivorceDateType(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isDivorced())
            return f.constDivorce().constDetail().getDateType();
    }
    return DateType::EMPT;
}

Date RecordRAM::getFamilyDivorceDate1(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isDivorced())
            return f.constDivorce().constDetail().getDate1();
    }
    return Date();
}

Date RecordRAM::getFamilyDivorceDate2(const Identifier fam) const
{
    if(this->isFamily(fam))
    {
        Family f = this->constFamily(fam);
        if(f.isDivorced())
            return f.constDivorce().constDetail().getDate2();
    }
    return Date();
}


Identifier RecordRAM::getIndividualFather(const Identifier indi) const
{
    if(this->isIndividual(indi)){
        Identifier fam = this->getIndividualParentalFamily(indi);
        if(this->isFamily(fam))
            return this->constFamily(fam).getHusband();
    }
    return Identifier();
}

Identifier RecordRAM::getIndividualMother(const Identifier indi) const
{
    if(this->isIndividual(indi)){
        Identifier fam = this->getIndividualParentalFamily(indi);
        if(this->isFamily(fam))
            return this->constFamily(fam).getWife();
    }
    return Identifier();
}

Identifier RecordRAM::getIndividualParentalFamily(const Identifier indi) const
{
    for(auto it=this->_families.cbegin(); it!=this->_families.cend(); it++)
    {
        if(it->getChildren().contains(indi))
        {
            return it->getRef();
        }
    }
    return Identifier();
}

QVector<Identifier> RecordRAM::getIndividualPartners(const Identifier indi) const
{
    QVector<Identifier> families, partners;
    if(this->isIndividual(indi))
    {
        families = this->getFamiliesOfIndividualParent(indi);
    }
    for(auto it = families.cbegin(); it != families.cend(); it++){
        Identifier father = this->constFamily(*it).getHusband();
        Identifier mother = this->constFamily(*it).getWife();
        partners.append(father);
        partners.append(mother);
    }
    partners.removeAll(indi);
    return partners;
}

QVector<Identifier> RecordRAM::getChildrenOfIndividual(const Identifier indi) const
{
    QVector<Identifier> families, children;
    if(this->isIndividual(indi))
    {
        families = this->getFamiliesOfIndividualParent(indi);
    }
    for(auto it = families.cbegin(); it != families.cend(); it++){
        children.append(this->constFamily(*it).getChildren());
    }
    this->sortByBirthDate(children);
    return children;
}

QVector<Identifier> RecordRAM::getChildrenOfCouple(const Identifier indi1, const Identifier indi2) const
{
    auto family = this->getFamilyOfCouple(indi1, indi2);
    if(this->isFamily(family))
    {
        QVector<Identifier> children = this->constFamily(family).getChildren();
        this->sortByBirthDate(children);
        return children;
    }
    return QVector<Identifier>();
}

QVector<Identifier> RecordRAM::getIndividualSiblings(const Identifier indi) const
{
    QVector<Identifier> fams;
    QVector<Identifier> children;
    if(this->isIndividual(indi)){
        Identifier father = this->getIndividualFather(indi);
        Identifier mother = this->getIndividualMother(indi);
        if(this->isIndividual(father))
        {
            auto fatherFams = this->getFamiliesOfIndividualParent(father);
            fams.append(fatherFams);
        }
        if(this->isIndividual(mother))
        {
            auto motherFams = this->getFamiliesOfIndividualParent(mother);
            for(auto it = motherFams.begin(); it != motherFams.end(); it++)
            {
                if(!fams.contains(*it))
                {
                    fams.append(*it);
                }
            }
        }
        Identifier fam = this->getIndividualParentalFamily(indi);
        if(this->isFamily(fam))
        {
            fams.push_back(fam);
        }
        for(auto family = fams.cbegin(); family!=fams.cend(); family++)
        {
            auto famChildren = this->constFamily(*family).getChildren();
            for(auto child = famChildren.begin(); child != famChildren.end(); child++)
            {
                bool notMe = (*child != indi);
                bool notContained = (!children.contains(*child));
                if(notMe && notContained)
                {
                    children.append(*child);
                }
            }
        }
    }
    this->sortByBirthDate(children);
    return children;
}


///////////////////////////////////////////////////////////////////////////////
/// Set records
///////////////////////////////////////////////////////////////////////////////

/// Head

void RecordRAM::setHeadSrc(const QString src)
{
    this->head.setSrc(src);
}

void RecordRAM::setHeadSrcVersion(const QString vers)
{
    this->head.setSrcVersion(vers);
}

void RecordRAM::setHeadSrcName(const QString name)
{
    this->head.setSrcName(name);
}

void RecordRAM::setHeadSrcCorp(const QString corp)
{
    this->head.setSrcCorp(corp);
}

void RecordRAM::setHeadSrcAddrAddress(const QString addr)
{
    this->head.srcCorpAddr().setAddress(addr);
}

void RecordRAM::setHeadSrcAddrCity(const QString city)
{
    this->head.srcCorpAddr().setCity(city);
}

void RecordRAM::setHeadSrcAddrState(const QString state)
{
    this->head.srcCorpAddr().setState(state);
}

void RecordRAM::setHeadSrcAddrPhone(const QString phone)
{
    this->head.srcCorpAddr().setPhone(phone);
}

void RecordRAM::setHeadSrcAddrEmail(const QString email)
{
    this->head.srcCorpAddr().setEmail(email);
}

void RecordRAM::setHeadSrcAddrWww(const QString www)
{
    this->head.srcCorpAddr().setWww(www);
}

void RecordRAM::setHeadSrcData(const QString data)
{
    this->head.setSrcData(data);
}

void RecordRAM::setHeadSrcDataDate(const Date date)
{
    this->head.setSrcDataDate(date);
}

void RecordRAM::setHeadDest(const QString dest)
{
    this->head.setDest(dest);
}

void RecordRAM::setHeadDate(const Date date)
{
    this->head.setDate(date);
}

void RecordRAM::setHeadTime(const QTime time)
{
    this->head.setTime(time);
}

void RecordRAM::setHeadRefSubm(const Identifier subm)
{
    this->head.setRefSubm(subm);
}

void RecordRAM::setHeadFile(const QString file)
{
    this->head.setFile(file);
}

void RecordRAM::setHeadCopr(const QString copr)
{
    this->head.setCopr(copr);
}

void RecordRAM::setHeadGedVers(const QString vers)
{
    this->head.setGedVers(vers);
}

void RecordRAM::setHeadGedForm(const QString form)
{
    this->head.setGedForm(form);
}

void RecordRAM::setHeadCharSet(const QString charset)
{
    this->head.setCharSet(charset);
}

void RecordRAM::setHeadCharVers(const QString vers)
{
    this->head.setCharVers(vers);
}

void RecordRAM::setHeadLang(const QString lang)
{
    this->head.setLang(lang);
}

void RecordRAM::setHeadPlac(const QString plac)
{
    this->head.setPlac(plac);
}

void RecordRAM::setHeadNote(const QString note)
{
    this->head.setNote(note);
}


/// Submitter

void RecordRAM::setSubmitterName(const Identifier subm, const QString name)
{
    if(this->isSubmitter(subm))
        this->submitter(subm).setName(name);
}

void RecordRAM::setSubmitterLang(const Identifier subm, const QString lang)
{
    if(this->isSubmitter(subm))
        this->submitter(subm).setLang(lang);
}

void RecordRAM::setSubmitterNote(const Identifier subm, const QString note)
{
    if(this->isSubmitter(subm))
        this->submitter(subm).setNote(note);
}

void RecordRAM::setSubmitterDate(const Identifier subm, const Date date)
{
    if(this->isSubmitter(subm))
        this->submitter(subm).setDate(date);
}

void RecordRAM::setSubmitterTime(const Identifier subm, const QTime time)
{
    if(this->isSubmitter(subm))
        this->submitter(subm).setTime(time);
}

unsigned int RecordRAM::setSourceData(const Identifier src, const CommonEventType t)
{
    if(this->isSource(src))
    {
        return this->source(src).addData(t);
    }
    return 0;
}

void RecordRAM::setSourceDataDateFrom(const Identifier src, const CommonEventType t, unsigned int index, const Date from)
{
    if(this->isSource(src))
    {
        this->source(src).setDataDateFrom(t, index, from);
    }
}

void RecordRAM::setSourceDataDateTo(const Identifier src, const CommonEventType t, unsigned int index, const Date to)
{
    if(this->isSource(src))
    {
        this->source(src).setDataDateTo(t, index, to);
    }
}

void RecordRAM::setSourceDataPlac(const Identifier src, const CommonEventType t, unsigned int index, const QString plac)
{
    if(this->isSource(src))
    {
        this->source(src).setDataPlac(t, index, plac);
    }
}

void RecordRAM::setSourceDataPage1(const Identifier src, const CommonEventType t, unsigned int index, const QString page)
{
    if(this->isSource(src))
    {
        this->source(src).setDataPage1(t, index, page);
    }
}

void RecordRAM::setSourceDataPage2(const Identifier src, const CommonEventType t, unsigned int index, const QString page)
{
    if(this->isSource(src))
    {
        this->source(src).setDataPage2(t, index, page);
    }
}

void RecordRAM::setSourceDataUrl(const Identifier src, const CommonEventType t, unsigned int index, const QString url)
{
    if(this->isSource(src))
    {
        this->source(src).setDataUrl(t, index, url);
    }
}

void RecordRAM::setSourceArchive(const Identifier src, const QString title)
{
    if(this->isSource(src))
    {
        this->source(src).setArchive(title);
    }
}

void RecordRAM::setSourceTitle(const Identifier src, const QString title)
{
    if(this->isSource(src))
    {
        this->source(src).setSignature(title);
    }
}

void RecordRAM::setSourceOriginator(const Identifier src, const QString title)
{
    if(this->isSource(src))
        this->source(src).setOriginator(title);
}

void RecordRAM::setSourceUrl(const Identifier src, const QString url)
{
    if(this->isSource(src))
    {
        this->source(src).setUrl(url);
    }
}


/// Individual

void RecordRAM::setIndividualNamePrefix(Identifier indi, QString name)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).name().setPrefix(name);
    }
}

void RecordRAM::setIndividualNameGiven(Identifier indi, QString name)
{
    if(this->isIndividual(indi))
        this->individual(indi).name().setGiven(name);
}

void RecordRAM::setIndividualNameSurname(Identifier indi, QString name)
{
    if(this->isIndividual(indi))
        this->individual(indi).name().setSurname(name);
}

void RecordRAM::setIndividualNameMarname(Identifier indi, QString name)
{
    if(this->isIndividual(indi))
        this->individual(indi).name().setMarname(name);
}

void RecordRAM::setIndividualNameSuffix(Identifier indi, QString name)
{
    if(this->isIndividual(indi))
        this->individual(indi).name().setSuffix(name);
}

void RecordRAM::setIndividualGender(Identifier indi, Gender g)
{
    if(this->isIndividual(indi))
    {
        // If individual figures as a spouse in no families, change the gender
        if(this->getFamiliesOfIndividualParent(indi).empty())
        {
            this->individual(indi).setGender(g);
        }
    }
}

void RecordRAM::setIndividualBirthDateType(Identifier indi, DateType type)
{
    if(this->isIndividual(indi))
        this->individual(indi).birth().detail().setDateType(type);
}

void RecordRAM::setIndividualBirthDate1(Identifier indi, Date date)
{
    if(this->isIndividual(indi))
        this->individual(indi).birth().detail().setDate1(date);
}

void RecordRAM::setIndividualBirthDate2(Identifier indi, Date date)
{
    if(this->isIndividual(indi))
        this->individual(indi).birth().detail().setDate2(date);
}

void RecordRAM::setIndividualBirthPlaceName(const Identifier indi, const QString place)
{
    if(this->isIndividual(indi))
        this->individual(indi).birth().detail().place().setName(place);
}

void RecordRAM::setIndividualBirthObstetrix(const Identifier indi, const Identifier obstetrix)
{
    if(this->isIndividual(indi))
    {
        if(this->isIndividual(obstetrix) || !obstetrix.isValid())
        {
            this->individual(indi).birth().detail().setWitness1(obstetrix);
        }
        else if(!this->isIndividual(obstetrix))
        {
            this->newIndividual(obstetrix);
        }
    }
}

void RecordRAM::setIndividualBirthSourceCitationRef(Identifier indi, Identifier src)
{
    if(this->isIndividual(indi))
    {
        if(this->isSource(src))
        {
            this->individual(indi).birth().detail().sourceCitation().setRef(src);
        }
        // Remove source
        else
        {
            this->removeIndividualBirthSource(indi);
        }
    }
}

void RecordRAM::setIndividualBirthSourceCitationPage(Identifier indi, QString page)
{
    if(this->isIndividual(indi))
    {
        SourceCitation& cit = this->individual(indi).birth().detail().sourceCitation();
        if(this->isSource(cit.getRef()))
            cit.setPage(page);
    }
}

void RecordRAM::setIndividualBirthSourceCitationUrl(Identifier indi, QString url)
{
    if(this->isIndividual(indi))
    {
        SourceCitation& cit = this->individual(indi).birth().detail().sourceCitation();
        if(this->isSource(cit.getRef()))
            cit.setUrl(url);
    }
}

void RecordRAM::setIndividualChristeningDateType(const Identifier indi, const DateType datetype)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).christening().detail().setDateType(datetype);
    }
}

void RecordRAM::setIndividualChristeningDate1(const Identifier indi, const Date date)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).christening().detail().setDate1(date);
    }
}

void RecordRAM::setIndividualChristeningDate2(const Identifier indi, const Date date)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).christening().detail().setDate2(date);
    }
}

void RecordRAM::setIndividualChristeningPriest(const Identifier indi, const Identifier priest)
{
    if(this->isIndividual(indi))
    {
        if(this->isIndividual(priest) || !priest.isValid())
        {
            this->individual(indi).christening().detail().setPriest(priest);
        }
        else if(!this->isIndividual(priest))
        {
            this->newIndividual(priest);
        }
    }
}

void RecordRAM::setIndividualChristeningGodfather(const Identifier indi, const Identifier godfather)
{
    if(this->isIndividual(indi))
    {
        if(this->isIndividual(godfather) || !godfather.isValid())
        {
            this->individual(indi).christening().detail().setWitness1(godfather);
        }
        else if(!this->isIndividual(godfather))
        {
            this->newIndividual(godfather);
        }
    }
}

void RecordRAM::setIndividualChristeningGodmother(const Identifier indi, const Identifier godmother)
{
    if(this->isIndividual(indi))
    {
        if(this->isIndividual(godmother) || !godmother.isValid())
        {
            this->individual(indi).christening().detail().setWitness2(godmother);
        }
        else if(!this->isIndividual(godmother))
        {
            this->newIndividual(godmother);
        }
    }
}

void RecordRAM::setIndividualDeathDateType(Identifier indi, DateType date)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).death().detail().setDateType(date);
    }
}

void RecordRAM::setIndividualDeathDate1(Identifier indi, Date date)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).death().detail().setDate1(date);
    }
}

void RecordRAM::setIndividualDeathDate2(Identifier indi, Date date)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).death().detail().setDate2(date);
    }
}

void RecordRAM::setIndividualDeathPlaceName(Identifier indi, QString place)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).death().detail().place().setName(place);
    }
}

void RecordRAM::setIndividualDeathCause(Identifier indi, QString cause)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).death().detail().setCause(cause);
    }
}

void RecordRAM::setIndividualDeathSourceCitationRef(Identifier indi, Identifier src)
{

    if(this->isIndividual(indi))
    {
        if(this->isSource(src))
        {
            this->individual(indi).death().detail().sourceCitation().setRef(src);
        }
        // Remove source
        else
        {
            this->removeIndividualDeathSource(indi);
        }
    }
}

void RecordRAM::setIndividualDeathSourceCitationPage(Identifier indi, QString page)
{
    if(this->isIndividual(indi))
    {
        SourceCitation& cit = this->individual(indi).death().detail().sourceCitation();
        if(this->isSource(cit.getRef()))
            cit.setPage(page);
    }
}

void RecordRAM::setIndividualDeathSourceCitationUrl(Identifier indi, QString url)
{
    if(this->isIndividual(indi))
    {
        if(this->isIndividual(indi))
        {
            SourceCitation& cit = this->individual(indi).death().detail().sourceCitation();
            if(this->isSource(cit.getRef()))
                cit.setUrl(url);
        }
    }
}

void RecordRAM::setIndividualBurialDateType(const Identifier indi, const DateType datetype)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).burial().detail().setDateType(datetype);
    }
}

void RecordRAM::setIndividualBurialDate1(const Identifier indi, const Date date)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).burial().detail().setDate1(date);
    }
}

void RecordRAM::setIndividualBurialDate2(const Identifier indi, const Date date)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).burial().detail().setDate2(date);
    }
}

void RecordRAM::setIndividualBurialPlaceName(const Identifier indi, const QString place)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).burial().detail().place().setName(place);
    }
}

void RecordRAM::setIndividualBurialPriest(const Identifier indi, const Identifier priest)
{
    if(this->isIndividual(indi))
    {
        if(this->isIndividual(priest) || !priest.isValid())
        {
            this->individual(indi).burial().detail().setPriest(priest);
        }
        else if(!this->isIndividual(priest))
        {
            this->newIndividual(priest);
        }
    }
}

unsigned int RecordRAM::setIndividualOccu(const Identifier indi)
{
    unsigned int index = 0;
    if(this->isIndividual(indi))
    {
        index = this->individual(indi).getOccuCount();
        this->individual(indi).occupation(index);
        this->individual(indi).occupation(index).detail().setDateType(DateType::PERIOD);
    }
    return index;
}

void RecordRAM::setIndividualOccuDescription(const Identifier indi, const unsigned int index, const QString descr)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getOccuCount())
        {
            this->individual(indi).occupation(index).setDescription(descr);
        }
    }
}

void RecordRAM::setIndividualOccuDateType(const Identifier indi, const unsigned int index, const DateType datetype)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getOccuCount())
        {
            this->individual(indi).occupation(index).detail().setDateType(datetype);
        }
    }
}

void RecordRAM::setIndividualOccuDate1(const Identifier indi, const unsigned int index, const Date date)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getOccuCount())
        {
            this->individual(indi).occupation(index).detail().setDate1(date);
        }
    }
}

void RecordRAM::setIndividualOccuDate2(const Identifier indi, const unsigned int index, const Date date)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getOccuCount())
        {
            this->individual(indi).occupation(index).detail().setDate2(date);
        }
    }
}

unsigned int RecordRAM::setIndividualEduc(const Identifier indi)
{
    unsigned int index = 0;
    if(this->isIndividual(indi))
    {
        index = this->constIndividual(indi).getEducCount();
        this->individual(indi).education(index);
        this->individual(indi).education(index).detail().setDateType(DateType::PERIOD);
    }
    return index;
}

void RecordRAM::setIndividualEducDescription(const Identifier indi, const unsigned int index, const QString descr)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getEducCount())
        {
            this->individual(indi).education(index).setDescription(descr);
        }
    }
}

void RecordRAM::setIndividualEducDateType(const Identifier indi, const unsigned int index, const DateType datetype)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getEducCount())
        {
            this->individual(indi).education(index).detail().setDateType(datetype);
        }
    }
}

void RecordRAM::setIndividualEducDate1(const Identifier indi, const unsigned int index, const Date date)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getEducCount())
        {
            this->individual(indi).education(index).detail().setDate1(date);
        }
    }
}

void RecordRAM::setIndividualEducDate2(const Identifier indi, const unsigned int index, const Date date)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getEducCount())
        {
            this->individual(indi).education(index).detail().setDate2(date);
        }
    }
}

unsigned int RecordRAM::setIndividualResi(const Identifier indi)
{
    unsigned int index = 0;
    if(this->isIndividual(indi))
    {
        index = this->constIndividual(indi).getResiCount();
        this->individual(indi).residence(index);
        this->individual(indi).residence(index).detail().setDateType(DateType::PERIOD);
    }
    return index;
}

void RecordRAM::setIndividualResiDateType(const Identifier indi, const unsigned int index, const DateType datetype)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getResiCount())
        {
            this->individual(indi).residence(index).detail().setDateType(datetype);
        }
    }
}

void RecordRAM::setIndividualResiDate1(const Identifier indi, const unsigned int index, const Date date)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getResiCount())
        {
            this->individual(indi).residence(index).detail().setDate1(date);
        }
    }
}

void RecordRAM::setIndividualResiDate2(const Identifier indi, const unsigned int index, const Date date)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getResiCount())
        {
            this->individual(indi).residence(index).detail().setDate2(date);
        }
    }
}

void RecordRAM::setIndividualResiAddrCity(const Identifier indi, const unsigned int index, const QString city)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getResiCount())
        {
            this->individual(indi).residence(index).detail().address().setCity(city);
        }
    }
}

void RecordRAM::setIndividualResiAddrAddr(const Identifier indi, const unsigned int index, const QString addr)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getResiCount())
        {
            this->individual(indi).residence(index).detail().address().setAddress(addr);
        }
    }
}

unsigned int RecordRAM::setIndividualReli(const Identifier indi)
{
    unsigned int index = 0;
    if(this->isIndividual(indi))
    {
        index = this->constIndividual(indi).getReliCount();
        this->individual(indi).religion(index);
        this->individual(indi).religion(index).detail().setDateType(DateType::PERIOD);
    }
    return index;
}

void RecordRAM::setIndividualReliDescription(const Identifier indi, const unsigned int index, const QString descr)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getReliCount())
        {
            this->individual(indi).religion(index).setDescription(descr);
        }
    }
}

void RecordRAM::setIndividualReliDateType(const Identifier indi, const unsigned int index, const DateType datetype)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getReliCount())
        {
            this->individual(indi).religion(index).detail().setDateType(datetype);
        }
    }
}

void RecordRAM::setIndividualReliDate1(const Identifier indi, const unsigned int index, const Date date)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getReliCount())
        {
            this->individual(indi).religion(index).detail().setDate1(date);
        }
    }
}

void RecordRAM::setIndividualReliDate2(const Identifier indi, const unsigned int index, const Date date)
{
    if(this->isIndividual(indi))
    {
        if(index < this->constIndividual(indi).getReliCount())
        {
            this->individual(indi).religion(index).detail().setDate2(date);
        }
    }
}

void RecordRAM::setIndividualPhone(const Identifier indi, const QString phone)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).address().setPhone(phone);
    }
}

void RecordRAM::setIndividualEmail(const Identifier indi, const QString email)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).address().setEmail(email);
    }
}

void RecordRAM::setIndividualWww(const Identifier indi, const QString www)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).address().setWww(www);
    }
}

void RecordRAM::setIndividualNote(const Identifier indi, const QString note)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).setNote(note);
    }
}


/// Family

void RecordRAM::setFamilyHusband(const Identifier fam, const Identifier husb)
{
    if(this->isFamily(fam))
    {
        if(this->isIndividual(husb))
        {
            this->family(fam).setHusband(husb);
        }
        else if(!husb.isValid())
        {
            this->removeFamilyHusband(fam);
        }
    }
}

void RecordRAM::setFamilyWife(const Identifier fam, const Identifier wife)
{
    if(this->isFamily(fam))
    {
        if(this->isIndividual(wife))
        {
            this->family(fam).setWife(wife);
        }
        else if(!wife.isValid())
        {
            this->removeFamilyWife(fam);
        }
    }
}

void RecordRAM::setFamilyChild(const Identifier fam, const Identifier chi)
{
    if(this->isFamily(fam) && this->isIndividual(chi))
        this->family(fam).setChild(chi);
}

void RecordRAM::setFamilyMarried(Identifier fam)
{
    if(this->isFamily(fam))
    {
        this->family(fam).setMarriage();
    }
}

void RecordRAM::setFamilyMarriageDateType(Identifier fam, DateType type)
{
    if(this->isFamily(fam))
        this->family(fam).marriage().detail().setDateType(type);
}

void RecordRAM::setFamilyMarriageDate1(Identifier fam, Date date)
{
    if(this->isFamily(fam))
    {
        this->family(fam).marriage().detail().setDate1(date);
    }
}

void RecordRAM::setFamilyMarriageDate2(Identifier fam, Date date)
{
    if(this->isFamily(fam))
    {
        this->family(fam).marriage().detail().setDate2(date);
    }
}

void RecordRAM::setFamilyMarriagePlaceName(Identifier fam, QString plac)
{
    if(this->isFamily(fam))
    {
        this->family(fam).marriage().detail().place().setName(plac);
    }
}

void RecordRAM::setFamilyMarriagePriest(const Identifier fam, const Identifier priest)
{
    if(this->isFamily(fam))
    {
        if(this->isIndividual(priest) || !priest.isValid())
        {
            this->family(fam).marriage().detail().setPriest(priest);
        }
        else if(!this->isIndividual(priest))
        {
            this->newIndividual(priest);
        }
    }
}

void RecordRAM::setFamilyMarriageWitness1(const Identifier fam, const Identifier witness)
{
    if(this->isFamily(fam))
    {
        if(this->isIndividual(witness) || !witness.isValid())
        {
            this->family(fam).marriage().detail().setWitness1(witness);
        }
        else if(!this->isIndividual(witness))
        {
            this->newIndividual(witness);
        }
    }
}

void RecordRAM::setFamilyMarriageWitness2(const Identifier fam, const Identifier witness)
{
    if(this->isFamily(fam))
    {
        if(this->isIndividual(witness) || !witness.isValid())
        {
            this->family(fam).marriage().detail().setWitness2(witness);
        }
        else if(!this->isIndividual(witness))
        {
            this->newIndividual(witness);
        }
    }
}

void RecordRAM::setFamilyMarriageSourceCitationRef(const Identifier fam, const Identifier src)
{

    if(this->isFamily(fam))
    {
        if(this->isSource(src))
        {
            this->family(fam).marriage().detail().sourceCitation().setRef(src);
        }
        // Remove source
        else
        {
            this->removeFamilyMarriageSource(fam);
        }
    }
}

void RecordRAM::setFamilyMarriageSourceCitationPage(const Identifier fam, const QString page)
{
    if(this->isFamily(fam))
    {
        SourceCitation& cit = this->family(fam).marriage().detail().sourceCitation();
        if(this->isSource(cit.getRef()))
            cit.setPage(page);
    }
}

void RecordRAM::setFamilyMarriageSourceCitationUrl(const Identifier fam, const QString url)
{
    if(this->isFamily(fam))
    {
        SourceCitation& cit = this->family(fam).marriage().detail().sourceCitation();
        if(this->isSource(cit.getRef()))
            cit.setUrl(url);
    }
}

void RecordRAM::setFamilyDivorced(Identifier fam)
{
    if(this->isFamily(fam))
    {
        this->family(fam).setDivorce();
    }
}

void RecordRAM::setFamilyDivorceDateType(Identifier fam, DateType type)
{
    if(this->isFamily(fam))
        this->family(fam).divorce().detail().setDateType(type);
}

void RecordRAM::setFamilyDivorceDate1(Identifier fam, Date date)
{
    if(this->isFamily(fam))
    {
        this->family(fam).divorce().detail().setDate1(date);
    }
}

void RecordRAM::setFamilyDivorceDate2(Identifier fam, Date date)
{
    if(this->isFamily(fam))
    {
        this->family(fam).divorce().detail().setDate2(date);
    }
}

void RecordRAM::setFamilyDivorcePlaceName(Identifier fam, QString plac)
{
    if(this->isFamily(fam))
    {
        this->family(fam).divorce().detail().place().setName(plac);
    }
}




void RecordRAM::setIndividualFather(Identifier chi, Identifier father)
{
    /// TODO - empty father ref
    this->setIndividualParent(chi, father, Gender::MALE);
}

void RecordRAM::setIndividualMother(Identifier chi, Identifier mother)
{
    /// TODO - empty mother ref
    this->setIndividualParent(chi, mother, Gender::FEMALE);
}

void RecordRAM::setIndividualCouple(const Identifier husb, const Identifier wife)
{
    if(this->isIndividual(husb) && this->isIndividual(wife))
    {
        bool isHusbMale = this->constIndividual(husb).getGender() == Gender::MALE;
        bool isWifeFemale = this->constIndividual(wife).getGender() == Gender::FEMALE;
        if(isHusbMale && isWifeFemale)
        {
            for(auto it = this->_families.begin(); it!= this->_families.end(); it++)
            {
                if((it->getHusband() == husb) && (it->getWife() == wife))
                    return; // family is already present
            }
            Identifier newFam = this->newFamily();
            this->family(newFam).setHusband(husb);
            this->family(newFam).setWife(wife);
        }
    }
}

void RecordRAM::setIndividualChild(const Identifier indi, const Identifier chi)
{
    if(this->isIndividual(indi) && this->isIndividual(chi))
        this->setIndividualParent(chi, indi, this->constIndividual(indi).getGender());
}

void RecordRAM::swapIndividualOccu(Identifier indi, const unsigned int index1, const unsigned int index2)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).swapOccu(index1, index2);
    }
}

void RecordRAM::swapIndividualEduc(Identifier indi, const unsigned int index1, const unsigned int index2)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).swapEduc(index1, index2);
    }
}

void RecordRAM::swapIndividualResi(Identifier indi, const unsigned int index1, const unsigned int index2)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).swapResi(index1, index2);
    }
}

void RecordRAM::swapIndividualReli(Identifier indi, const unsigned int index1, const unsigned int index2)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).swapReli(index1, index2);
    }
}

void RecordRAM::swapFamilies(const Identifier fam1, const Identifier fam2)
{
    Family f = this->constFamily(fam1);                 // Copy constructor - full copy with old id!!
    this->family(fam1).copyFamily(this->family(fam2));  // Data copy only (no id copy)
    this->family(fam2).copyFamily(f);                   // Data copy only (no id copy)
}

void RecordRAM::removeIndividualBirth(Identifier indi)
{
    if(this->isIndividual(indi))
        this->individual(indi).removeBirth();
}

void RecordRAM::removeIndividualChristening(Identifier indi)
{
    if(this->isIndividual(indi))
        this->individual(indi).removeChristening();
}

void RecordRAM::removeIndividualDeath(Identifier indi)
{
    if(this->isIndividual(indi))
        this->individual(indi).removeDeath();
}

void RecordRAM::removeIndividualBurial(Identifier indi)
{
    if(this->isIndividual(indi))
        this->individual(indi).removeBurial();
}

void RecordRAM::removeIndividualBirthSource(const Identifier indi)
{
    if(this->isIndividual(indi))
    {
        if(this->individual(indi).isBorn())
        {
            this->individual(indi).birth().detail().sourceCitation().remove();
        }
    }
}

void RecordRAM::removeIndividualDeathSource(const Identifier indi)
{
    if(this->isIndividual(indi))
    {
        if(this->individual(indi).isDeceased())
        {
            this->individual(indi).death().detail().sourceCitation().remove();
        }
    }
}

void RecordRAM::removeIndividualOccu(const Identifier indi, const unsigned int index)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).removeOccu(index);
    }
}

void RecordRAM::removeIndividualEduc(const Identifier indi, const unsigned int index)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).removeEduc(index);
    }
}

void RecordRAM::removeIndividualResi(const Identifier indi, const unsigned int index)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).removeResi(index);
    }
}

void RecordRAM::removeIndividualReli(const Identifier indi, const unsigned int index)
{
    if(this->isIndividual(indi))
    {
        this->individual(indi).removeReli(index);
    }
}


/// Removers

void RecordRAM::removeFamilyHusband(Identifier fam)
{
    if(this->isFamily(fam)){
        this->family(fam).removeHusband();
        if(this->constFamily(fam).isEmpty())
        {
            this->deleteFamily(fam);
        }
    }
}

void RecordRAM::removeFamilyWife(Identifier fam)
{
    if(this->isFamily(fam)){
        this->family(fam).removeWife();
        if(this->constFamily(fam).isEmpty())
        {
            this->deleteFamily(fam);
        }
    }
}

void RecordRAM::removeFamilyChild(Identifier fam, Identifier chi)
{
    if(this->isFamily(fam)){
        this->family(fam).removeChild(chi);
        if(this->constFamily(fam).isEmpty())
        {
            this->deleteFamily(fam);
        }
    }
}

void RecordRAM::removeFamilyMarriage(Identifier fam)
{
    if(this->isFamily(fam))
    {
        this->family(fam).removeMarriage();
    }
}

void RecordRAM::removeFamilyMarriageSource(const Identifier fam)
{
    if(this->isFamily(fam))
    {
        if(this->family(fam).isMarried())
        {
            this->family(fam).marriage().detail().sourceCitation().remove();
            //qDebug() << "SRC REF " << cit.getRef().get();
        }
    }
}

void RecordRAM::removeSourceData(const Identifier &src, const CommonEventType t, unsigned int index)
{
    if(this->isSource(src))
    {
        this->source(src).removeData(t, index);
    }
}

void RecordRAM::removeFamilyDivorce(Identifier fam)
{
    if(this->isFamily(fam))
    {
        this->family(fam).removeDivorce();
    }
}



/// Delete records
void RecordRAM::deleteIndividual(Identifier indi)
{
    QVector<Identifier> famsToDelete;
    // Remove individual from individuals list
    this->_individuals.remove(indi);
    // Remove individual's Identifier
    this->_identifierFactoryIndividual.freeIdentifier(indi);
    // Put empty identifier to every family ref pointing to this individual
    for(auto it=this->_families.begin(); it!=this->_families.end(); it++){
        (*it).removeIndividual(indi);
        if(it->isEmpty())
            famsToDelete.push_back(it->getRef());
    }
    for(auto i=famsToDelete.length(); i!=0; i--)
        this->deleteFamily(famsToDelete.takeFirst());

//    if(this->getIndividualProband() == indi)
//    {
//        this->clearIndividualProband();
//    }
//    if(this->getIndividualCurrent() == indi)
//    {
//        this->clearIndividualCurrent();
//    }
    /// TODO Conflict!!! - what Identifier should be proband and current?
}

void RecordRAM::deleteFamily(Identifier fam)
{
    this->_families.remove(fam);
    // Remove family's Identifier
    this->_identifierFactoryFamily.freeIdentifier(fam);
}

void RecordRAM::deleteSubmitter(Identifier subm)
{
    this->_submitters.remove(subm);
    // Ensure there is some Submitter Identifier in the Header - Mandatory!
    if(this->head.getRefSubm() == subm)
    {
        this->head.setRefSubm(this->newSubmitter());

    }
    // Remove submitter's Identifier
    this->_identifierFactorySubmitter.freeIdentifier(subm);
}

void RecordRAM::deleteSource(Identifier src)
{
    this->_sources.remove(src);
    // Remove source's Identifier
    this->_identifierFactorySource.freeIdentifier(src);

    // Remove references to this source
    for(auto it = this->_individuals.begin(); it != this->_individuals.end(); it++)
    {
        if(it->isBorn())
        {
            auto cit = it->birth().detail().sourceCitation();
            if(cit.getRef() == src)
            {
                cit.remove();
            }
        }
        if(it->isDeceased())
        {
            auto cit = it->death().detail().sourceCitation();
            if(cit.getRef() == src)
            {
                cit.remove();
            }
        }
    }
    for(auto it = this->_families.begin(); it != this->_families.end(); it++)
    {
        if(it->isMarried())
        {
            auto cit = it->marriage().detail().sourceCitation();
            if(cit.getRef() == src)
            {
                cit.remove();
            }
        }
    }
}

void RecordRAM::deleteDatabase()
{
    this->_identifierFactoryIndividual.reset();
    this->_identifierFactoryFamily.reset();
    this->_identifierFactorySubmitter.reset();
    this->_identifierFactorySource.reset();
    this->_individuals.clear();
    this->_families.clear();
    this->_sources.clear();
    this->_submitters.clear();
}

bool RecordRAM::compareBirthDates::operator()(Identifier ref1, Identifier ref2) const
{
    DateType datetype1 = _data.getIndividualBirthDateType(ref1);
    DateType datetype2 = _data.getIndividualBirthDateType(ref2);
    Date date1 = _data.getIndividualBirthDate1(ref1);
    Date date2 = _data.getIndividualBirthDate1(ref2);

    // Both dates are valid for comparison
    if((datetype1 == DateType::SIMPLE) && (datetype2 == DateType::SIMPLE))
    {
        if(date1 < date2)
        {
            return true; // indi1, indi2
        }
        else if(date1 == date2)
        {
            return true;   // Equivalent
        }
        else // date1 > date2
        {
            return false; // indi2, indi1
        }
    }
    else if((datetype1 == DateType::SIMPLE) && (datetype2 != DateType::SIMPLE))
    {
        return false; // indi2, indi1
    }
    else if((datetype1 != DateType::SIMPLE) && (datetype2 == DateType::SIMPLE))
    {
        return true; // indi1, indi2
    }
    else // ((datetype1 != DateType::SIMPLE) && (datetype2 != DateType::SIMPLE))
    {
        return true;
    }
}
