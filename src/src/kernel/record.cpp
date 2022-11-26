/*!
 *  \file   record.cpp
 *  \author Eva Navratilova
 */

#include "record.h"

Record::Record()
{

}

Record::~Record()
{

}

Date Record::getSourceCommonDateFrom(Identifier src) const
{
    bool notDateInitialized = true;
    Date date;
    Date tempDate;

    if(this->isSource(src))
    {
        auto data = this->getSourceData(src);
        for(CommonEventType type : data)
        {
            unsigned int count = this->getSourceDataCount(src, type);
            for(unsigned int i = 0; i < count; i++)
            {
                tempDate = this->getSourceDataDateFrom(src, type, i);
                if(notDateInitialized)
                {
                    date = tempDate;
                    notDateInitialized = false;
                }
                else if(date > tempDate)
                {
                    date = tempDate;
                }
            }
        }
    }

    return date;
}

Date Record::getSourceCommonDateTo(Identifier src) const
{
    bool notDateInitialized = true;
    Date date;
    Date tempDate;

    if(this->isSource(src))
    {
        auto data = this->getSourceData(src);
        for(CommonEventType type : data)
        {
            unsigned int count = this->getSourceDataCount(src, type);
            for(unsigned int i = 0; i < count; i++)
            {
                tempDate = this->getSourceDataDateTo(src, type, i);
                if(notDateInitialized)
                {
                    date = tempDate;
                    notDateInitialized = false;
                }
                else if(date < tempDate)
                {
                    date = tempDate;
                }
            }
        }
    }

    return date;
}

void Record::setFamilySpouse(Identifier fam, Identifier spouse)
{
    if(this->isFamily(fam))
    {
        if(this->isIndividual(spouse))
        {
            Gender g = this->getIndividualGender(spouse);
            if(g == Gender::MALE)
            {
                this->setFamilyHusband(fam, spouse);
            }
            else if(g == Gender::FEMALE)
            {
                this->setFamilyWife(fam, spouse);
            }
        }
    }
}

void Record::removeFamilySpouse(Identifier fam, Identifier spouse)
{
    if(this->isFamily(fam))
    {
        Identifier husb = this->getFamilyHusband(fam);
        Identifier wife = this->getFamilyWife(fam);
        if(husb == spouse)
        {
            this->removeFamilyHusband(fam);
        }
        else if(wife == spouse)
        {
            this->removeFamilyWife(fam);
        }
    }
}

BoolExtended Record::isIndividualAlive(const Identifier indi, int maxAge, const Date date)
{
    if(date == Date())
        return BoolExtended::UNDETERMINED;

    Date birth = this->getIndividualBirthDate1(indi);
    Date death = this->getIndividualBirthDate1(indi);
    // Nothing known
    if(birth == Date() && death == Date())
    {
        return BoolExtended::UNDETERMINED;
    }
    // Both known
    else if(birth != Date() && death != Date())
    {
        if((birth < date) && (date < death))
            return BoolExtended::TRUE;
        else
            return BoolExtended::FALSE;
    }
    // Birth known
    else if(birth != Date())
    {
        Date maxDeath(date.year() + maxAge, date.month(), date.day());
        // Correction for February, 28th
        if(! maxDeath.isValid())
        {
            maxDeath.setDate(date.year() + maxAge, date.month(), date.day() - 1);
        }
        if((date < birth) || maxDeath < date)
        {
            return BoolExtended::FALSE;
        }
        else
        {
            return BoolExtended::UNDETERMINED;
        }
    }
    // Death known
    else
    {
        Date maxBirth(date.year() - maxAge, date.month(), date.day());
        // Correction for February, 28th
        if(! maxBirth.isValid())
        {
            maxBirth.setDate(date.year() - maxAge, date.month(), date.day() - 1);
        }
        if((date < maxBirth) || death < date)
        {
            return BoolExtended::FALSE;
        }
        else
        {
            return BoolExtended::UNDETERMINED;
        }

    }

    /// TODO - Check parents and children!!!!!
}

QString Record::getIndividualNameSurnameMarriedBirth(const Identifier indi) const
{
    QString lastname = this->getIndividualNameSurnameMarried(indi);
    if(lastname.isEmpty())
    {
        lastname = this->getIndividualNameSurnameBirth(indi);
    }
    return lastname;
}

