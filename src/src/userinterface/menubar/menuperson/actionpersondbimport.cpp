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

    int id = 1;

    QString dbHostname = "localhost";
    QString dbName = "demos";
    QString dbUsername = "genealogy";
    QString dbPassword = "Genealogy49!";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(dbHostname);
    db.setDatabaseName(dbName);
    db.setUserName(dbUsername);
    db.setPassword(dbPassword);

    if(db.open()){
        QSqlQuery givenNameQuery;
        givenNameQuery.exec(QString("SELECT n.name, pn.name_order "
                           "FROM person p "
                           "LEFT JOIN person_name pn on p.id = pn.person_id "
                           "LEFT JOIN name n on n.id = pn.name_id "
                           "WHERE p.id = %1 "
                           "ORDER BY pn.name_order ASC").arg(id));
        QString givenName = "";
        while (givenNameQuery.next()) {
            givenName += givenNameQuery.value(0).toString();
        }
        _kernel.record()->setIndividualNameGiven(_newPerson,givenName);

        QSqlQuery surnameQuery;
        surnameQuery.exec(QString("SELECT s.name, nS.name, p.religion "
                                  "FROM person p "
                                  "LEFT JOIN surname s on p.sname = s.id "
                                  "LEFT JOIN normalizedSurname nS on s.norm_name_id = nS.id "
                                  "WHERE p.id = %1").arg(id));

        surnameQuery.next();
        if(surnameQuery.value(1).toString() != ""){
            _kernel.record()->setIndividualNameSurname(_newPerson,surnameQuery.value(1).toString());
        } else if(surnameQuery.value(0).toString() != ""){
            _kernel.record()->setIndividualNameSurname(_newPerson,surnameQuery.value(0).toString());
        }

        QSqlQuery deathQuery;
        deathQuery.exec(QString("SELECT b.death_place, b.dead_date, b.dead_time, b.burial_place, b.burial_date, b.comment, bDC.name, nDC.name "
                                "FROM person p "
                                "LEFT JOIN burial b on p.burial_id = b.id "
                                "LEFT JOIN burialDeathCause bDC on b.death_cause = bDC.id "
                                "LEFT JOIN normalizedDeathCause nDC on bDC.norm_name_id = nDC.id "
                                "WHERE p.id = %1").arg(id));
        deathQuery.next();
        if(deathQuery.value(0).toString() != ""){
            _kernel.record()->setIndividualDeathPlaceName(_newPerson,deathQuery.value(0).toString());
        }
        if(deathQuery.value(1).toString() != ""){
            _kernel.record()->setIndividualDeathDate1(_newPerson,QDate::fromString(deathQuery.value(1).toString(),"yyyy-MM-dd"));
        }
        if(deathQuery.value(3).toString() != ""){
            _kernel.record()->setIndividualBurialPlaceName(_newPerson,deathQuery.value(3).toString());
        }
        if(deathQuery.value(4).toString() != ""){
            _kernel.record()->setIndividualBurialDate1(_newPerson,QDate::fromString(deathQuery.value(4).toString(),"yyyy-MM-dd"));
        }
        if(deathQuery.value(7).toString() != ""){
            _kernel.record()->setIndividualDeathCause(_newPerson,deathQuery.value(7).toString());
        } else if(deathQuery.value(6).toString() != ""){
            _kernel.record()->setIndividualDeathCause(_newPerson,deathQuery.value(6).toString());
        }

        QSqlQuery birthQuery;
        birthQuery.exec( QString("SELECT b.birth_date, b.birth_time, b.baptism_date, b.baptism_time, b.sex "
                                 "FROM person p "
                                 "LEFT JOIN birth b on p.birth_id = b.id "
                                 "WHERE p.id = %1").arg(1));
        birthQuery.next();
        if(birthQuery.value(0).toString() != ""){
           _kernel.record()->setIndividualBirthDate1(_newPerson,QDate::fromString(birthQuery.value(0).toString(),"yyyy-MM-dd"));
        }
        if(birthQuery.value(2).toString() != ""){
            _kernel.record()->setIndividualChristeningDate1(_newPerson,QDate::fromString(birthQuery.value(2).toString()));
        }
        if(birthQuery.value(4).toString() == "M"){
            _kernel.record()->setIndividualGender(_newPerson,Gender::MALE);
        } else if(birthQuery.value(4).toString() == "F"){
            _kernel.record()->setIndividualGender(_newPerson,Gender::FEMALE);
        }


    }

    return ;
}

void ActionPersonDbImport::translate()
{
    this->setText(tr("Import from database..."));
}
