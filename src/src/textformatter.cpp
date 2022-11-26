/*!
 *  \file   textformatter.cpp
 *  \author Eva Navratilova
 */

#include "textformatter.h"

const char* TextFormatter::_intro =
        // Translate - tr() analogy for static members
        QT_TR_NOOP("");

const char* TextFormatter::_sectionPerson =
        QT_TR_NOOP("Person:");

const char* TextFormatter::_dictionaryPerson [static_cast<int>(PersonVariables::MAX)][2] =
{
    // ID
    {"%id", QT_TR_NOOP("Identifier")},
    //NAME
    {"%name", QT_TR_NOOP("Given name")},
    //BIRN
    {"%bsurn", QT_TR_NOOP("Birth surname")},
    //MARN
    {"%msurn", QT_TR_NOOP("Married surname")},
    //BIRMARN
    {"%bmsurn", QT_TR_NOOP("Birth surname preferably, if it is not known married surname is used")},
    //MARBIRN
    {"%mbsurn", QT_TR_NOOP("Married surname preferably, if it is not known, birth surname is used")},
    //TIT1
    {"%tit1", QT_TR_NOOP("Title in front of the name")},
    //TIT2
    {"%tit2", QT_TR_NOOP("Title after the name with prepended comma")},

    //BDATE
    {"%bdate", QT_TR_NOOP("Date of birth")},
    //DDATE
    {"%ddate", QT_TR_NOOP("Date of death")},
    //BDDD
    {"%bd-dd", QT_TR_NOOP("Date of birth - Date of death")},
    //BYEAR
    {"%byear", QT_TR_NOOP("Year of birth")},
    //DYEAR
    {"%dyear", QT_TR_NOOP("Year of death")},
    //BYDY
    {"%by-dy", QT_TR_NOOP("Year of death")},
    //BPLACE
    {"%bplace", QT_TR_NOOP("Place of birth")},
    //DPLACE
    {"%dplace", QT_TR_NOOP("Place of death")},
    //DCAUSE
    {"%dcause", QT_TR_NOOP("Cause of death")},

    //AGE
    {"%age", QT_TR_NOOP("Age (current age for living, age at death otherwise)")},

    //RESI
    {"%resi", QT_TR_NOOP("Residence")},
    //OCCU
    {"%occu", QT_TR_NOOP("Occupation")}
};

const char* TextFormatter::_sectionMarriage =
        QT_TR_NOOP("Marriage:");

const char* TextFormatter::_dictionaryMarriage [static_cast<int>(MarriageVariables::MAX)][2] =
{
    // WDATE
    {"%wdate", QT_TR_NOOP("Wedding date")},
    //WPLACE
    {"%wplace", QT_TR_NOOP("Wedding place")}
};

const char* TextFormatter::_sectionSource =
        QT_TR_NOOP("Source:");

const char* TextFormatter::_dictionarySource [static_cast<int>(SourceVariables::MAX)][2] =
{
    //ARCHIVE
    {"%arch", QT_TR_NOOP("Archive")},
    //SIGNATURE
    {"%sign", QT_TR_NOOP("Signature")},
    //ORIGIN
    {"%orig", QT_TR_NOOP("Place of origin of the register")},
    //PLACE ONE
    {"%currplac", QT_TR_NOOP("Place related to current citation")},
    //DATA
    {"%data", QT_TR_NOOP("Which types of records are included in the register")},
    //DATES
    {"%from-to", QT_TR_NOOP("Time span of the register")}
};

const char* TextFormatter::_examples =
        QT_TR_NOOP("Examples:"
                   "");

const char* TextFormatter::_sectionHtml =
        QT_TR_NOOP("HTML formatting is supported:");

const char* TextFormatter::_dictionaryHtml [static_cast<int>(HtmlVariables::MAX)][2] =
{
    // <b>
    {"<b>*</b>", QT_TR_NOOP("The text * will be bold")},
    // <i>
    {"<i>*</i>", QT_TR_NOOP("The text * will be italic")},
    // <br>
    {"<br>", QT_TR_NOOP("New line")}
};

const char* TextFormatter::_divider = QT_TR_NOOP("--------------------------");

const char* TextFormatter::_unknown = QT_TR_NOOP("?");

