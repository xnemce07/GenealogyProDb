/*!
 *  \file   importergedcom.cpp
 *  \author Eva Navratilova
 */

#include "importergedcom.h"

const QRegularExpression ImporterGedcom::_lineExpression = QRegularExpression("^\\s*(\\d)\\s+(@([^@ ]+)@\\s+)?(\\w+)(\\s+@([^@ ]+)@)?(\\s(.*))?$");


bool ImporterGedcom::existsFile()
{
    QFileInfo fileInfo(this->_fileToImport);
    return (fileInfo.exists() && fileInfo.isFile());
}

/*Date ImporterGedcom::dateRfc(QString str) const
{
    Date date;
    QStringList list = str.split(' ');
    for(auto it = list.begin(); it != list.end(); it++)
    {
        *it = it->toLower();
        (*it)[0] = (*it)[0].toUpper();
    }
    str = list.join(' ');
    return Date::fromString(str, Qt::RFC2822Date);
}*/

Identifier ImporterGedcom::individualFromXref(const QString xref, Gender g) const
{
    Identifier indi = Identifier::fromString(xref);
    if(!_record->isIndividual(indi))
    {
        indi = _record->newIndividual(indi);
        _record->setIndividualGender(indi, g);
    }
    return indi;
}

Identifier ImporterGedcom::familyFromXref(const QString xref) const
{
    Identifier fam = Identifier::fromString(xref);
    if(!_record->isFamily(fam))
        fam = _record->newFamily(fam);
    return fam;
}

Identifier ImporterGedcom::submitterFromXref(const QString xref) const
{
    Identifier subm = Identifier::fromString(xref);
    if(!_record->isSubmitter(subm))
        subm = _record->newSubmitter(subm);
    return subm;
}

Identifier ImporterGedcom::sourceFromXref(const QString xref) const
{
    Identifier src = Identifier::fromString(xref);
    if(!_record->isSource(src))
        src = _record->newSource(src);
    return src;
}

/*bool ImporterGedcom::getValueOfChildWithTag(const cg::GedcomNode *node, cg::GedcomParser::NodeList *subNodeList, const QString tag, QString &val) const
{
    auto sub = node->childrenWithTag(tag);

    // Possible SIGSEGV???
    subNodeList = &sub;
    if(sub.length() > 0)
    {
        val = sub.first()->value();
        return true;
    }
    return false;
}*/

bool ImporterGedcom::getDateStructure(const QString string, DateType &type, Date &date1, Date &date2) const
{
    // Preinitilalization of values to invalid
    type = DateType::EMPT;
    date1 = Date();
    date2 = Date();



    QString dateExprStr("((\\d\\d?)\\s+)*(([A-Z]{3})[A-Z]*\\s+)*(\\d+)");
    QRegularExpression expression("^(((FROM|TO|BEF|AFT|BET|ABT|CAL|EST)\\s+)*(" + dateExprStr + "))(\\s+(TO|AND)\\s+(" + dateExprStr + "))*$");
    QRegularExpressionMatch match = expression.match(string.toUpper());
    if(match.isValid())
    {
        // captured() returns Null string if nothing captured
        // If captured a date in the first date position
        if(!match.captured(9).isNull())
        {
            date1 = this->dateFromMatch(match.captured(9), match.captured(8),match.captured(6));

            // If captured FROM|TO|BEF|AFT|BET|ABT|CAL|EST
            if(!match.captured(3).isNull())
            {
                QString delim1, delim2;
                delim1 = match.captured(3);
                if(delim1 == "FROM")
                {
                    type = DateType::PERIOD;
                }
                else if(delim1 == "TO")
                {
                    type = DateType::PERIOD;
                    date2 = date1;
                    date1 = Date();
                }
                else if(delim1 == "BEF")
                {
                    type = DateType::BEFORE;
                }
                else if(delim1 == "AFT")
                {
                    type = DateType::AFTER;
                }
                else if(delim1 == "BET")
                {
                    type = DateType::BETWEEN;
                }
                else // ABT|CAL|EST - Estimated dates
                {
                    type = DateType::ESTIMATED;
                }

                // Captured a second date?
                if(!match.captured(11).isNull())
                {
                    delim2 = match.captured(11);
                    if((delim1 == "FROM" && delim2 == "TO") || (delim1 == "BET" && delim2 == "AND"))
                    {
                        date2 = this->dateFromMatch(match.captured(17), match.captured(16), match.captured(14));
                    }
                    else // Invalid combination
                    {
                        return false;
                    }
                }
                else if(delim1 == "BET")    // BET needs a following AND part
                {
                    return false;
                }
            }
            // It is a simple date if not captured FROM|TO|BEF|AFT|BET|ABT|CAL|EST
            else
                type = DateType::SIMPLE;
        }
    }
    return true;
}

bool ImporterGedcom::getAncestryDescriptionData(const cg::GedcomNode *structure, QString &description, DateType &datetype, Date &date1, Date &date2) const
{
    description = structure->value();

    QRegularExpression ancestryDescriptionExpression("(.*)(\\s+\\((.+)\\))");
    QRegularExpressionMatch matchAncestryDescription = ancestryDescriptionExpression.match(description);
    if(matchAncestryDescription.isValid())
    {
        QString newDescription = matchAncestryDescription.captured(1);
        QString newDate = matchAncestryDescription.captured(3);

        newDate.remove(' ');

        QString dateExpression("[^\\d]*((((\\d+)\\.)?(\\d+)\\.)?(\\d+))");
        QRegularExpression dateFullExpression(dateExpression + "[^\\d-]*(-" + dateExpression + ")?[^\\d]*");
        QRegularExpressionMatch matchDateFull = dateFullExpression.match(newDate);

        if(matchDateFull.isValid())
        {
            Date dateFrom(matchDateFull.captured(6).toInt(),
                          matchDateFull.captured(5).toInt(),
                          matchDateFull.captured(4).toInt());
            Date dateTo  (matchDateFull.captured(13).toInt(),
                          matchDateFull.captured(12).toInt(),
                          matchDateFull.captured(11).toInt());

            if(dateFrom.isValid())
            {
                description = newDescription;
                date1 = dateFrom;
                if(dateTo.isValid())
                {
                    date2 = dateTo;
                    datetype = DateType::PERIOD;
                }
                else
                {
                    datetype = DateType::AFTER;
                }
            }
        }
    }
    return true;
}

