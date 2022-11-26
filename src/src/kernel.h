/*!
 *  \file   kernel.h
 *  \author Eva Navratilova
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QStringList>

#include "kernel/record.h"
#include "kernel/importer.h"
#include "kernel/importer/importergedcom.h"
#include "kernel/importer/importernewproject.h"
#include "kernel/exporter.h"
#include "kernel/exporter/exportergedcom.h"
#include "kernel/record/recordram.h"
#include "kernel/record/recordRAM/identifier.h"


/**
 * @brief
 *
 */
class Kernel : public QObject
{
    Q_OBJECT
private:
    Record *_record = nullptr; /**< Saves all records about people and their relationships */
    Importer *_importer = nullptr; /**< Imports a file */
    Exporter *_exporter = nullptr; /**< Exports or saves a file */

    /**
     * @brief Returns a Lower Case extension of given filename
     *
     * @param filename  Name of the file to extract extension from
     * @return          Extension of given filename in Lower Case
     */
    QString _getFileExtension(QString filename);

    void _cleanupRecord();
    void _cleanupImporter();
    void _cleanupExporter();

public:
    /**
     * @brief Constructor of Kernel
     *
     */
    Kernel();

    /*static Kernel& getInstance(){
        static Kernel instance;
        return instance;
    }*/

    /**
     * @brief Kernel is not copyable - Copy constructors are deleted
     *
     */
    Kernel(Kernel const&) = delete;
    void operator=(Kernel const&) = delete;

    /**
     * @brief Destructor of Kernel
     *
     */
    virtual ~Kernel();

    /**
     * @brief
     *
     * @return Record
     */
    Record* record();

    /**
     * @brief Imports a file, using its extension to determine the right way of the import.
     *
     * @param filename  Name of the file to import with its extension (if string empty, new project created!)
     * @param saveable  Is the file saveable (eg. this file was previously generated from this program)
     * @return          True if the import was successful (false can indicate missing file, invalid extension, etc.)
     */
    bool importFile(QString filename, bool& saveable);
    bool exportFile(QString filename);

    bool newProject();

signals:
    void objectsToImport(int count);
    void objectImported();
    void importDone();

};




#endif // KERNEL_H
