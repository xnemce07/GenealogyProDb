/*!
 *  \file   exportergedcom.cpp
 *  \author Eva Navratilova
 */

#include "exportergedcom.h"

QString ExporterGedcom::genderToString(Gender g) const
{
    QString str;
    switch (g)
    {
    case Gender::MALE:
        str = "M";
        break;
    case Gender::FEMALE:
        str = "F";
        break;
    default:
        str = "U";
    }
    return str;
}

QString ExporterGedcom::dateToString(Date date) const
{
    QString day, month, year;
    if(DatePrecision::EMPTY != date.datePrecision())
    {
        year = QString::number(date.year());
        if(DatePrecision::YEAR != date.datePrecision())
        {
            switch(date.month())
            {
            case 1:
                month = "JAN ";
                break;
            case 2:
                month = "FEB ";
                break;
            case 3:
                month = "MAR ";
                break;
            case 4:
                month = "APR ";
                break;
            case 5:
                month = "MAY ";
                break;
            case 6:
                month = "JUN ";
                break;
            case 7:
                month = "JUL ";
                break;
            case 8:
                month = "AUG ";
                break;
            case 9:
                month = "SEP ";
                break;
            case 10:
                month = "OCT ";
                break;
            case 11:
                month = "NOV ";
                break;
            case 12:
                month = "DEC ";
                break;
            default:
                month = "";
            }
            if(DatePrecision::YEAR_MONTH != date.datePrecision())
            {
                day = QString::number(date.day()) + " ";
            }
        }
    }
    return day + month + year;
}

QString ExporterGedcom::timeToString(QTime time) const
{
    QString hour = QString::number(time.hour());
    QString minute = QString::number(time.minute());
    return hour + ":" + minute;
}

QString ExporterGedcom::createContStructure(QString text, unsigned int level)
{
    const int maxNoteLen = 248;
    QString str;
    str = text.left(maxNoteLen) + "\n";
    while(! text.mid(maxNoteLen).isEmpty())
    {
        text = text.mid(maxNoteLen);
        str += QString::number(level) + " CONT " + text.left(maxNoteLen) + "\n";
    }
    return str;
}

QString ExporterGedcom::eventToString(const CommonEventType t) const
{
    QString result;
    switch (t)
    {
    case CommonEventType::BIRT:
        result = "BIRT";
        break;
    case CommonEventType::CHR:
        result = "CHR";
        break;
    case CommonEventType::DEAT:
        result = "DEAT";
        break;
    case CommonEventType::BURI:
        result = "BURI";
        break;
    case CommonEventType::EDUC:
        result = "EDUC";
        break;
    case CommonEventType::NATI:
        result = "NATI";
        break;
    case CommonEventType::OCCU:
        result = "OCCU";
        break;
    case CommonEventType::RELI:
        result = "RELI";
        break;
    case CommonEventType::RESI:
        result = "RESI";
        break;
    case CommonEventType::MARR:
        result = "MARR";
        break;
    case CommonEventType::DIV:
        result = "DIV";
        break;
    default:
        break;
    }
    return result;
}

QString ExporterGedcom::exportDate(int level, const DateType datetype, const Date date1, const Date date2)
{
    QString str;
    bool isDateOk = false;

    switch(datetype)
    {
    case DateType::SIMPLE:
    case DateType::ESTIMATED:
    case DateType::BEFORE:
    case DateType::AFTER:
        isDateOk = (date1.isValid())? true : false;
        break;
    case DateType::BETWEEN:
    case DateType::PERIOD:
        isDateOk = (date1.isValid() && date2.isValid())? true : false;
        break;
    default:
        // EMPT not needed
        break;
    }

    if(isDateOk)
    {
        QString strDate1 = this->dateToString(date1);
        QString strDate2 = this->dateToString(date2);

        str += QString::number(level) + " DATE ";

        switch(datetype)
        {
        case DateType::SIMPLE:
            str += strDate1;
            break;
        case DateType::ESTIMATED:
            str += "EST " + strDate1;
            break;
        case DateType::AFTER:
            str += "AFT " + strDate1;
            break;
        case DateType::BEFORE:
            str += "BEF " + strDate1;
            break;
        case DateType::BETWEEN:
            str += "BET " + strDate1 + " AND " + strDate2;
            break;
        case DateType::PERIOD:
            str += "FROM " + strDate1 + " TO " + strDate2;
            break;
        default:
            // EMPT not necessary
            break;
        }
        str += "\n";
    }
    return str;
}