bool ImporterGedcom::getAncestryAddressData(const cg::GedcomNode *structure, QString &city, QString &addr, DateType &datetype, Date &date1, Date &date2) const
{
    QString description;
    this->getAncestryDescriptionData(structure, description, datetype, date1, date2);
    QRegularExpression address("\\s*([^\\d]+)\\s+(\\d+[^\\s]*)\\s*");
    QRegularExpressionMatch matchAddress = address.match(description);
    if(matchAddress.isValid())
    {
        city = matchAddress.captured(1);
        addr = matchAddress.captured(2);
    }
    else
    {
        addr = description;
    }
    return true;
}

bool ImporterGedcom::getAttributeStructureData(const cg::GedcomNode *structure, QString &description, DateType &datetype, Date &date1, Date &date2) const
{
    description = structure->value();

    if(structure->childrenWithTag("DATE").length() > 0)
    {
        auto dateStruct = structure->childrenWithTag("DATE").first();
        this->getDateStructure(dateStruct->value(), datetype, date1, date2);
    }
    return true;
}

bool ImporterGedcom::getSourceCitationData(const cg::GedcomNode *structure, Identifier &ref, QString &page, QString &url) const
{
    if(structure->childrenWithTag("SOUR").length() > 0)
    {
        auto src = structure->childrenWithTag("SOUR").first();
        ref = this->sourceFromXref(src->xref());

        if(src->childrenWithTag("PAGE").length() > 0)
        {
            page = src->childrenWithTag("PAGE").first()->value();
        }
        if(src->childrenWithTag("_URL").length() > 0)
        {
            url = src->childrenWithTag("_URL").first()->value();
        }


        return true;    // Source citation imported
    }
    return false; // Source citation not imported
}


Date ImporterGedcom::dateFromMatch(QString yearStr, QString monthStr, QString dayStr) const
{
    int d, m, y;

    // QString::toInt returns 0 if conversion failed - desireable
    d = dayStr.toInt();
    y = yearStr.toInt();

    if(monthStr == "JAN")
        m = 1;
    else if(monthStr == "FEB")
        m = 2;
    else if(monthStr == "MAR")
        m = 3;
    else if(monthStr == "APR")
        m = 4;
    else if(monthStr == "MAY")
        m = 5;
    else if(monthStr == "JUN")
        m = 6;
    else if(monthStr == "JUL")
        m = 7;
    else if(monthStr == "AUG")
        m = 8;
    else if(monthStr == "SEP")
        m = 9;
    else if(monthStr == "OCT")
        m = 10;
    else if(monthStr == "NOV")
        m = 11;
    else if(monthStr == "DEC")
        m = 12;
    else
        m = 0;

    return Date(y,m,d);
}

QString ImporterGedcom::getNote(cg::GedcomNode *note) const
{
    QString str = note->value();
    QList<cg::GedcomNode*> conts = note->childrenWithTag("CONT");
    conts.append(note->childrenWithTag("CONC"));
    for(auto it = conts.begin(); it != conts.end(); it++)
    {
        str += (**it).value();
    }
    return str;
}

bool ImporterGedcom::convertIdentifiers(QString &out)
{
    /// TODO - implement via QThread - MUCH QUICKER, eliminates "Not Responding"

    QStringList lineList = out.split('\n');


    for(QStringList::iterator line=lineList.begin(); line != lineList.end(); line++)
    {
        QRegularExpressionMatch match = _lineExpression.match(*line);
        if (match.isValid())
        {
            QString id = match.captured(3);
            if(!id.isNull())
            {
                QString tag = match.captured(4);
                Identifier generatedId;
                if(tag == "INDI")
                    generatedId = this->_record->newIndividual();
                else if(tag == "FAM")
                    generatedId = this->_record->newFamily();
                else if(tag == "SUBM")
                    generatedId = this->_record->newSubmitter();
                else if(tag == "SOUR")
                    generatedId = this->_record->newSource();


                /*QThread *thd = QThread::create(&ImporterGedcom::replaceIdentifier, &generatedId, &id, &lineList, &line);
                thd->moveToThread(&_thread);
                QObject::connect(thd, &QThread::finished, thd, &QObject::deleteLater);
                thd->start();*/

                _referenceDictionary.insert(id, generatedId);

                this->replaceIdentifier(generatedId, id, line);
            }
        }
    }

    // Second run - replace all old ids with newly generated identifiers
    this->replaceReferences(lineList);

    // >>> Overall complexity - 2*n (instead of former cubic: m*n^2 -> n^3)

    out = lineList.join('\n');

    _referenceDictionary.clear(); // Not needed anymore

    //Thus should be solved differently than deleting the whole database
    //this->_record->deleteDatabase();
    return true;
}

bool ImporterGedcom::replaceIdentifier(const Identifier &ref, QString& oldRef, QStringList::iterator &line) const
{
    if(ref.isValid())
    {
        (*line) = line->replace(oldRef,ref.get());
    }
    else{}          // No support for this tag

    return true;
}