TextFormatter::~TextFormatter()
{

}

QString TextFormatter::dictToString(const char *dict[])
{
    return (QString(dict[0]) + "\t" + tr(dict[1]));
}

QString TextFormatter::markUnknownIfEmpty(QString str)
{
    if(str.isEmpty())
    {
        str = tr(_unknown);
    }
    return str;
}

QString TextFormatter::attributeText(QString description, Date date1, Date date2)
{
    QString text = description;
    QString dateText = TextFormatter::dateToText(date1);
    if(!dateText.isEmpty())
    {
        text += " (" + dateText;
        dateText = TextFormatter::dateToText(date2);
        if(!dateText.isEmpty())
        {
            text += "-" + dateText;
        }
        text += ")";
    }
    return text;
}

QString TextFormatter::getPersonText(Kernel &k, Identifier indi, QString text)
{
    for(int i = 0; i < static_cast<int>(PersonVariables::MAX); i++)
    {
        QString currentExpr = _dictionaryPerson[i][0];
        QString toReplace;
        DateType datetype;
        Age age;
        Date date1, date2;
        QString strDate1, strDate2;
        QRegularExpressionMatch match = QRegularExpression(currentExpr).match(text);

        if(match.hasMatch())
        {
            switch(i)
            {
            case static_cast<int>(PersonVariables::ID):
                toReplace = QString::number(indi.getNumber());
                break;
            case static_cast<int>(PersonVariables::NAME):
                toReplace = markUnknownIfEmpty(k.record()->getIndividualNameGiven(indi));
                break;
            case static_cast<int>(PersonVariables::BIRN):
                toReplace = markUnknownIfEmpty(k.record()->getIndividualNameSurnameBirth(indi));
                break;
            case static_cast<int>(PersonVariables::MARN):
                toReplace = markUnknownIfEmpty(k.record()->getIndividualNameSurnameMarried(indi));
                break;
            case static_cast<int>(PersonVariables::BIRMARN):
                toReplace = markUnknownIfEmpty(k.record()->getIndividualNameSurnameBirthMarried(indi));
                break;
            case static_cast<int>(PersonVariables::MARBIRN):
                toReplace = markUnknownIfEmpty(k.record()->getIndividualNameSurnameMarriedBirth(indi));
                break;
            case static_cast<int>(PersonVariables::TIT1):
                toReplace = k.record()->getIndividualNamePrefix(indi);
                break;
            case static_cast<int>(PersonVariables::TIT2):
                toReplace = k.record()->getIndividualNameSuffix(indi);
                if(! toReplace.isEmpty())
                    toReplace = ", " + toReplace;
                break;

            case static_cast<int>(PersonVariables::BDATE):
                datetype = k.record()->getIndividualBirthDateType(indi);
                date1 = k.record()->getIndividualBirthDate1(indi);
                date2 = k.record()->getIndividualBirthDate2(indi);
                toReplace = TextFormatter::dateStructureToText(datetype, date1, date2);
                break;
            case static_cast<int>(PersonVariables::DDATE):
                datetype = k.record()->getIndividualDeathDateType(indi);
                date1 = k.record()->getIndividualDeathDate1(indi);
                date2 = k.record()->getIndividualDeathDate2(indi);
                toReplace = TextFormatter::dateStructureToText(datetype, date1, date2);
                break;
            case static_cast<int>(PersonVariables::BDDD):
                datetype = k.record()->getIndividualBirthDateType(indi);
                date1 = k.record()->getIndividualBirthDate1(indi);
                date2 = k.record()->getIndividualBirthDate2(indi);
                strDate1 = TextFormatter::dateStructureToText(datetype, date1, date2);
                datetype = k.record()->getIndividualDeathDateType(indi);
                date1 = k.record()->getIndividualDeathDate1(indi);
                date2 = k.record()->getIndividualDeathDate2(indi);
                strDate2 = TextFormatter::dateStructureToText(datetype, date1, date2);
                datetype = (k.record()->isIndividualDeceased(indi))? DateType::PERIOD : DateType::SIMPLE;
                toReplace = TextFormatter::dateStructureToText(datetype, strDate1, strDate2);
                break;
            case static_cast<int>(PersonVariables::BYEAR):
                datetype = k.record()->getIndividualBirthDateType(indi);
                date1 = k.record()->getIndividualBirthDate1(indi);
                date1 = Date(date1.year());
                date2 = k.record()->getIndividualBirthDate2(indi);
                date2 = Date(date2.year());
                toReplace = TextFormatter::dateStructureToText(datetype, date1, date2);
                break;
            case static_cast<int>(PersonVariables::DYEAR):
                datetype = k.record()->getIndividualDeathDateType(indi);
                date1 = k.record()->getIndividualDeathDate1(indi);
                date1 = Date(date1.year());
                date2 = k.record()->getIndividualDeathDate2(indi);
                date2 = Date(date2.year());
                toReplace = TextFormatter::dateStructureToText(datetype, date1, date2);
                break;
            case static_cast<int>(PersonVariables::BYDY):
                datetype = k.record()->getIndividualBirthDateType(indi);
                date1 = k.record()->getIndividualBirthDate1(indi);
                date1 = Date(date1.year());
                date2 = k.record()->getIndividualBirthDate2(indi);
                date2 = Date(date2.year());
                strDate1 = TextFormatter::dateStructureToText(datetype, date1, date2);
                datetype = k.record()->getIndividualDeathDateType(indi);
                date1 = k.record()->getIndividualDeathDate1(indi);
                date1 = Date(date1.year());
                date2 = k.record()->getIndividualDeathDate2(indi);
                date2 = Date(date2.year());
                strDate2 = TextFormatter::dateStructureToText(datetype, date1, date2);
                datetype = (k.record()->isIndividualDeceased(indi))? DateType::PERIOD : DateType::SIMPLE;
                toReplace = TextFormatter::dateStructureToText(datetype, strDate1, strDate2);
                break;
            case static_cast<int>(PersonVariables::BPLACE):
                toReplace = k.record()->getIndividualBirthPlaceName(indi);
                break;
            case static_cast<int>(PersonVariables::DPLACE):
                toReplace = k.record()->getIndividualDeathPlaceName(indi);
                break;
            case static_cast<int>(PersonVariables::DCAUSE):
                toReplace = k.record()->getIndividualDeathCause(indi);
                break;

            case static_cast<int>(PersonVariables::AGE):
                age = k.record()->getIndividualAge(indi);
                if(age.isValid())
                {
                    toReplace = QString::number(age.years());
                }
                else
                {
                    toReplace = markUnknownIfEmpty(QString());
                }

                break;

            case static_cast<int>(PersonVariables::RESI):
                if(k.record()->getIndividualResiCount(indi) > 0)
                {
                    toReplace = TextFormatter::getResidenceShortText(k, indi, 0);
                }
                //toReplace = markUnknownIfEmpty(toReplace);
                break;
            case static_cast<int>(PersonVariables::OCCU):
                if(k.record()->getIndividualOccuCount(indi) > 0)
                {
                    toReplace = TextFormatter::getOccupationShortText(k, indi, 0);
                }
                //toReplace = markUnknownIfEmpty(toReplace);
                break;
            }
        }
        text.replace(currentExpr, toReplace);
    }
    return text.simplified();   // Remove leading, trailing and multi whitespaces
}

