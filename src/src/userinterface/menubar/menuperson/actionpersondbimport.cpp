/*!
 *  \file   actionpersondbimport.cpp
 *  \author Leopold Nemcek
 */

#include "actionpersondbimport.h"

ActionPersonDbImport::ActionPersonDbImport(Kernel &k, QWidget *parent)
    : Action (parent), _kernel(k)
{
    //connect(this, &ActionPersonAdd::triggered, this, &ActionPersonAdd::process);
    this->disable();
}

void ActionPersonDbImport::process()
{
    QSettings settings;
    _newPerson = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(_newPerson, settings.value("dataConstraints/autoDead").toBool());
    this->modifyPerson();
    emit(this->probandChanged(_newPerson));
}


void ActionPersonDbImport::modifyPerson()
{


    QString dbHostname = "localhost";
    QString dbName = "demos";
    QString dbUsername = "genealogy";
    QString dbPassword = "Genealogy49!";

//    bool ok = true;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    bool drvrAvailavle = db.isDriverAvailable("QMYSQL");
    db.setHostName(dbHostname);
    db.setDatabaseName(dbName);
    db.setUserName(dbUsername);
    db.setPassword(dbPassword);

    bool ok = db.open();

    QSqlError err;
    if(ok){
       _kernel.record()->setIndividualNameGiven(_newPerson, "Mark");
    } else {
        _kernel.record()->setIndividualNameGiven(_newPerson, "Fred");
        err = db.lastError();
    }
    bool valid = db.isValid();

    auto errortType = err.type();
    auto errortext = err.text();

    auto i = 5;
    return ;
}

void ActionPersonDbImport::translate()
{
    this->setText(tr("Import from database..."));
}