bool ImporterGedcom::replaceReferences(QStringList &lineList) const
{
    for(QStringList::iterator line=lineList.begin(); line != lineList.end(); line++)
    {
        QRegularExpressionMatch match = _lineExpression.match(*line);
        if (match.isValid())
        {
            QString id = match.captured(3);
            QString xref = match.captured(6);
            if(!id.isEmpty())
            {

            }
            if(!xref.isEmpty())
            {
                line->replace("@" + xref + "@", "@" + _referenceDictionary.value(xref).get() + "@");
            }
        }
    }
    return true;
}

bool ImporterGedcom::importHead(cg::GedcomNode *head)
{
    cg::GedcomParser::NodeList nodeList;

    /*
    // Save Source
    if(this->getValueOfChildWithTag(head, &nodeList, "SOUR", val))
    {
        this->_record->setHeadSrc(nodeList.first()->value());
    }
    else
    {
        // Source is Mandatory!
        return false;
    }

    // Save Source Version
    if(this->getValueOfChildWithTag(nodeList.first(), nullptr, "VERS", val))
        this->_record->setHeadSrcVersion(val);

    // Save Source Name
    if(this->getValueOfChildWithTag(nodeList.first(), nullptr, "NAME", val))
        this->_record->setHeadSrcName(val);

    // Save Source Corp
    if(this->getValueOfChildWithTag(nodeList.first(), &subNodeList, "CORP", val))
        this->_record->setHeadSrcCorp(val);

    // Save Source Corp Address Structure
    if(this->getValueOfChildWithTag(subNodeList.first(), &subSubNodeList, "CORP", val))
    {
        this->_record->setHeadSrcAddrAddress(val);

        if(this->getValueOfChildWithTag(subSubNodeList.first(), nullptr, "CITY", val))
            this->_record->setHeadSrcAddrCity(val);
        if(this->getValueOfChildWithTag(subSubNodeList.first(), nullptr, "STAE", val))
            this->_record->setHeadSrcAddrState(val);
    }

    // Outer addres parts
    if(this->getValueOfChildWithTag(subNodeList.first(), nullptr, "PHON", val))
        this->_record->setHeadSrcAddrPhone(val);
    if(this->getValueOfChildWithTag(subNodeList.first(), nullptr, "EMAIL", val))
        this->_record->setHeadSrcAddrEmail(val);
    if(this->getValueOfChildWithTag(subNodeList.first(), nullptr, "WWW", val))
        this->_record->setHeadSrcAddrWww(val);

    // Save Source Data
    subNodeList = nodeList.first()->childrenWithTag("DATA");
    if(subNodeList.length() > 0)
    {
        this->_record->setHeadSrcData(subNodeList.first()->value());

        if(this->getValueOfChildWithTag(subNodeList.first(), nullptr, "DATE", val))
            this->_record->setHeadDate(this->dateFromString(val));
    }
    if(this->getValueOfChildWithTag(nodeList.first(), nullptr, "DEST", val))
        this->_record->setHeadDest(val);
    if(this->getValueOfChildWithTag(nodeList.first(), &subNodeList, "DATE", val))
    {
        this->_record->setHeadDate(this->dateFromString(val));
        if(this->getValueOfChildWithTag(subNodeList.first(), nullptr, "TIME", val))
            this->_record->setHeadTime(QTime::fromString(val,"h:m"));
    }
*/


    nodeList = head->childrenWithTag("SUBM");
    if(nodeList.length() > 0)
    {
        Identifier subm = this->submitterFromXref(nodeList.front()->xref());
        _record->setHeadRefSubm(subm);
    }
    else
    {
        return false;
    }
    return true;
}

bool ImporterGedcom::importIndividual(cg::GedcomNode *indi)
{
    Identifier ref = Identifier::fromString(indi->id());
    if(ref.isValid())
    {
        if(!_record->isIndividual(ref))
        {
            Identifier resRef = _record->newIndividual(ref);
            // Invalid INDI ref
            if(! resRef.isValid())
            {
                qDebug() << "SHOULD NOT HAPPEN";
                return false;
            }
        }
    }
    else
        ref = _record->newIndividual();

    // Name
    if(indi->childrenWithTag("NAME").length() > 0)
    {
        auto name = indi->childrenWithTag("NAME").first();
        QString nameValue = name->value();
        QRegularExpression nameExpr("^([^\\/]*[^\\/\\s]+)*\\s*(\\/\\s*(.*[^\\s])?\\s*\\/)?$");
        QRegularExpressionMatch nameMatch = nameExpr.match(nameValue);
        if(nameMatch.isValid())
        {
            _record->setIndividualNameGiven(ref, nameMatch.captured(1));
            _record->setIndividualNameSurname(ref, nameMatch.captured(3));
        }
        if(name->childrenWithTag("GIVN").length() > 0)
        {
            QString strName = name->childrenWithTag("GIVN").first()->value();
            if(! strName.isEmpty())
            {
                    _record->setIndividualNameGiven(ref, strName);
            }
        }
        if(name->childrenWithTag("NPFX").length() > 0)
            _record->setIndividualNamePrefix(ref, name->childrenWithTag("NPFX").first()->value());
        if(name->childrenWithTag("SURN").length() > 0)
        {
            QString strSurn = name->childrenWithTag("SURN").first()->value();
            if(! strSurn.isEmpty())
            {
                _record->setIndividualNameSurname(ref, strSurn);
            }
        }
        if(name->childrenWithTag("_MARNM").length() > 0)
            _record->setIndividualNameMarname(ref, name->childrenWithTag("_MARNM").first()->value());
        if(name->childrenWithTag("NSFX").length() > 0)
            _record->setIndividualNameSuffix(ref, name->childrenWithTag("NSFX").first()->value());
    }

    // Gender
    if(indi->childrenWithTag("SEX").length() > 0)
    {
        QString sexValue = indi->childrenWithTag("SEX").first()->value();
        if(sexValue == "M")
            _record->setIndividualGender(ref, Gender::MALE);
        else if(sexValue == "F")
            _record->setIndividualGender(ref, Gender::FEMALE);
        else
            _record->setIndividualGender(ref, Gender::UNDET);
    }

    // Event structures (Birth, Death, ...)

    // Birth
    this->importIndividualBirth(indi, ref);
    // Christening
    this->importIndividualChristening(indi, ref);
    // Death
    this->importIndividualDeath(indi, ref);
    // Burial
    this->importIndividualBurial(indi, ref);

    // Occupation
    this->importIndividualOccupation(indi, ref);
    // Education
    this->importIndividualEducation(indi, ref);
    // Residence
    this->importIndividualResidence(indi, ref);
    // Religion
    this->importIndividualReligion(indi, ref);

    // Contact
    this->importIndividualContact(indi, ref);

    // Note
    QString noteText;
    auto notes = indi->childrenWithTag("NOTE");
    for(auto note = notes.begin(); note != notes.end(); note++)
    {
        if(note != notes.begin())
        {
            noteText += '\n';
        }
        noteText += this->getNote(*note);
    }
    _record->setIndividualNote(ref, noteText);

    /// TODO - Rest of all the structures!!

    return true;
}