QString TextFormatter::getPersonLineText(Kernel &k, Identifier indi)
{
    if(! k.record()->isIndividual(indi))
    {
        return "+";
    }

    QSettings settings;
    QString text = settings.value("textformat/person").toString();

    return TextFormatter::getPersonText(k, indi, text);
}

QString TextFormatter::getPersonTreeText(Kernel &k, Identifier indi)
{
    if(! k.record()->isIndividual(indi))
    {
        return TextFormatter::markUnknownIfEmpty(QString());
    }

    QSettings settings;
    QString text = settings.value("textformat/tree/person").toString();

    QString value = TextFormatter::getPersonText(k, indi, text);
    return value;
}

QString TextFormatter::getOccupationFullText(Kernel &k, Identifier indi, unsigned int index)
{
    QString description = k.record()->getIndividualOccuDescription(indi, index);
    Date date1 = k.record()->getIndividualOccuDate1(indi, index);
    Date date2 = k.record()->getIndividualOccuDate2(indi, index);
    return TextFormatter::attributeText(description, date1, date2);
}

QString TextFormatter::getEducationFullText(Kernel &k, Identifier indi, unsigned int index)
{
    QString description = k.record()->getIndividualEducDescription(indi, index);
    Date date1 = k.record()->getIndividualEducDate1(indi, index);
    Date date2 = k.record()->getIndividualEducDate2(indi, index);
    return TextFormatter::attributeText(description, date1, date2);
}

