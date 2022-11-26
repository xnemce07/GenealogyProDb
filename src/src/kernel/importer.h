/*!
 *  \file   importer.h
 *  \author Eva Navratilova
 */

#ifndef IMPORTER_H
#define IMPORTER_H

#include <QString>
#include "record.h"


enum class ImportType
{
    THIS_APP,
    OTHER_APP
};


/**
 * @brief
 *
 */
class Importer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     */
    Importer();
    /**
     * @brief
     *
     */
    virtual ~Importer();
    // not copyable
    /**
     * @brief
     *
     * @param
     */
    Importer(const Importer&) = delete;
    /**
     * @brief
     *
     * @param
     * @return Importer &operator
     */
    Importer& operator=(const Importer&) = delete;

    /**
     * @brief
     *
     * @param filename
     * @param record
     * @return bool
     */
    virtual bool importFile(QString filename, Record &record, ImportType &appType) = 0;

signals:
    void objectsToImport(int count);
    void objectImported();
};




#endif // IMPORTER_H