QString ExporterGedcom::exportAddress(int level, const QString addr, const QString city)
{
    QString str;
    if(! addr.isEmpty())
    {
        str += QString::number(level) + " ADDR " + addr + "\n";
        level++;
        if(! city.isEmpty())
        {
            str += QString::number(level) + " CITY " + city + "\n";
        }
    }
    return str;
}

QString ExporterGedcom::exportSourceCitation(int level, const Identifier src, const QString page, const QString url)
{
    QString str;
    if(_record->isSource(src))
    {
        str += QString::number(level) + " SOUR @" + src.get() + "@" + "\n";
        level++;
        if(!page.isEmpty())
        {
            str += QString::number(level) + " PAGE " + page + "\n";
        }
        if(!url.isEmpty())
        {
            str += QString::number(level) + " _URL " + url + "\n";
        }
    }
    return str;
}

QString ExporterGedcom::exportPriest(int level, Identifier priest)
{
    QString str;
    if(_record->isIndividual(priest))
    {
        str += QString::number(level) + " _PRIEST @" + priest.get() + "@" + "\n";
    }
    return  str;
}

QString ExporterGedcom::exportWitness1(int level, Identifier wit)
{
    QString str;
    if(_record->isIndividual(wit))
    {
        str += QString::number(level) + " _WIT1 @" + wit.get() + "@" + "\n";
    }
    return  str;
}

QString ExporterGedcom::exportWitness2(int level, Identifier wit)
{
    QString str;
    if(_record->isIndividual(wit))
    {
        str += QString::number(level) + " _WIT2 @" + wit.get() + "@" + "\n";
    }
    return  str;
}

///////////////////////////////////////////////////////////////////////////////

QString ExporterGedcom::exportHeader()
{
    QString str;
    Date date = Date::currentDate();
    QTime time = QTime::currentTime();

    str =   "0 HEAD\n"
            "1 SOUR " + QString::fromUtf8(APP_SH_NAME) + "\n"
            "2 VERS " + QString::fromUtf8(APP_VERS_CURR) + "\n"
            "2 NAME " + QString::fromUtf8(APP_NAME) + "\n"
            "2 CORP " + QString::fromUtf8(APP_AUTH) + "\n"
            "1 DEST " + QString::fromUtf8(APP_SH_NAME) + "\n"
            "1 DATE " + this->dateToString(date) + "\n"
            "2 TIME " + this->timeToString(time) + "\n"
            "1 SUBM @" + _record->getHeadRefSubm().get() + "@\n"
            "1 FILE " + this->_filename + "\n"
            "1 GEDC\n"
            "2 VERS 5.5.1\n"
            "2 FORM LINEAGE-LINKED\n"
            "1 CHAR UTF-8\n";

    return str;
}