QString TextFormatter::getResidenceFullText(Kernel &k, Identifier indi, unsigned int index)
{
    QString description = k.record()->getIndividualResiAddrCity(indi, index);
    QString addr = k.record()->getIndividualResiAddrAddr(indi, index);
    if(description.isEmpty())
    {
        description = addr;
    }
    else
    {
        if(!addr.isEmpty())
        {
            description += " " + addr;
        }
    }
    Date date1 = k.record()->getIndividualResiDate1(indi, index);
    Date date2 = k.record()->getIndividualResiDate2(indi, index);
    return TextFormatter::attributeText(description, date1, date2);
}

QString TextFormatter::getReligionFullText(Kernel &k, Identifier indi, unsigned int index)
{
    QString description = k.record()->getIndividualReliDescription(indi, index);
    Date date1 = k.record()->getIndividualReliDate1(indi, index);
    Date date2 = k.record()->getIndividualReliDate2(indi, index);
    return TextFormatter::attributeText(description, date1, date2);
}

QString TextFormatter::getOccupationShortText(Kernel &k, Identifier indi, unsigned int index)
{
    QString description = k.record()->getIndividualOccuDescription(indi, index);
    return TextFormatter::attributeText(description);
}

QString TextFormatter::getEducationShortText(Kernel &k, Identifier indi, unsigned int index)
{
    QString description = k.record()->getIndividualEducDescription(indi, index);
    return TextFormatter::attributeText(description);
}

QString TextFormatter::getResidenceShortText(Kernel &k, Identifier indi, unsigned int index)
{
    QString description = k.record()->getIndividualResiAddrCity(indi, index);
    QString addr = k.record()->getIndividualResiAddrAddr(indi, index);
    if(description.isEmpty())
    {
        description = addr;
    }
    else
    {
        if(!addr.isEmpty())
        {
            description += " " + addr;
        }
    }
    return TextFormatter::attributeText(description);
}

QString TextFormatter::getReligionShortText(Kernel &k, Identifier indi, unsigned int index)
{
    QString description = k.record()->getIndividualReliDescription(indi, index);
    Date date1, date2;
    return TextFormatter::attributeText(description, date1, date2);
}

QString TextFormatter::getMarriageTreeText(Kernel &k, Identifier fam)
{
    if((! k.record()->isFamily(fam)) || (!k.record()->isFamilyMarried(fam)))
    {
        return QString();
    }

    QSettings settings;
    QString text = settings.value("textformat/tree/marriage").toString();

    for(int i = 0; i < static_cast<int>(MarriageVariables::MAX); i++)
    {
        QString currentExpr = _dictionaryMarriage[i][0];
        QString toReplace;
        DateType datetype;
        Date date1, date2;
        QRegularExpressionMatch match = QRegularExpression(currentExpr).match(text);

        if(match.hasMatch())
        {
            switch(i)
            {
            case static_cast<int>(MarriageVariables::WDATE):
                datetype = k.record()->getFamilyMarriageDateType(fam);
                date1 = k.record()->getFamilyMarriageDate1(fam);
                date2 = k.record()->getFamilyMarriageDate2(fam);
                toReplace = TextFormatter::dateStructureToText(datetype, date1, date2);
                break;
            case static_cast<int>(MarriageVariables::WPLACE):
                toReplace = k.record()->getFamilyMarriagePlaceName(fam);
                break;
            }
        }
        text.replace(currentExpr, toReplace);
    }
    return text.simplified();   // Remove leading, trailing and multi whitespaces
}