bool ImporterGedcom::importIndividualBirth(cg::GedcomNode *indiStruct, Identifier indi)
{
    cg::GedcomNode* indiEventStruct;
    if(indiStruct->childrenWithTag("BIRT").length() > 0)
    {
        indiEventStruct = indiStruct->childrenWithTag("BIRT").first();

        if(indiEventStruct->childrenWithTag("DATE").length() > 0)
        {
            auto dateStruct = indiEventStruct->childrenWithTag("DATE").first();
            DateType dateType;
            Date date1, date2;
            this->getDateStructure(dateStruct->value(), dateType, date1, date2);
            _record->setIndividualBirthDateType(indi, dateType);
            _record->setIndividualBirthDate1(indi, date1);
            _record->setIndividualBirthDate2(indi, date2);
        }
        if(indiEventStruct->childrenWithTag("PLAC").length() > 0)
        {
            _record->setIndividualBirthPlaceName(indi, indiEventStruct->childrenWithTag("PLAC").first()->value());
        }
        if(indiEventStruct->childrenWithTag("_WIT1").length() > 0)
        {
            Identifier obst = this->individualFromXref(indiEventStruct->childrenWithTag("_WIT1").first()->xref());
            _record->setIndividualBirthObstetrix(indi, obst);
        }

        Identifier src;
        QString page;
        QString url;
        if(this->getSourceCitationData(indiEventStruct, src, page, url))
        {
            _record->setIndividualBirthSourceCitationRef(indi, src);
            _record->setIndividualBirthSourceCitationPage(indi, page);
            _record->setIndividualBirthSourceCitationUrl(indi, url);
        }
    }
    return true;
}

bool ImporterGedcom::importIndividualChristening(cg::GedcomNode *indiStruct, Identifier indi)
{
    cg::GedcomNode* indiEventStruct;
    if(indiStruct->childrenWithTag("CHR").length() > 0)
    {
        indiEventStruct = indiStruct->childrenWithTag("CHR").first();

        if(indiEventStruct->childrenWithTag("DATE").length() > 0)
        {
            auto dateStruct = indiEventStruct->childrenWithTag("DATE").first();
            DateType dateType;
            Date date1, date2;
            this->getDateStructure(dateStruct->value(), dateType, date1, date2);
            _record->setIndividualChristeningDateType(indi, dateType);
            _record->setIndividualChristeningDate1(indi, date1);
            _record->setIndividualChristeningDate2(indi, date2);
        }
        if(indiEventStruct->childrenWithTag("_PRIEST").length() > 0)
        {
            Identifier priest = this->individualFromXref(indiEventStruct->childrenWithTag("_PRIEST").first()->xref());
            _record->setIndividualChristeningPriest(indi, priest);
        }
        if(indiEventStruct->childrenWithTag("_WIT1").length() > 0)
        {
            Identifier godparent = this->individualFromXref(indiEventStruct->childrenWithTag("_WIT1").first()->xref());
            _record->setIndividualChristeningGodfather(indi, godparent);
        }
        if(indiEventStruct->childrenWithTag("_WIT2").length() > 0)
        {
            Identifier godparent = this->individualFromXref(indiEventStruct->childrenWithTag("_WIT2").first()->xref());
            _record->setIndividualChristeningGodmother(indi, godparent);
        }
    }
    return true;
}

bool ImporterGedcom::importIndividualDeath(cg::GedcomNode *indiStruct, Identifier indi)
{
    cg::GedcomNode* indiEventStruct;
    if(indiStruct->childrenWithTag("DEAT").length() > 0)
    {
        indiEventStruct = indiStruct->childrenWithTag("DEAT").first();
        _record->setIndividualDeceased(indi, true);

        if(indiEventStruct->childrenWithTag("DATE").length() > 0)
        {
            auto dateStruct = indiEventStruct->childrenWithTag("DATE").first();
            DateType dateType;
            Date date1, date2;
            this->getDateStructure(dateStruct->value(), dateType, date1, date2);
            _record->setIndividualDeathDateType(indi, dateType);
            _record->setIndividualDeathDate1(indi, date1);
            _record->setIndividualDeathDate2(indi, date2);
        }
        if(indiEventStruct->childrenWithTag("PLAC").length() > 0)
        {
            _record->setIndividualDeathPlaceName(indi, indiEventStruct->childrenWithTag("PLAC").first()->value());
        }
        if(indiEventStruct->childrenWithTag("CAUS").length() > 0)
        {
            _record->setIndividualDeathCause(indi, indiEventStruct->childrenWithTag("CAUS").first()->value());
        }

        Identifier src;
        QString page;
        QString url;
        if(this->getSourceCitationData(indiEventStruct, src, page, url))
        {
            _record->setIndividualDeathSourceCitationRef(indi, src);
            _record->setIndividualDeathSourceCitationPage(indi, page);
            _record->setIndividualDeathSourceCitationUrl(indi, url);
        }
    }
    return true;
}

