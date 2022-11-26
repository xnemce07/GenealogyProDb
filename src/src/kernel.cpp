/*!
 *  \file   kernel.cpp
 *  \author Eva Navratilova
 */

#include "kernel.h"

QString Kernel::_getFileExtension(QString filename)
{
    QString extension;
    QStringList namePieces = filename.split('.');
    if(namePieces.length() > 0)
    {
        extension = namePieces.last();
    }
    return extension.toLower();
}

void Kernel::_cleanupRecord()
{
    if(this->_record != nullptr)
    {
        delete this->_record;
        this->_record = nullptr;
    }
}

void Kernel::_cleanupImporter()
{
    if(this->_importer != nullptr)
    {
        delete this->_importer;
        this->_importer = nullptr;
    }
}

void Kernel::_cleanupExporter()
{
    if(this->_exporter != nullptr)
    {
        delete this->_exporter;
        this->_exporter = nullptr;
    }
}

Kernel::Kernel()
{
    this->_record = new RecordRAM();
}

Kernel::~Kernel()
{
    this->_cleanupRecord();
    this->_cleanupImporter();
    this->_cleanupExporter();
}


Record* Kernel::record()
{
    return this->_record;
}

bool Kernel::importFile(QString filename, bool &saveable)
{
    ImportType impType;
    bool retVal;
    QString extension = this->_getFileExtension(filename);

    saveable = false;

    if(filename.isEmpty())
    {
        _record->deleteDatabase();
        this->_importer = new ImporterNewProject();
    }
    else if(extension == "ged")
    {
        _record->deleteDatabase();
        this->_importer = new ImporterGedcom();
    }
    // else if(other extension types)
    else
    {
        // Not able to instantiate an importer for this extension
        emit(this->importDone());
        return false;
    }

    connect(_importer, &Importer::objectsToImport, this, &Kernel::objectsToImport);
    connect(_importer, &Importer::objectImported, this, &Kernel::objectImported);

    retVal = this->_importer->importFile(filename, *_record, impType);

    if(impType == ImportType::THIS_APP)
        saveable = true;

    // Cleanup of the importer
    this->_cleanupImporter();

    emit(this->importDone());
    return retVal;
}

bool Kernel::exportFile(QString filename)
{
    QString extension = this->_getFileExtension(filename);
    if(extension == "ged")
        this->_exporter = new ExporterGedcom();
    else
        return false;

    bool retVal = this->_exporter->exportFile(filename, *(this->_record));

    // Cleanup of the exporter
    this->_cleanupExporter();

    return retVal;
}

bool Kernel::newProject()
{
    bool saveable;
    return this->importFile(QString(), saveable);
}