QString TextFormatter::getCitationText(Kernel &k, Identifier source, CommonEventType t, QString place)
{
    QSettings settings;
    QString text = settings.value("textformat/citation").toString();

    if(! k.record()->isSource(source))
    {
        return QString();
    }

    for(int i = 0; i < toUnderlying(SourceVariables::MAX); i++)
    {
        QString currentExpr = _dictionarySource[i][0];
        QString toReplace;
        QRegularExpressionMatch match = QRegularExpression(currentExpr).match(text);

        if(match.hasMatch())
        {
            Date date1;
            Date date2;

            QStringList data;
            QString tempPlace, strPlace, strDate1, strDate2;
            auto types = k.record()->getSourceData(source);

            for(unsigned int index = 0; index < k.record()->getSourceDataCount(source, t); index++)
            {
                tempPlace = k.record()->getSourceDataPlac(source, t, index);
                if(tempPlace == place)
                {
                    strPlace = tempPlace;
                    date1 = k.record()->getSourceDataDateFrom(source, t, index);
                    date2 = k.record()->getSourceDataDateTo(source, t, index);
                    break;
                }

            }
            if(! strPlace.isEmpty())
            {
                strDate1 = (date1.isValid())? QString::number(date1.year()) : tr(_unknown);
                strDate2 = (date2.isValid())? QString::number(date2.year()) : tr(_unknown);
            }

            switch(i)
            {
            case toUnderlying(SourceVariables::ARCHIVE):
                toReplace = markUnknownIfEmpty(k.record()->getSourceArchive(source));
                break;
            case toUnderlying(SourceVariables::SIGNATURE):
                toReplace = markUnknownIfEmpty(k.record()->getSourceTitle(source));
                break;
            case toUnderlying(SourceVariables::ORIGIN):
                toReplace = markUnknownIfEmpty(k.record()->getSourceOriginator(source));
                break;
            case toUnderlying(SourceVariables::CURRPLAC):
                toReplace = markUnknownIfEmpty(place);
                break;
            case toUnderlying(SourceVariables::DATA):
                for(auto t = types.cbegin(); t < types.cend(); t++)
                {
                    if(k.record()->getSourceDataCount(source, *t) > 0)
                    {
                        data.push_back(TextFormatter::getSourceTypeText(*t));
                    }
                }
                toReplace = data.join(',');
                if(toReplace.isEmpty())
                {
                    toReplace = TextFormatter::getSourceTypeText(CommonEventType::EMPT);
                }
                break;
            case toUnderlying(SourceVariables::FROMTO):
                if(!(strDate1.isEmpty() || strDate2.isEmpty()))
                {
                    toReplace = strDate1 + "-" + strDate2;
                }
                else
                {
                    toReplace = tr(_unknown);
                }
                break;
            }
        }
        text.replace(currentExpr, toReplace);
    }
    return text.simplified();   // Remove leading, trailing and multi whitespaces

}

QString TextFormatter::getCitationTextPreview(Kernel &k, Identifier source)
{
    CommonEventType t = CommonEventType::EMPT;
    QString plac;

    auto data = k.record()->getSourceData(source);
    for (auto one : data)
    {
        auto index = k.record()->getSourceDataCount(source, one);
        if(index > 0)
        {
            t = one;
            plac = k.record()->getSourceDataPlac(source, one, 0);
            break;
        }
    }

    if(t != CommonEventType::EMPT)
    {
        return TextFormatter::getCitationText(k, source, t, plac);
    }
    else
    {
        return QString();
    }
}