bool ImporterGedcom::importIndividualBurial(cg::GedcomNode *indiStruct, Identifier indi)
{
    cg::GedcomNode* indiEventStruct;
    if(indiStruct->childrenWithTag("BURI").length() > 0)
    {
        indiEventStruct = indiStruct->childrenWithTag("BURI").first();

        if(indiEventStruct->childrenWithTag("DATE").length() > 0)
        {
            auto dateStruct = indiEventStruct->childrenWithTag("DATE").first();
            DateType dateType;
            Date date1, date2;
            this->getDateStructure(dateStruct->value(), dateType, date1, date2);
            _record->setIndividualBurialDateType(indi, dateType);
            _record->setIndividualBurialDate1(indi, date1);
            _record->setIndividualBurialDate2(indi, date2);
        }
        if(indiEventStruct->childrenWithTag("PLAC").length() > 0)
        {
            _record->setIndividualBurialPlaceName(indi, indiEventStruct->childrenWithTag("PLAC").first()->value());
        }
        if(indiEventStruct->childrenWithTag("_PRIEST").length() > 0)
        {
            Identifier priest = this->individualFromXref(indiEventStruct->childrenWithTag("_PRIEST").first()->xref());
            _record->setIndividualBurialPriest(indi, priest);
        }

        /// TODO - Source citations
    }
    return true;
}

bool ImporterGedcom::importIndividualOccupation(cg::GedcomNode *indiStruct, Identifier indi)
{
    cg::GedcomNode* indiEventStruct;
    for(int i = 0; i < indiStruct->childrenWithTag("OCCU").length(); i++)
    {
        indiEventStruct = indiStruct->childrenWithTag("OCCU").at(i);

        _record->setIndividualOccu(indi);
        unsigned int index = _record->getIndividualOccuCount(indi) - 1;

        QString description;
        DateType datetype;
        Date date1, date2;
        if(_fromAncestry)
        {
            this->getAncestryDescriptionData(indiEventStruct, description, datetype, date1, date2);
        }
        else
        {
            this->getAttributeStructureData(indiEventStruct, description, datetype, date1, date2);
        }
        _record->setIndividualOccuDescription(indi, index, description);
        _record->setIndividualOccuDateType(indi, index, datetype);
        _record->setIndividualOccuDate1(indi, index, date1);
        _record->setIndividualOccuDate2(indi, index, date2);
    }
    return true;
}

bool ImporterGedcom::importIndividualEducation(cg::GedcomNode *indiStruct, Identifier indi)
{
    cg::GedcomNode* indiEventStruct;
    for(int i = 0; i < indiStruct->childrenWithTag("EDUC").length(); i++)
    {
        indiEventStruct = indiStruct->childrenWithTag("EDUC").at(i);

        _record->setIndividualEduc(indi);
        unsigned int index = _record->getIndividualEducCount(indi) - 1;

        QString description;
        DateType datetype;
        Date date1, date2;
        if(_fromAncestry)
        {
            this->getAncestryDescriptionData(indiEventStruct, description, datetype, date1, date2);
        }
        else
        {
            this->getAttributeStructureData(indiEventStruct, description, datetype, date1, date2);
        }
        _record->setIndividualEducDescription(indi, index, description);
        _record->setIndividualEducDateType(indi, index, datetype);
        _record->setIndividualEducDate1(indi, index, date1);
        _record->setIndividualEducDate2(indi, index, date2);
    }
    return true;
}

bool ImporterGedcom::importIndividualResidence(cg::GedcomNode *indiStruct, Identifier indi)
{
    cg::GedcomNode* indiEventStruct;
    for(int i = 0; i < indiStruct->childrenWithTag("RESI").length(); i++)
    {
        indiEventStruct = indiStruct->childrenWithTag("RESI").at(i);

        _record->setIndividualResi(indi);
        unsigned int index = _record->getIndividualResiCount(indi) - 1;

        QString description, city, addr;
        DateType datetype;
        Date date1, date2;
        this->getAttributeStructureData(indiEventStruct, description, datetype, date1, date2);
        _record->setIndividualResiDateType(indi, index, datetype);
        _record->setIndividualResiDate1(indi, index, date1);
        _record->setIndividualResiDate2(indi, index, date2);

        auto addrStruct = indiEventStruct->childrenWithTag("ADDR");
        auto placStruct = indiEventStruct->childrenWithTag("PLAC");
        if(addrStruct.length() > 0)
        {
            if(_fromAncestry)
            {
                this->getAncestryAddressData(addrStruct.first(), city, addr, datetype, date1, date2);
                _record->setIndividualResiAddrCity(indi, index, city);
                _record->setIndividualResiAddrAddr(indi, index, addr);
                _record->setIndividualResiDateType(indi, index, datetype);
                _record->setIndividualResiDate1(indi, index, date1);
                _record->setIndividualResiDate2(indi, index, date2);
            }
            else
            {
                addr = this->getNote(addrStruct.first());
                _record->setIndividualResiAddrAddr(indi, index, addr);
                auto cityStruct = addrStruct.first()->childrenWithTag("CITY");
                if(cityStruct.length() > 0)
                {
                    _record->setIndividualResiAddrCity(indi, index, cityStruct.first()->value());
                }
            }
        }
        else if(placStruct.length() > 0)
        {
            if(_fromAncestry)
            {
                this->getAncestryAddressData(placStruct.first(), city, addr, datetype, date1, date2);
                _record->setIndividualResiAddrCity(indi, index, city);
                _record->setIndividualResiAddrAddr(indi, index, addr);
                _record->setIndividualResiDateType(indi, index, datetype);
                _record->setIndividualResiDate1(indi, index, date1);
                _record->setIndividualResiDate2(indi, index, date2);
            }
            else
            {
                QString plac = placStruct.first()->value();
                _record->setIndividualResiAddrAddr(indi, index, plac);
            }
        }
    }
    return true;
}

