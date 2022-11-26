/*!
 *  \file   exportergedcom.h
 *  \author Eva Navratilova
 */

#ifndef EXPORTERGEDCOM_H
#define EXPORTERGEDCOM_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QTime>

#include "../exporter.h"
#include "../record/recordRAM/date.h"


/**
 * @brief
 *
 */
class ExporterGedcom : public Exporter
{
public:

private:
    Record *_record;
    QString _filename;

    QString genderToString(Gender g) const;
    QString dateToString(Date date) const;
    QString timeToString(QTime time) const;
    QString createContStructure(QString text, unsigned int levelOfCont);
    QString eventToString(const CommonEventType t) const;
    QString exportDate(int level, const DateType datetype, const Date date1, const Date date2);
    QString exportAddress(int level, const QString addr, const QString city);
    QString exportSourceCitation(int level, const Identifier src, const QString page, const QString url);
    QString exportPriest(int level, Identifier priest);
    QString exportWitness1(int level, Identifier wit);
    QString exportWitness2(int level, Identifier wit);

    QString exportHeader();
    QString exportIndividual(Identifier indi);
    QString exportFamily(Identifier fam);
    QString exportSubmitter(Identifier subm);
    QString exportSource(Identifier src);

 public:
    /**
     * @brief
     *
     */
    ExporterGedcom() = default;

    /**
     * @brief
     *
     */
    ~ExporterGedcom() = default;

    // not copyable
    /**
     * @brief
     *
     * @param
     */
    ExporterGedcom(const ExporterGedcom&) = delete;

    /**
     * @brief
     *
     * @param
     * @return GedcomExporter &operator
     */
    ExporterGedcom& operator=(ExporterGedcom&) = delete;

    /**
     * @brief
     *
     * @param filename
     * @param record
     * @return bool
     */
    bool exportFile(QString filename, Record &record);

};

#endif // EXPORTERGEDCOM_H