QString TextFormatter::getSourceText(Kernel &k, Identifier source)
{
    if(!k.record()->isSource(source))
    {
        return QString();
    }

    QSettings settings;
    QString text = settings.value("textformat/source").toString();

    for(int i = 0; i < toUnderlying(SourceVariables::MAX); i++)
    {
        QString currentExpr = _dictionarySource[i][0];
        QString toReplace;
        QRegularExpressionMatch match = QRegularExpression(currentExpr).match(text);

        if(match.hasMatch())
        {
            Date date1 = k.record()->getSourceCommonDateFrom(source);
            Date date2 = k.record()->getSourceCommonDateTo(source);

            QString strDate1 = QString::number(date1.year());
            QString strDate2 = QString::number(date2.year());

            QVector<CommonEventType> types = k.record()->getSourceData(source);
            QStringList data;

            switch(i)
            {
            case toUnderlying(SourceVariables::ARCHIVE):
                toReplace = markUnknownIfEmpty(k.record()->getSourceArchive(source));
                break;
            case toUnderlying(SourceVariables::SIGNATURE):
                toReplace = markUnknownIfEmpty(k.record()->getSourceTitle(source));
                break;
            case toUnderlying(SourceVariables::ORIGIN):
            case toUnderlying(SourceVariables::CURRPLAC):
                toReplace = markUnknownIfEmpty(k.record()->getSourceOriginator(source));
                break;
            case toUnderlying(SourceVariables::DATA):
                for(auto t = types.cbegin(); t < types.cend(); t++)
                {
                    if(k.record()->getSourceDataCount(source, *t) > 0)
                    {
                        data.push_back(TextFormatter::getSourceTypeText(*t));
                    }
                }
                toReplace = data.join(',');
                if(toReplace.isEmpty())
                {
                    toReplace = TextFormatter::getSourceTypeText(CommonEventType::EMPT);
                }
                break;
            case toUnderlying(SourceVariables::FROMTO):
                if(!(strDate1.isEmpty() || strDate2.isEmpty()))
                {
                    toReplace = strDate1 + "-" + strDate2;
                }
                else
                {
                    toReplace = tr(_unknown);
                }
                break;
            }
        }
        text.replace(currentExpr, toReplace);
    }
    return text.simplified();   // Remove leading, trailing and multi whitespaces

}

QString TextFormatter::getSourceTypeText(const CommonEventType t)
{
    switch (t) {
    case CommonEventType::BIRT:
        return tr("B");
    case CommonEventType::MARR:
        return tr("M");
    case CommonEventType::DEAT:
        return tr("D");
    default:
        return tr("X");
    }
}

QString TextFormatter::dateStructureToText(const DateType &datetype, const QString &date1, const QString &date2)
{
    QString result;
    switch (datetype)
    {
    case DateType::SIMPLE:
        result = date1;
        break;
    case DateType::ESTIMATED:
        result = tr("cca %1").arg(date1);
        break;
    case DateType::BEFORE:
        result = tr("before %1").arg(date1);
        break;
    case DateType::AFTER:
        result = tr("after %1").arg(date1);
        break;
    case DateType::BETWEEN:
        if(date1 == date2)
        {
            result = date1;
        }
        else
        {
            result = tr("between %1 and %2").arg(date1).arg(date2);
        }
        break;
    case DateType::PERIOD:
        result = tr("%1-%2").arg(date1).arg(date2);
        break;
    default:
        result = "?";
        break;
    }
    return result;
}

QString TextFormatter::dateStructureToText(const DateType &datetype, const Date &date1, const Date &date2)
{

    QString result, strDate1, strDate2;
    strDate1 = TextFormatter::dateToText(date1);
    strDate2 = TextFormatter::dateToText(date2);
    result = TextFormatter::dateStructureToText(datetype, strDate1, strDate2);
    return result;
}

QString TextFormatter::dateToText(const Date date)
{
    if(date.isNull())
        return QString();

    QSettings settings;
    QLocale locale = settings.value("textformat/locale").toLocale();
    QString format;
    if(date.datePrecision() == DatePrecision::FULL)
    {
        format = settings.value("textformat/dateFull").toString();
    }
    else if(date.datePrecision() == DatePrecision::YEAR)
    {
        format = settings.value("textformat/dateWM").toString();
    }
    else if(date.datePrecision() == DatePrecision::YEAR_MONTH)
    {
        format = settings.value("textformat/dateWD").toString();
    }
    QString dateStr = date.toString(format);
    return dateStr;
}

Date TextFormatter::dateFromText(QString date)
{
    QSettings settings;

    QString formatFull = settings.value("textformat/dateFull").toString();
    QString formatYM = settings.value("textformat/dateWD").toString();
    QString formatY = settings.value("textformat/dateWM").toString();

    return Date::fromString(date, formatFull, formatYM, formatY);
}