bool ImporterGedcom::importIndividualReligion(cg::GedcomNode *indiStruct, Identifier indi)
{
    cg::GedcomNode* indiEventStruct;
    for(int i = 0; i < indiStruct->childrenWithTag("RELI").length(); i++)
    {
        indiEventStruct = indiStruct->childrenWithTag("RELI").at(i);

        _record->setIndividualReli(indi);
        unsigned int index = _record->getIndividualReliCount(indi) - 1;

        QString description;
        DateType datetype;
        Date date1, date2;
        if(_fromAncestry)
        {
            this->getAncestryDescriptionData(indiEventStruct, description, datetype, date1, date2);
        }
        else
        {
            this->getAttributeStructureData(indiEventStruct, description, datetype, date1, date2);
        }
        _record->setIndividualReliDescription(indi, index, description);
        _record->setIndividualReliDateType(indi, index, datetype);
        _record->setIndividualReliDate1(indi, index, date1);
        _record->setIndividualReliDate2(indi, index, date2);
    }
    return true;
}

bool ImporterGedcom::importIndividualContact(cg::GedcomNode *indiStruct, Identifier indi)
{
    cg::GedcomNode* indiEventStruct;
    if(indiStruct->childrenWithTag("EVEN").length() > 0)
    {
        indiEventStruct = indiStruct->childrenWithTag("EVEN").first();

        if(indiEventStruct->childrenWithTag("PHON").length() > 0)
        {
            _record->setIndividualPhone(indi, indiEventStruct->childrenWithTag("PHON").first()->value());
        }
        if(indiEventStruct->childrenWithTag("EMAIL").length() > 0)
        {
            _record->setIndividualEmail(indi, indiEventStruct->childrenWithTag("EMAIL").first()->value());
        }
        if(indiEventStruct->childrenWithTag("WWW").length() > 0)
        {
            _record->setIndividualWww(indi, indiEventStruct->childrenWithTag("WWW").first()->value());
        }
    }
    return true;
}

bool ImporterGedcom::importFamily(cg::GedcomNode *fam)
{
    Identifier ref = Identifier::fromString(fam->id());
    if(ref.isValid())
    {
        if(!this->_record->isFamily(ref))
        {
            Identifier resRef = this->_record->newFamily(ref);
            if(! resRef.isValid())
            {
                qDebug() << "SHOULD NOT HAPPEN FAM";
                return false;
            }
        }
    }
    else
        ref = this->_record->newFamily();

    // Husband
    if(fam->childrenWithTag("HUSB").length() > 0)
    {
        Identifier refHusb = individualFromXref(fam->childrenWithTag("HUSB").first()->xref(), Gender::MALE);
        // Gender check
        if(_record->getIndividualGender(refHusb) == Gender::MALE)
        {
            this->_record->setFamilyHusband(ref, refHusb);
        }
    }

    // Wife
    if(fam->childrenWithTag("WIFE").length() > 0)
    {
        Identifier refWife = this->individualFromXref(fam->childrenWithTag("WIFE").first()->xref(), Gender::FEMALE);
        // Gender check
        if(_record->getIndividualGender(refWife) == Gender::FEMALE)
        {
            this->_record->setFamilyWife(ref, refWife);
        }
    }

    // Child n-times
    for(int i = 0; i < fam->childrenWithTag("CHIL").length(); i++)
    {
        cg::GedcomNode* chil = fam->childrenWithTag("CHIL").at(i);
        Identifier refChil = individualFromXref(chil->xref());
        this->_record->setFamilyChild(ref, refChil);
    }

    // Marriage
    this->importFamilyMarriage(fam, ref);
    // Divorce
    this->importFamilyDivorce(fam, ref);

    return true;
}

bool ImporterGedcom::importFamilyMarriage(cg::GedcomNode *famStruct, Identifier fam)
{
    cg::GedcomNode* famEventStruct;
    if(famStruct->childrenWithTag("MARR").length() > 0)
    {
        famEventStruct = famStruct->childrenWithTag("MARR").first();
        _record->setFamilyMarried(fam, true);

        if(famEventStruct->childrenWithTag("DATE").length() > 0)
        {
            auto dateStruct = famEventStruct->childrenWithTag("DATE").first();
            DateType dateType;
            Date date1, date2;
            this->getDateStructure(dateStruct->value(), dateType, date1, date2);
            _record->setFamilyMarriageDateType(fam, dateType);
            _record->setFamilyMarriageDate1(fam, date1);
            _record->setFamilyMarriageDate2(fam, date2);
        }
        if(famEventStruct->childrenWithTag("PLAC").length() > 0)
        {
            _record->setFamilyMarriagePlaceName(fam, famEventStruct->childrenWithTag("PLAC").first()->value());
        }
        if(famEventStruct->childrenWithTag("_PRIEST").length() > 0)
        {
            Identifier priest = this->individualFromXref(famEventStruct->childrenWithTag("_PRIEST").first()->xref());
            _record->setFamilyMarriagePriest(fam, priest);
        }
        if(famEventStruct->childrenWithTag("_WIT1").length() > 0)
        {
            Identifier witness = this->individualFromXref(famEventStruct->childrenWithTag("_WIT1").first()->xref());
            _record->setFamilyMarriageWitness1(fam, witness);
        }
        if(famEventStruct->childrenWithTag("_WIT2").length() > 0)
        {
            Identifier witness = this->individualFromXref(famEventStruct->childrenWithTag("_WIT2").first()->xref());
            _record->setFamilyMarriageWitness2(fam, witness);
        }

        Identifier src;
        QString page;
        QString url;
        if(this->getSourceCitationData(famEventStruct, src, page, url))
        {
            _record->setFamilyMarriageSourceCitationRef(fam, src);
            _record->setFamilyMarriageSourceCitationPage(fam, page);
            _record->setFamilyMarriageSourceCitationUrl(fam, url);
        }
    }
    return true;
}

