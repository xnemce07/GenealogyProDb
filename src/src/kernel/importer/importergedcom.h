/*!
 *  \file   importergedcom.h
 *  \author Eva Navratilova
 */

#ifndef GEDCOMIMPORTER_H
#define GEDCOMIMPORTER_H

#include <QString>
#include <QFileInfo>
#include <QTextStream>
#include <QTemporaryFile>
#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QThread>

#include "../importer.h"
#include "../record.h"
#include "../../3rd-party/cgGedcom/anselcodec.h"
#include "../../3rd-party/cgGedcom/cggedcom.h"
#include "../../3rd-party/cgGedcom/gedcomnode.h"
#include "../../3rd-party/cgGedcom/gedcomparser.h"

#define T_EMPT 0
#define T_INDI 1
#define T_ATTR 2
#define T_FAM  3


class ImporterGedcom : public Importer
{
    Q_OBJECT
private:
    Record *_record;
    QString _fileToImport;

    bool _fromAncestry;

    cg::AnselCodec *_pTextCodec;
    cg::GedcomParser _parser;

    QHash<QString, Identifier> _referenceDictionary;

    int _nodeCount;
    int _nodePercent = 0;
    int _nodeCountImported = 0;

    static const QRegularExpression _lineExpression;


    bool existsFile();

    //Date dateRfc(QString str) const;
    Date dateFromMatch(QString yearStr, QString monthStr, QString dayStr) const;
    //Date dateFromMatch(QString yearStr, QString monthStr, QString dayStr) const;

    Identifier individualFromXref(const QString xref, Gender g = Gender::UNDET) const;
    Identifier familyFromXref(const QString xref) const;
    Identifier submitterFromXref(const QString xref) const;
    Identifier sourceFromXref(QString xref) const;

    //bool getValueOfChildWithTag(const cg::GedcomNode *node, cg::GedcomParser::NodeList *subNodeList, const QString tag, QString &val) const;
    bool getDateStructure(const QString string, DateType &type, Date &date1, Date &date2) const;

    bool getAncestryDescriptionData(const cg::GedcomNode *structure, QString &description, DateType &datetype, Date &date1, Date &date2) const;
    bool getAncestryAddressData(const cg::GedcomNode *structure, QString &city, QString &addr, DateType &datetype, Date &date1, Date &date2) const;
    bool getAttributeStructureData(const cg::GedcomNode *structure, QString &description, DateType &datetype, Date &date1, Date &date2) const;
    bool getSourceCitationData(const cg::GedcomNode *structure, Identifier &ref, QString &page, QString &url) const;

    QString getNote(cg::GedcomNode* note) const;

    bool convertIdentifiers(QString &out);
    bool replaceIdentifier(const Identifier &ref, QString &oldRef, QStringList::iterator &line) const;
    bool replaceReferences(QStringList &lineList) const;

    bool importHead(cg::GedcomNode *head);
    bool importIndividual(cg::GedcomNode *indi);
    bool importIndividualBirth(cg::GedcomNode *indiStruct, Identifier indi);
    bool importIndividualChristening(cg::GedcomNode *indiStruct, Identifier indi);
    bool importIndividualDeath(cg::GedcomNode *indiStruct, Identifier indi);
    bool importIndividualBurial(cg::GedcomNode *indiStruct, Identifier indi);
    bool importIndividualOccupation(cg::GedcomNode *indiStruct, Identifier indi);
    bool importIndividualEducation(cg::GedcomNode *indiStruct, Identifier indi);
    bool importIndividualResidence(cg::GedcomNode *indiStruct, Identifier indi);
    bool importIndividualReligion(cg::GedcomNode *indiStruct, Identifier indi);
    bool importIndividualContact(cg::GedcomNode *indiStruct, Identifier indi);

    bool importFamily(cg::GedcomNode *fam);
    bool importFamilyMarriage(cg::GedcomNode *famStruct, Identifier fam);
    bool importFamilyDivorce(cg::GedcomNode *famStruct, Identifier fam);
    bool importSubmitter(cg::GedcomNode *subm);
    bool importSource(cg::GedcomNode *src);

    void notifyNodeImported();


public:
    ImporterGedcom();
    ~ImporterGedcom() = default;

    bool importFile(QString filename, Record &record, ImportType &appType);


};

#endif // GEDCOMIMPORTER_H