void TextFormatter::defaultSettings(FormatableText f)
{
    bool setDefaultIndi, setDefaultTreeIndi, setDefaultTreeMarriage, setDefaultSource, setDefaultCitation;
    setDefaultIndi = setDefaultTreeIndi = setDefaultTreeMarriage = setDefaultSource = setDefaultCitation = false;

    switch(f)
    {
    case FormatableText::INDIVIDUAL:
        setDefaultIndi = true;
        break;
    case FormatableText::TREE_INDIVIDUAL:
        setDefaultTreeIndi = true;
        break;
    case FormatableText::TREE_MARRIAGE:
        setDefaultTreeMarriage = true;
        break;
    case FormatableText::SOURCE:
        setDefaultSource = true;
        break;
    case FormatableText::SOURCE_CITATION:
        setDefaultCitation = true;
        break;
    case FormatableText::EMPTY:
        setDefaultIndi = setDefaultTreeIndi = setDefaultTreeMarriage = setDefaultSource = setDefaultCitation
                = true;
        break;
    }

    QSettings settings;

    // INITIALIZE VALUES
    // Person
    QString id   = _dictionaryPerson[toUnderlying(PersonVariables::ID)][0];
    QString name = _dictionaryPerson[toUnderlying(PersonVariables::NAME)][0];
    QString surn = _dictionaryPerson[toUnderlying(PersonVariables::BIRMARN)][0];
    QString tit1 = _dictionaryPerson[toUnderlying(PersonVariables::TIT1)][0];
    QString tit2 = _dictionaryPerson[toUnderlying(PersonVariables::TIT2)][0];
    QString bydy = _dictionaryPerson[toUnderlying(PersonVariables::BYDY)][0];
    QString bddd = _dictionaryPerson[toUnderlying(PersonVariables::BDDD)][0];
    QString age = _dictionaryPerson[toUnderlying(PersonVariables::AGE)][0];
    QString dcause = _dictionaryPerson[toUnderlying(PersonVariables::DCAUSE)][0];
    QString resi = _dictionaryPerson[toUnderlying(PersonVariables::RESI)][0];
    QString occu = _dictionaryPerson[toUnderlying(PersonVariables::OCCU)][0];

    // Marriage
    QString wdate = _dictionaryMarriage[toUnderlying(MarriageVariables::WDATE)][0];
    QString wplac = _dictionaryMarriage[toUnderlying(MarriageVariables::WPLACE)][0];

    // Source
    QString srcData = _dictionarySource[toUnderlying(SourceVariables::DATA)][0];
    QString srcSign = _dictionarySource[toUnderlying(SourceVariables::SIGNATURE)][0];
    QString srcOrig = _dictionarySource[toUnderlying(SourceVariables::ORIGIN)][0];
    QString srcFromTo = _dictionarySource[toUnderlying(SourceVariables::FROMTO)][0];

    // SET SETTINGS VALUES
    // Person fields
    if(setDefaultIndi)
        settings.setValue(TextFormatter::getSettingsKey(FormatableText::INDIVIDUAL),  tr("(%1) %2 %3 %4%5 (%6) %7 %8").arg(id).arg(tit1).arg(name).arg(surn).arg(tit2).arg(bydy).arg(occu).arg(resi));

    if(setDefaultTreeIndi)
        settings.setValue(TextFormatter::getSettingsKey(FormatableText::TREE_INDIVIDUAL), tr("<b>%1 %2 %3%4</b> (%5)<br>%6 (%7)<br>%8 %9").arg(tit1).arg(name).arg(surn).arg(tit2).arg(age).arg(bddd).arg(dcause).arg(occu).arg(resi));

    // Marriage field
    if(setDefaultTreeMarriage)
        settings.setValue(TextFormatter::getSettingsKey(FormatableText::TREE_MARRIAGE), tr("%1 %2").arg(wdate).arg(wplac));

    // Source field (for citations)
    if(setDefaultCitation)
        settings.setValue(TextFormatter::getSettingsKey(FormatableText::SOURCE_CITATION),  tr("%1: %2 %3").arg(srcData).arg(srcFromTo).arg(srcOrig));

    // Source field (for source lookup)
    if(setDefaultSource)
        settings.setValue(TextFormatter::getSettingsKey(FormatableText::SOURCE),  tr("%1: %2 %3 (%4)").arg(srcData).arg(srcSign).arg(srcOrig).arg(srcFromTo));
    /// TODO - is the text locale really necessary???
    // Text locale
    //settings.setValue("textformat/locale", QLocale(QLocale::English));
    // Date format
    /// TODO - format taken from Date documentation, write doc & settings ui for users!!!
    /// TODO - yyyy does not work for 3-digit and other years (for example year 851 does not work!!!)
    settings.setValue("textformat/dateFull", "d.M.yyyy");   // Full date        1.1.1900
    settings.setValue("textformat/dateWD", "M.yyyy");       // Without day      1.1900
    settings.setValue("textformat/dateWM", "yyyy");         // Without month    1900
}