bool ImporterGedcom::importFamilyDivorce(cg::GedcomNode *famStruct, Identifier fam)
{
    cg::GedcomNode* famEventStruct;
    if(famStruct->childrenWithTag("DIV").length() > 0)
    {
        famEventStruct = famStruct->childrenWithTag("DIV").first();
        _record->setFamilyDivorced(fam, true);

        if(famEventStruct->childrenWithTag("DATE").length() > 0)
        {
            auto dateStruct = famEventStruct->childrenWithTag("DATE").first();
            DateType dateType;
            Date date1, date2;
            this->getDateStructure(dateStruct->value(), dateType, date1, date2);
            _record->setFamilyDivorceDateType(fam, dateType);
            _record->setFamilyDivorceDate1(fam, date1);
            _record->setFamilyDivorceDate2(fam, date2);
        }
    }
    return true;
}

/// DONE FULLY
bool ImporterGedcom::importSubmitter(cg::GedcomNode *subm)
{
    Identifier ref = Identifier::fromString(subm->id());
    if(ref.isValid())
    {
        if(!this->_record->isSubmitter(ref))
        {
            Identifier resRef = this->_record->newSubmitter(ref);
            if(! resRef.isValid())
            {
                qDebug() << "SHOULD NOT HAPPEN SUBM";
                return false;
            }
        }
    }
    else
        ref = this->_record->newSubmitter();

    if(subm->childrenWithTag("NAME").length() > 0)
    {
        this->_record->setSubmitterName(ref, subm->childrenWithTag("NAME").first()->value());
    }
    if(subm->childrenWithTag("LANG").length() > 0)
    {
        this->_record->setSubmitterLang(ref, subm->childrenWithTag("LANG").first()->value());
    }
    if(subm->childrenWithTag("CHAN").length() > 0)
    {
        auto chan = subm->childrenWithTag("CHAN").first();
        if(chan->childrenWithTag("DATE").length() > 0)
        {
            auto date = subm->childrenWithTag("DATE").first();
            DateType dateType;
            Date date1, date2;
            this->getDateStructure(date->value(), dateType, date1, date2);
            this->_record->setSubmitterDate(ref, date1);
            if(date->childrenWithTag("TIME").length() > 0)
            {
                QTime time;
                time.fromString(date->childrenWithTag("TIME").first()->value(), "hh:mm:ss");
                this->_record->setSubmitterTime(ref, time);
            }
        }
        this->_record->setSubmitterLang(ref, subm->childrenWithTag("LANG").first()->value());
    }
    if(subm->childrenWithTag("LANG").length() > 0)
    {
        this->_record->setSubmitterLang(ref, subm->childrenWithTag("LANG").first()->value());
    }
    if(subm->childrenWithTag("NOTE").length() > 0)
    {
        this->_record->setSubmitterNote(ref, this->getNote(subm->childrenWithTag("NOTE").first()));
    }
    return true;
}

/// DONE for sources of BIRT, MARR and DEAT (so probably OK)
bool ImporterGedcom::importSource(cg::GedcomNode *src)
{
    Identifier ref = Identifier::fromString(src->id());
    if(ref.isValid())
    {
        if(!this->_record->isSource(ref))
        {
            Identifier resRef = this->_record->newSource(ref);
            if(! resRef.isValid())
            {
                qDebug()<<"SHOULD NOT HAPPEN SOUR";
                return false;
            }
        }
    }
    else
        ref = this->_record->newSource();

    /// TODO import rest of the data

    if(src->childrenWithTag("DATA").length() > 0)
    {
        cg::GedcomNode* data = src->childrenWithTag("DATA").first();
        if(data->childrenWithTag("EVEN").length() > 0)
        {
            auto evenList = data->childrenWithTag("EVEN");

            // For all event data
            for(auto even = evenList.begin(); even != evenList.end(); even++)
            {
                QString val = (*even)->value();

                unsigned int index = 0;
                CommonEventType type = CommonEventType::EMPT;

                if(val == "BIRT")
                {
                    type = CommonEventType::BIRT;
                    index = this->_record->setSourceData(ref, type);
                }
                else if (val == "DEAT")
                {
                    type = CommonEventType::DEAT;
                    index = this->_record->setSourceData(ref, type);
                }
                else if(val == "MARR")
                {
                    type = CommonEventType::MARR;
                    index = this->_record->setSourceData(ref, type);
                }

                // Possibly add more options??

                if(type != CommonEventType::EMPT)
                {
                    if((**even).childrenWithTag("DATE").length() > 0)
                    {
                        DateType dateType;
                        Date date1, date2;
                        this->getDateStructure((**even).childrenWithTag("DATE").first()->value(), dateType, date1, date2);
                        this->_record->setSourceDataDateFrom(ref, type, index, date1);
                        this->_record->setSourceDataDateTo(ref, type, index, date2);

                    }
                    if((**even).childrenWithTag("PLAC").length() > 0)
                    {
                        QString plac = (**even).childrenWithTag("PLAC").first()->value();
                        this->_record->setSourceDataPlac(ref, type, index, plac);
                    }
                    if((**even).childrenWithTag("_PAG1").length() > 0)
                    {
                        QString page = (**even).childrenWithTag("_PAG1").first()->value();
                        this->_record->setSourceDataPage1(ref, type, index, page);
                    }
                    if((**even).childrenWithTag("_PAG2").length() > 0)
                    {
                        QString page = (**even).childrenWithTag("_PAG2").first()->value();
                        this->_record->setSourceDataPage2(ref, type, index, page);
                    }
                    if((**even).childrenWithTag("_URL").length() > 0)
                    {
                        QString url = (**even).childrenWithTag("_URL").first()->value();
                        this->_record->setSourceDataUrl(ref, type, index, url);
                    }
                }
            }
        }
    }

    if(src->childrenWithTag("AUTH").length() > 0)
    {
        QString archive = this->getNote(src->childrenWithTag("AUTH").first());
        this->_record->setSourceArchive(ref, archive);
    }

    if(src->childrenWithTag("TITL").length() > 0)
    {
        QString titl = this->getNote(src->childrenWithTag("TITL").first());
        this->_record->setSourceTitle(ref, titl);
    }

    if(src->childrenWithTag("PUBL").length() > 0)
    {
        QString orig = this->getNote(src->childrenWithTag("PUBL").first());
        this->_record->setSourceOriginator(ref, orig);
    }

    /// TODO - DOCUMENT EXPANSION !!!!!
    ///
    /// +1 _URL <URL_OF_SOURCE>
    ///    +2 [CONC|CONT] <URL_OF_SOURCE>
    ///
    if(src->childrenWithTag("_URL").length() > 0)
    {
        QString url = this->getNote(src->childrenWithTag("_URL").first());
        this->_record->setSourceUrl(ref, url);
    }
    return true;
}

