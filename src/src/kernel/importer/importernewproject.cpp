/*!
 *  \file   importernewproject.cpp
 *  \author Eva Navratilova
 */

#include "importernewproject.h"

// Is this necessary? Maybe it would be ok to check if(!getHeadRefSubm.isValid()){add new Submitter}
bool ImporterNewProject::importFile(QString filename, Record &record, ImportType &appType)
{
    Q_UNUSED(filename);
    appType = ImportType::OTHER_APP;

    emit(this->objectsToImport(1));

    const Identifier subm = record.newSubmitter();
    record.setHeadRefSubm(subm);

    //record.newIndividual();

    emit(this->objectImported());

    return true;
}