// Probalby all done
QString ExporterGedcom::exportIndividual(Identifier indi)
{
    QString str;
    if(_record->isIndividual(indi))
    {
        str = "0 @" + indi.get() + "@ INDI\n";
        QString nameGivn, nameSurn, nameMarr, namePref, nameSuff;
        nameGivn = _record->getIndividualNameGiven(indi);
        nameSurn = _record->getIndividualNameSurnameBirth(indi);
        nameMarr = _record->getIndividualNameSurnameMarried(indi);
        namePref = _record->getIndividualNamePrefix(indi);
        nameSuff = _record->getIndividualNameSuffix(indi);

        if((nameGivn.length() + nameSurn.length() + nameMarr.length() + namePref.length() + nameSuff.length()) > 0)
        {
            str += "1 NAME";
            if(! nameGivn.isEmpty())
                str += " " + nameGivn;
            if(! nameSurn.isEmpty())
                str += " /" + nameSurn + "/";
            str += "\n";
            if(! nameMarr.isEmpty())
                str += "2 _MARNM " + nameMarr + "\n";
            if(! namePref.isEmpty())
                str += "2 NPFX " + namePref + "\n";
            if(! nameSuff.isEmpty())
                str += "2 NSFX " + nameSuff + "\n";
        }

        str += "1 SEX " + this->genderToString(_record->getIndividualGender(indi)) + "\n";

        // BIRT
        if(_record->isIndividualBorn(indi))
        {
            str += "1 " + this->eventToString(CommonEventType::BIRT) + "\n";

            DateType datetype = _record->getIndividualBirthDateType(indi);
            Date date1 = _record->getIndividualBirthDate1(indi);
            Date date2 = _record->getIndividualBirthDate2(indi);

            str += this->exportDate(2, datetype, date1, date2);

            QString plac = _record->getIndividualBirthPlaceName(indi);
            if(! plac.isEmpty())
            {
                str += "2 PLAC " + plac + "\n";
            }

            Identifier obst = _record->getIndividualBirthObstetrix(indi);
            str += this->exportWitness1(2, obst);

            Identifier src = _record->getIndividualBirthSourceRef(indi);
            QString page = _record->getIndividualBirthSourceCitationPage(indi);
            QString url = _record->getIndividualBirthSourceCitationUrl(indi);

            str += this->exportSourceCitation(2, src, page, url);
        }

        // CHR
        if(_record->isIndividualChristened(indi))
        {
            str += "1 " + this->eventToString(CommonEventType::CHR) + "\n";

            DateType datetype = _record->getIndividualChristeningDateType(indi);
            Date date1 = _record->getIndividualChristeningDate1(indi);
            Date date2 = _record->getIndividualChristeningDate2(indi);

            str += this->exportDate(2, datetype, date1, date2);

            Identifier priest = _record->getIndividualChristeningPriest(indi);
            Identifier godfather = _record->getIndividualChristeningGodfather(indi);
            Identifier godmother = _record->getIndividualChristeningGodmother(indi);
            str += this->exportPriest(2, priest);
            str += this->exportWitness1(2, godfather);
            str += this->exportWitness2(2, godmother);
        }

        // DEAT
        if(_record->isIndividualDeceased(indi))
        {
            str += "1 " + this->eventToString(CommonEventType::DEAT) + "\n";

            DateType datetype = _record->getIndividualDeathDateType(indi);
            Date date1 = _record->getIndividualDeathDate1(indi);
            Date date2 = _record->getIndividualDeathDate2(indi);

            str += this->exportDate(2, datetype, date1, date2);

            QString plac = _record->getIndividualDeathPlaceName(indi);
            if(! plac.isEmpty())
            {
                str += "2 PLAC " + plac + "\n";
            }

            QString caus = _record->getIndividualDeathCause(indi);
            if(! caus.isEmpty())
            {
                str += "2 CAUS " + caus + "\n";
            }

            Identifier src = _record->getIndividualDeathSourceRef(indi);
            QString page = _record->getIndividualDeathSourceCitationPage(indi);
            QString url = _record->getIndividualDeathSourceCitationUrl(indi);

            str += this->exportSourceCitation(2, src, page, url);
        }

        // BURI
        if(_record->isIndividualBuried(indi))
        {
            str += "1 " + this->eventToString(CommonEventType::BURI) + "\n";

            DateType datetype = _record->getIndividualBurialDateType(indi);
            Date date1 = _record->getIndividualBurialDate1(indi);
            Date date2 = _record->getIndividualBurialDate2(indi);

            str += this->exportDate(2, datetype, date1, date2);

            QString plac = _record->getIndividualBurialPlaceName(indi);
            if(! plac.isEmpty())
            {
                str += "2 PLAC " + plac + "\n";
            }

            Identifier priest = _record->getIndividualBurialPriest(indi);
            str += this->exportPriest(2, priest);
        }

        // OCCU
        for (unsigned int i = 0; i < _record->getIndividualOccuCount(indi); i++)
        {
            QString descr = _record->getIndividualOccuDescription(indi, i);
            str += "1 " + this->eventToString(CommonEventType::OCCU) + " " + descr + "\n";

            DateType datetype = _record->getIndividualOccuDateType(indi, i);
            Date date1 = _record->getIndividualOccuDate1(indi, i);
            Date date2 = _record->getIndividualOccuDate2(indi, i);

            str += this->exportDate(2, datetype, date1, date2);
        }

        // EDUC
        for (unsigned int i = 0; i < _record->getIndividualEducCount(indi); i++)
        {
            QString descr = _record->getIndividualEducDescription(indi, i);
            str += "1 " + this->eventToString(CommonEventType::EDUC) + " " + descr + "\n";

            DateType datetype = _record->getIndividualEducDateType(indi, i);
            Date date1 = _record->getIndividualEducDate1(indi, i);
            Date date2 = _record->getIndividualEducDate2(indi, i);

            str += this->exportDate(2, datetype, date1, date2);
        }

        // RELI
        for (unsigned int i = 0; i < _record->getIndividualReliCount(indi); i++)
        {
            QString descr = _record->getIndividualReliDescription(indi, i);
            str += "1 " + this->eventToString(CommonEventType::RELI) + " " + descr + "\n";

            DateType datetype = _record->getIndividualReliDateType(indi, i);
            Date date1 = _record->getIndividualReliDate1(indi, i);
            Date date2 = _record->getIndividualReliDate2(indi, i);

            str += this->exportDate(2, datetype, date1, date2);
        }

        // RESI
        for (unsigned int i = 0; i < _record->getIndividualResiCount(indi); i++)
        {
            str += "1 " + this->eventToString(CommonEventType::RESI) + "\n";

            DateType datetype = _record->getIndividualResiDateType(indi, i);
            Date date1 = _record->getIndividualResiDate1(indi, i);
            Date date2 = _record->getIndividualResiDate2(indi, i);

            str += this->exportDate(2, datetype, date1, date2);

            QString addr = _record->getIndividualResiAddrAddr(indi, i);
            QString city = _record->getIndividualResiAddrCity(indi, i);

            str += this->exportAddress(2, addr, city);
        }

        // NOTE
        auto note = _record->getIndividualNote(indi);
        if(!note.isEmpty())
        {
            QStringList noteList = note.split("\n");
            for(auto noteLine = noteList.begin(); noteLine != noteList.end(); noteLine++)
            {
                str += "1 NOTE " + this->createContStructure(*noteLine, 2);
            }
        }
    }
    return str;
}