QString Record::getIndividualNameSurnameBirthMarried(const Identifier indi) const
{
    QString lastname = this->getIndividualNameSurnameBirth(indi);
    if(lastname.isEmpty())
    {
        lastname = this->getIndividualNameSurnameMarried(indi);
    }
    return lastname;
}

/**
 * @brief Returns the age of an individual as a Date. The Date is one year bigger than the actual age!!
 *
 * Class Date cannot display a year 0
 *
 * @param indi
 * @return Date
 */
Age Record::getIndividualAge(const Identifier indi) const
{
    Age age;
    if(this->isIndividual(indi))
    {
        if((this->getIndividualBirthDateType(indi) == DateType::SIMPLE) &&
           (this->getIndividualDeathDateType(indi) == DateType::SIMPLE))
        {
            Date birth = this->getIndividualBirthDate1(indi);
            Date death = this->getIndividualDeathDate1(indi);

            age = Age(birth, death);
        }
    }
    return age;
}

QVector<Identifier> Record::getIndividualDescendants(Identifier indi) const
{
    QVector<Identifier> childrenToSearch;
    QVector<Identifier> descendants;
    childrenToSearch.append(indi);
    while(!childrenToSearch.isEmpty())
    {
        Identifier indiToSearch = childrenToSearch.takeFirst();
        auto tempChildren = this->getChildrenOfIndividual(indiToSearch);
        for(auto tempChild : tempChildren)
        {
            if(!childrenToSearch.contains(tempChild))
            {
                descendants.append(tempChild);
                childrenToSearch.append(tempChild);
            }
        }
    }
    return descendants;
}

QVector<Identifier> Record::getIndividualAncestors(Identifier indi) const
{
    QVector<Identifier> ancestorsToSearch;
    QVector<Identifier> ancestors;
    ancestorsToSearch.append(indi);
    while(!ancestorsToSearch.isEmpty())
    {
        Identifier indiToSearch = ancestorsToSearch.takeFirst();
        Identifier father = this->getIndividualFather(indiToSearch);
        Identifier mother = this->getIndividualMother(indiToSearch);
        QVector<Identifier> tempAncestors;
        if(this->isIndividual(father) && !ancestorsToSearch.contains(father))
        {
            tempAncestors.append(father);
        }
        if(this->isIndividual(mother) && !ancestorsToSearch.contains(mother))
        {
            tempAncestors.append(mother);
        }
        ancestors.append(tempAncestors);
        ancestorsToSearch.append(tempAncestors);
    }
    return ancestors;
}

QStringList Record::getStringsGivenNames(Gender g) const
{
    QStringList names;
    QString name;
    for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
    {
        if(this->getIndividualGender(ref) != g)
            continue;
        name = this->getIndividualNameGiven(ref);
        if(!name.isEmpty() && !names.contains(name))
        {
            names.push_back(name);
        }
    }
    std::sort(names.begin(), names.end());
    return names;
}

QStringList Record::getStringsSurnames(Gender g) const
{
    QStringList names;
    QString name1;
    QString name2;
    for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
    {
        if(this->getIndividualGender(ref) != g)
            continue;

        name1 = this->getIndividualNameSurnameBirth(ref);
        name2 = this->getIndividualNameSurnameMarried(ref);
        if(!name1.isEmpty() && !names.contains(name1))
        {
            names.push_back(name1);
        }
        if(!name2.isEmpty() && !names.contains(name2))
        {
            names.push_back(name2);
        }
    }
    std::sort(names.begin(), names.end());
    return names;
}

QStringList Record::getStringsPrefixes() const
{
    QStringList names;
    QString name;
    for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
    {
        name = this->getIndividualNamePrefix(ref);
        if(!name.isEmpty() && !names.contains(name))
        {
            names.push_back(name);
        }
    }
    std::sort(names.begin(), names.end());
    return names;
}

QStringList Record::getStringsSuffixes() const
{
    QStringList names;
    QString name;
    for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
    {
        name = this->getIndividualNameSuffix(ref);
        if(!name.isEmpty() && !names.contains(name))
        {
            names.push_back(name);
        }
    }
    std::sort(names.begin(), names.end());
    return names;
}

QStringList Record::getStringsPlaces() const
{
    QStringList strings;
    strings.append(this->getStringsEventPlaces(CommonEventType::BIRT));
    strings.append(this->getStringsEventPlaces(CommonEventType::DEAT));
    strings.append(this->getStringsEventPlaces(CommonEventType::BURI));
    strings.append(this->getStringsEventPlaces(CommonEventType::MARR));
    //strings.append(this->getStringsCities());
    std::sort(strings.begin(), strings.end());
    std::unique(strings.begin(), strings.end());
    return strings;
}

