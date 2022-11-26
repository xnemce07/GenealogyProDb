/*!
 *  \file   textformatter.h
 *  \author Eva Navratilova
 */

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QSettings>
#include <QCoreApplication>
#include <QPair>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#define PERSON_VAR_COUNT 10
#define MARRIAGE_VAR_COUNT 2

#include "kernel.h"

enum class FormatableText{
    EMPTY,
    INDIVIDUAL,
    SOURCE,
    SOURCE_CITATION,
    TREE_INDIVIDUAL,
    TREE_MARRIAGE
};

enum class PersonVariables
{
    ID,

    NAME,
    BIRN,
    MARN,
    BIRMARN,
    MARBIRN,
    TIT1,
    TIT2,

    BDATE,
    DDATE,
    BDDD,
    BYEAR,
    DYEAR,
    BYDY,
    BPLACE,
    DPLACE,
    DCAUSE,

    AGE,

    RESI,
    OCCU,

    MAX
};

enum class MarriageVariables
{
    WDATE,
    WPLACE,

    MAX
};

enum class SourceVariables
{
    ARCHIVE,
    SIGNATURE,
    ORIGIN,
    CURRPLAC,
    DATA,
    FROMTO,

    MAX
};

enum class HtmlVariables {
    B,
    I,
    BR,

    MAX
};

/**
 * @brief Creates texts from Records
 *
 * Creates text strings from Records according
 * to the user preferences saved in QSettings
 *
 */
class TextFormatter : public QObject
{
    Q_OBJECT
private:
    static const char* _intro;
    static const char* _sectionPerson;
    static const char* _dictionaryPerson [static_cast<int>(PersonVariables::MAX)][2];
    static const char* _sectionMarriage;
    static const char* _dictionaryMarriage [static_cast<int>(MarriageVariables::MAX)][2];
    static const char* _sectionSource;
    static const char* _dictionarySource [static_cast<int>(SourceVariables::MAX)][2];
    static const char* _examples;

    static const char* _sectionHtml;
    static const char* _dictionaryHtml [static_cast<int>(HtmlVariables::MAX)][2];

    static const char* _divider;
    static const char* _unknown;

public:
    /**
     * @brief
     *
     */
    //RecordExtender(Kernel &k);

    /**
     * @brief
     *
     */
    ~TextFormatter();

    static QString getPersonText(Kernel &k, Identifier indi, QString text);
    static QString getPersonLineText(Kernel &k, Identifier indi);
    static QString getPersonTreeText(Kernel &k, Identifier indi);

    static QString getOccupationFullText(Kernel &k, Identifier indi, unsigned int index);
    static QString getEducationFullText(Kernel &k, Identifier indi, unsigned int index);
    static QString getResidenceFullText(Kernel &k, Identifier indi, unsigned int index);
    static QString getReligionFullText(Kernel &k, Identifier indi, unsigned int index);

    static QString getOccupationShortText(Kernel &k, Identifier indi, unsigned int index);
    static QString getEducationShortText(Kernel &k, Identifier indi, unsigned int index);
    static QString getResidenceShortText(Kernel &k, Identifier indi, unsigned int index);
    static QString getReligionShortText(Kernel &k, Identifier indi, unsigned int index);

    static QString getMarriageTreeText(Kernel &k, Identifier fam);

    static QString getCitationText(Kernel &k, Identifier source, CommonEventType t, QString place);
    static QString getCitationTextPreview(Kernel &k, Identifier source);
    static QString getSourceText(Kernel &k, Identifier source);
    static QString getSourceTypeText(const CommonEventType t);

    static QString dateStructureToText(const DateType &datetype, const QString &date1, const QString &date2);
    static QString dateStructureToText(const DateType &datetype, const Date &date1, const Date &date2);
    static QString dateToText(const Date date);
    static Date dateFromText(QString date);

    static void defaultSettings(FormatableText f = FormatableText::EMPTY);
    static void saveSettings();
    static QString getSettingsKey(FormatableText f);

    static QString getHtmlString(FormatableText f);
    static QString getDictionaryString(FormatableText f);

    static std::function<QString (Kernel &, Identifier)> getTextGetter(FormatableText f);

    static QString help();

private:
    TextFormatter() = delete;

    static QString dictToString(const char* dict[]);
    static QString markUnknownIfEmpty(QString str);

    static QString attributeText(QString description, Date date1 = Date(), Date date2 = Date());

};








#endif // USERINTERFACE_H