// Probably all done
QString ExporterGedcom::exportFamily(Identifier fam)
{
    QString str;
    if(_record->isFamily(fam))
    {
        str = "0 @" + fam.get() + "@ FAM\n";
    }
    Identifier husb = _record->getFamilyHusband(fam);
    Identifier wife = _record->getFamilyWife(fam);
    QVector<Identifier> children = _record->getFamilyChildren(fam);

    if(_record->isIndividual(husb))
        str += "1 HUSB @" + husb.get() + "@\n";
    if(_record->isIndividual(wife))
        str += "1 WIFE @" + wife.get() + "@\n";
    for(auto it = children.cbegin(); it != children.cend(); it++)
    {
        if(_record->isIndividual(*it))
            str += "1 CHIL @" + it->get() + "@\n";
    }

    // MARR
    if(_record->isFamilyMarried(fam))
    {
        str += "1 " + this->eventToString(CommonEventType::MARR) + "\n";
        DateType datetype = _record->getFamilyMarriageDateType(fam);
        Date date1 = _record->getFamilyMarriageDate1(fam);
        Date date2 = _record->getFamilyMarriageDate2(fam);

        str += this->exportDate(2, datetype, date1, date2);

        QString place = _record->getFamilyMarriagePlaceName(fam);
        if(! place.isEmpty())
        {
            str += "2 PLAC " + place + "\n";
        }

        Identifier priest = _record->getFamilyMarriagePriest(fam);
        Identifier witness1 = _record->getFamilyMarriageWitness1(fam);
        Identifier witness2 = _record->getFamilyMarriageWitness2(fam);
        str += this->exportPriest(2, priest);
        str += this->exportWitness1(2, witness1);
        str += this->exportWitness2(2, witness2);

        Identifier src = _record->getFamilyMarriageSourceRef(fam);
        QString page = _record->getFamilyMarriageSourceCitationPage(fam);
        QString url = _record->getFamilyMarriageSourceCitationUrl(fam);

        str += this->exportSourceCitation(2, src, page, url);
    }

    // DIV
    if(_record->isFamilyDivorced(fam))
    {
        str += "1 " + this->eventToString(CommonEventType::DIV) + "\n";

        DateType datetype = _record->getFamilyDivorceDateType(fam);
        Date date1 = _record->getFamilyDivorceDate1(fam);
        Date date2 = _record->getFamilyDivorceDate2(fam);

        str += this->exportDate(2, datetype, date1, date2);
    }
    return str;
}

QString ExporterGedcom::exportSubmitter(Identifier subm)
{
    QString str;
    if(_record->isSubmitter(subm))
    {
        str =   "0 @" + subm.get() + "@ SUBM\n"
                "1 NAME " + _record->getSubmitterName(subm).left(60) + "\n"                ;
        if(! _record->isSubmitterEmpty(subm))
        {
            if(! _record->getSubmitterLang(subm).isEmpty())
            {
                str += "1 LANG " + _record->getSubmitterLang(subm) + "\n";
            }
            if(! _record->getSubmitterNote(subm).isEmpty())
            {
                str += "1 NOTE " + this->createContStructure(_record->getSubmitterNote(subm),2);
            }
            // Change Date not supported
        }
    }

    return str;
}