void ImporterGedcom::notifyNodeImported()
{
    _nodeCountImported++;
    int percent = (_nodeCountImported * 100) / _nodeCount;
    //qDebug() << "IMPORTED "<<_nodeCountImported<<" OF "<<_nodeCount;
    if(percent > _nodePercent)
    {
        emit(this->objectImported());

        while(percent > _nodePercent)
        {
            _nodePercent++;
        }
    }
}

ImporterGedcom::ImporterGedcom()
{
    // Initialize ansel codec for later use
    _pTextCodec = new cg::AnselCodec();
}

bool ImporterGedcom::importFile(QString filename, Record &record, ImportType &appType)
{
    this->_fileToImport = filename;
    this->_record = &record;

    // Check whether file exists
    if(!this->existsFile())
    {
        qDebug() << "NON-EXISTENT FILE";
        return false;
    }

    QString source;
    QString encoding;
    const QString ancestry = "Ancestry";
    cg::GedcomParser::NodeList headList, indiList, famList, submList, srcList;
    QTemporaryFile temp;

    // Get encoding information from file to import
    if(!_parser.getEncoding(this->_fileToImport, encoding, source))
    {
        qDebug() << "IMPORT - getEncoding FAIL";
        return false;
    }

    // Encoding must be Ansel
    if(encoding != QString("ANSEL"))
    {
        qDebug() << "IMPORT - encoding not ANSEL";
        return false;
    }

    _fromAncestry = (source == ancestry);

    if(source == APP_SH_NAME)
    {
        appType = ImportType::THIS_APP;
    }
    // If source is not this application, Identifiers (references) in the file
    // must be converted to valid format
    else
    {
        appType = ImportType::OTHER_APP;

        QString contents;
        QFile file(this->_fileToImport);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "IMPORT - open file FAIL";
            return false;
        }
        QTextStream in(&file);
        in.setCodec("UTF-8");
        in.setGenerateByteOrderMark(true);

        in.seek(0);
        contents = in.readAll();

        this->convertIdentifiers(contents);

        temp.open();
        if(temp.isOpen())
        {
            QTextStream out(&temp);
            out.setCodec("UTF-8");
            out.setGenerateByteOrderMark(true);

            out << contents;

            out.flush();
            in.flush();

            temp.close();
            this->_fileToImport = temp.fileName();
        }
        else
        {
            qDebug()<<"IMPORT - file not open";
            return false;
        }
    }

    // Parse input file
    _parser.parse(this->_fileToImport);

    // Create lists with records for certain tags
    headList = this->_parser.rootNode()->childrenWithTag("HEAD");
    indiList = this->_parser.nodesWithTag("INDI");
    famList = this->_parser.nodesWithTag("FAM");
    submList = this->_parser.nodesWithTag("SUBM");
    srcList = this->_parser.nodesWithTag("SOUR");

    _nodeCount = headList.length() + indiList.length() + famList.length() + submList.length() + srcList.length();
    _nodeCountImported = 0;

    emit(this->objectsToImport(100));

    // Precisely one head allowed
    if(headList.size() == 1 && this->importHead(headList.first()));
    else
    {
        // Submitter not found
        Identifier subm = _record->newSubmitter();
        _record->setHeadRefSubm(subm);
    }
    for(auto head : headList)
    {
        Q_UNUSED(head);
        notifyNodeImported();
        //emit(this->objectImported());
    }

    // Import all individuals
    for(auto it=indiList.begin(); it != indiList.end(); it++)
    {
        if(!this->importIndividual(*it))
        {
            return false;
        }
        notifyNodeImported();
        //emit(this->objectImported());
    }

    // Import all families
    for(auto it=famList.begin(); it != famList.end(); it++)
    {
        if(!this->importFamily(*it))
        {
            return false;
        }
        notifyNodeImported();
        //emit(this->objectImported());
    }

    // Import all submitters
    for(auto it=submList.begin(); it != submList.end(); it++)
    {
        if(!this->importSubmitter(*it))
        {
            return false;
        }
        notifyNodeImported();
        //emit(this->objectImported());
    }

    // Import all sources
    for(auto it=srcList.begin(); it != srcList.end(); it++)
    {
        if(!this->importSource(*it))
        {
            return false;
        }
        notifyNodeImported();
        //emit(this->objectImported());
    }

    return true;
}
