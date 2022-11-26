/*!
 *  \file   importernewproject.h
 *  \author Eva Navratilova
 */

#ifndef IMPORTERNEWPROJECT_H
#define IMPORTERNEWPROJECT_H

#include <QString>

#include "../importer.h"


class ImporterNewProject : public Importer
{
    Q_OBJECT
public:
    ImporterNewProject() = default;
    ~ImporterNewProject() = default;

    bool importFile(QString filename, Record &record, ImportType &appType);
};

#endif // IMPORTERNEWPROJECT_H