QString ExporterGedcom::exportSource(Identifier src)
{
    QString str;
    if(_record->isSource(src))
    {
        str =   "0 @" + src.get() + "@ SOUR\n";
        if(! _record->getSourceTitle(src).isEmpty())
        {
            str += "1 TITL " + this->createContStructure(_record->getSourceTitle(src), 1);
        }
        if(! _record->getSourceArchive(src).isEmpty())
        {
            str += "1 AUTH " + this->createContStructure(_record->getSourceArchive(src), 2);
        }
        if(! _record->getSourceOriginator(src).isEmpty())
        {
            str += "1 PUBL " + this->createContStructure(_record->getSourceOriginator(src), 2);
        }
        if(! _record->getSourceUrl(src).isEmpty())
        {
            str += "1 _URL " + this->createContStructure(_record->getSourceUrl(src), 2);
        }

        bool wasDataWritten = false;
        const QVector<CommonEventType> types = {CommonEventType::BIRT, CommonEventType::MARR, CommonEventType::DEAT};
        for(auto t = types.cbegin(); t != types.cend(); t++)
        {
            for(unsigned int index = 0; index < _record->getSourceDataCount(src, *t); index++)
            {
                // If first run
                if(! wasDataWritten)
                {
                    str += "1 DATA\n";
                    wasDataWritten = true;
                }

                str += "2 EVEN " + this->eventToString(*t) + "\n";

                Date dateFrom = _record->getSourceDataDateFrom(src, *t, index);
                Date dateTo = _record->getSourceDataDateTo(src, *t, index);
                str += this->exportDate(3, DateType::PERIOD, dateFrom, dateTo);

                QString plac = _record->getSourceDataPlac(src, *t, index);
                if(! plac.isEmpty())
                {
                    str += "3 PLAC " + plac + "\n";
                }

                QString page1 = _record->getSourceDataPage1(src, *t, index);
                if(! page1.isEmpty())
                {
                    str += "3 _PAG1 " + page1 + "\n";
                }

                QString page2 = _record->getSourceDataPage2(src, *t, index);
                if(! page2.isEmpty())
                {
                    str += "3 _PAG2 " + page2 + "\n";
                }

                QString url = _record->getSourceDataUrl(src, *t, index);
                if(! url.isEmpty())
                {
                    str += "3 _URL " + url + "\n";
                }
            }
        }
    }
    return str;
}

bool ExporterGedcom::exportFile(QString filename, Record &record)
{
    _record = &record;
    this->_filename = filename;

    // Open file for writing
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    // Output file stream initialization
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out.setGenerateByteOrderMark(true);     // Assigns BOM (For editor recognizeable UTF-8)

    // Temporary string container
    QString str;

    // Export Header
    str = this->exportHeader();
    if(str.isEmpty())
    {
        return false;
    }
    else
    {
        out << str;
    }

    // Export Individuals
    for(Identifier it = _record->getIdentifierIndividualFirst(); it != _record->getIdentifierIndividualLast(); _record->getIdentifierIndividualNext(it))
    {
        str = this->exportIndividual(it);
        if(str.isEmpty())
        {
            return false;
        }
        else
        {
            out << str;
        }
    }

    // Export Families
    for(Identifier it = _record->getIdentifierFamilyFirst(); it != _record->getIdentifierFamilyLast(); _record->getIdentifierFamilyNext(it))
    {
        str = this->exportFamily(it);
        if(str.isEmpty())
        {
            return false;
        }
        else
        {
            out << str;
        }
    }

    // Export Submitters
    for(Identifier it = _record->getIdentifierSubmitterFirst(); it != _record->getIdentifierSubmitterLast(); _record->getIdentifierSubmitterNext(it))
    {
        str = this->exportSubmitter(it);
        if(str.isEmpty())
        {
            return false;
        }
        else
        {
            out << str;
        }
    }

    // Export Sources
    for(Identifier it = _record->getIdentifierSourceFirst(); it != _record->getIdentifierSourceLast(); _record->getIdentifierSourceNext(it))
    {
        str = this->exportSource(it);
        if(str.isEmpty())
        {
            return false;
        }
        else
        {
            out << str;
        }
    }

    // Add endig sequence
    out << "0 TRLR\n";

    file.close();

    // Export OK
    return true;
}