QStringList Record::getStringsDeathCause() const
{
    QStringList causes;
    QString cause;
    for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
    {
        cause = this->getIndividualDeathCause(ref);
        if(!cause.isEmpty() && !causes.contains(cause))
        {
            causes.push_back(cause);
        }
    }
    std::sort(causes.begin(), causes.end());
    return causes;
}

QStringList Record::getStringsCities() const
{
    QStringList cities;
    QString city;
    unsigned int count;

    for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
    {
        count = this->getIndividualResiCount(ref);
        for(unsigned int i = 0; i < count; i++)
        {
            city = this->getIndividualResiAddrCity(ref, i);
            if(!city.isEmpty() && !cities.contains(city))
            {
                cities.push_back(city);
            }
        }
    }
    std::sort(cities.begin(), cities.end());
    return cities;
}

QStringList Record::getStringsAddress(const QString &city) const
{
    QStringList addresses;
    QString address;
    unsigned int count;

    for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
    {
        count = this->getIndividualResiCount(ref);
        for(unsigned int i = 0; i < count; i++)
        {
            if(this->getIndividualResiAddrCity(ref, i) == city)
            {
                address = this->getIndividualResiAddrAddr(ref, i);
                if(!address.isEmpty() && !addresses.contains(address))
                {
                    addresses.push_back(address);
                }
            }
        }
    }
    std::sort(addresses.begin(), addresses.end());
    return addresses;
}

QStringList Record::getStringsEducation() const
{
    QStringList educations;
    QString education;
    unsigned int count;

    for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
    {
        count = this->getIndividualEducCount(ref);
        for(unsigned int i = 0; i < count; i++)
        {
            education = this->getIndividualEducDescription(ref, i);
            if(!education.isEmpty() && !educations.contains(education))
            {
                educations.push_back(education);
            }
        }
    }
    std::sort(educations.begin(), educations.end());
    return educations;
}

QStringList Record::getStringsOccupation() const
{
    QStringList occupations;
    QString occupation;
    unsigned int count;

    for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
    {
        count = this->getIndividualOccuCount(ref);
        for(unsigned int i = 0; i < count; i++)
        {
            occupation = this->getIndividualOccuDescription(ref, i);
            if(!occupation.isEmpty() && !occupations.contains(occupation))
            {
                occupations.push_back(occupation);
            }
        }
    }
    std::sort(occupations.begin(), occupations.end());
    return occupations;
}

QStringList Record::getStringsReligion() const
{
    QStringList religions;
    QString religion;
    unsigned int count;

    for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
    {
        count = this->getIndividualReliCount(ref);
        for(unsigned int i = 0; i < count; i++)
        {
            religion = this->getIndividualReliDescription(ref, i);
            if(!religion.isEmpty() && !religions.contains(religion))
            {
                religions.push_back(religion);
            }
        }
    }
    std::sort(religions.begin(), religions.end());
    return religions;
}

QStringList Record::getStringsEventPlaces(const CommonEventType t) const
{
    QStringList places;
    QString place;

    // Family events - Marriage
    if(t == CommonEventType::MARR)
    {
        for(Identifier ref = this->getIdentifierFamilyFirst(); ref < this->getIdentifierFamilyLast(); this->getIdentifierFamilyNext(ref))
        {
            place = this->getFamilyMarriagePlaceName(ref);
            if(!place.isEmpty() && !places.contains(place))
            {
                places.push_back(place);
            }
        }
    }

    // Individual's events
    else
    {
        for(Identifier ref = this->getIdentifierIndividualFirst(); ref < this->getIdentifierIndividualLast(); this->getIdentifierIndividualNext(ref))
        {
            switch (t)
            {
            case CommonEventType::BIRT:
                place = this->getIndividualBirthPlaceName(ref);
                break;
            case CommonEventType::DEAT:
                place = this->getIndividualDeathPlaceName(ref);
                break;
            case CommonEventType::BURI:
                place = this->getIndividualBurialPlaceName(ref);
                break;
            default:
                qDebug()<<"RECIEVED UNEXPECTED ENUM VALUE.";
                break;
            }
            if(!place.isEmpty() && !places.contains(place))
            {
                places.push_back(place);
            }
        }
    }
    std::sort(places.begin(), places.end());
    return places;
}