void TextFormatter::saveSettings()
{

}

QString TextFormatter::getSettingsKey(FormatableText f)
{
    switch(f)
    {
    case FormatableText::INDIVIDUAL:
        return "textformat/person";
    case FormatableText::TREE_INDIVIDUAL:
        return "textformat/tree/person";
    case FormatableText::TREE_MARRIAGE:
        return "textformat/tree/marriage";
    case FormatableText::SOURCE:
        return "textformat/source";
    case FormatableText::SOURCE_CITATION:
        return "textformat/citation";
    case FormatableText::EMPTY:
        break;
    }
    return QString();
}

QString TextFormatter::getHtmlString(FormatableText f)
{
    QString str;
    if(f == FormatableText::TREE_INDIVIDUAL ||
       f == FormatableText::TREE_MARRIAGE)
    {
        for (auto i = 0; i<static_cast<int>(HtmlVariables::MAX); i++)
        {
            str += dictToString(_dictionaryHtml[i]) + "\n";
        }
        str += "\n";
    }
    return str;
}

QString TextFormatter::getDictionaryString(FormatableText f)
{
    int max = 0;
    switch(f)
    {
    case FormatableText::INDIVIDUAL:
    case FormatableText::TREE_INDIVIDUAL:
        max = static_cast<int>(PersonVariables::MAX);
        break;
    case FormatableText::SOURCE:
    case FormatableText::SOURCE_CITATION:
        max = static_cast<int>(SourceVariables::MAX);
        break;
    case FormatableText::TREE_MARRIAGE:
        max = static_cast<int>(MarriageVariables::MAX);
        break;
    case FormatableText::EMPTY:
        break;
    }
    QString text;
    for(int i = 0; i < max; i++)
    {
        switch(f)
        {
        case FormatableText::INDIVIDUAL:
        case FormatableText::TREE_INDIVIDUAL:
            text += dictToString(_dictionaryPerson[i]) + "\n";
            break;
        case FormatableText::SOURCE:
        case FormatableText::SOURCE_CITATION:
            text += dictToString(_dictionarySource[i]) + "\n";
            break;
        case FormatableText::TREE_MARRIAGE:
            text += dictToString(_dictionaryMarriage[i]) + "\n";
            break;
        case FormatableText::EMPTY:
            break;
        }
    }
    return text;
}

std::function<QString (Kernel &, Identifier)> TextFormatter::getTextGetter(FormatableText f)
{
    std::function<QString (Kernel &, Identifier)> fun;

    switch(f)
    {
    case FormatableText::INDIVIDUAL:
        fun = &TextFormatter::getPersonLineText;
        break;
    case FormatableText::TREE_INDIVIDUAL:
        fun = &TextFormatter::getPersonTreeText;
        break;
    case FormatableText::SOURCE:
        fun = &TextFormatter::getSourceText;
        break;
    case FormatableText::SOURCE_CITATION:
        fun = &TextFormatter::getCitationTextPreview;
        break;
    case FormatableText::TREE_MARRIAGE:
        fun = &TextFormatter::getMarriageTreeText;
        break;
    case FormatableText::EMPTY:
        break;
    }

    return fun;
}

QString TextFormatter::help()
{
    QString help;

    help  = tr(_intro) + "\n\n";
    help += tr(_divider) + "\n";
    help += tr(_sectionPerson) + "\n";
    help += tr(_divider) + "\n\n";
    help += getDictionaryString(FormatableText::INDIVIDUAL);
    help += "\n";
    help += tr(_divider) + "\n";
    help += tr(_sectionMarriage) + "\n";
    help += tr(_divider) + "\n\n";
    help += getDictionaryString(FormatableText::TREE_MARRIAGE);
    help += "\n";
    help += tr(_divider) + "\n";
    help += tr(_sectionSource) + "\n";
    help += tr(_divider) + "\n\n";
    help += getDictionaryString(FormatableText::SOURCE);
    help += "\n";
    help += tr(_examples) + "\n";

    return help;
}


