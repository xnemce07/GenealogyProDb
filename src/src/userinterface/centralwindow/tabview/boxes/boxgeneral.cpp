/*!
 *  \file   boxgeneral.cpp
 *  \author Eva Navratilova
 */

#include "boxgeneral.h"

BoxGeneral::BoxGeneral(QString title, Kernel &k, Identifier &p, QWidget *parent)
    : Box(title, BOX_NOT_CHECKABLE, k, p, parent)
{
    this->fill();

    connect(_subboxGeneralLeft, &SubboxGeneralLeft::changeNameGiven, this, &BoxGeneral::nameGivenChanged);
    connect(_subboxGeneralLeft, &SubboxGeneralLeft::changeNameMarname, this, &BoxGeneral::nameMarnameChanged);
    connect(_subboxGeneralLeft, &SubboxGeneralLeft::changeNameBirthname, this, &BoxGeneral::nameBirthnameChanged);
    connect(_subboxGeneralRight, &SubboxGeneralRight::changeGender, this, &BoxGeneral::genderChanged);
    connect(_subboxGeneralRight, &SubboxGeneralRight::changeNameTit1, this, &BoxGeneral::nameTit1Changed);
    connect(_subboxGeneralRight, &SubboxGeneralRight::changeNameTit2, this, &BoxGeneral::nameTit2Changed);
}

void BoxGeneral::update()
{
    Gender gender = _kernel.record()->getIndividualGender(_proband);

    QString givenName = _kernel.record()->getIndividualNameGiven(_proband);
    QString marName = _kernel.record()->getIndividualNameSurnameMarried(_proband);
    QString birthName = _kernel.record()->getIndividualNameSurnameBirth(_proband);
    QString tit1 = _kernel.record()->getIndividualNamePrefix(_proband);
    QString tit2 = _kernel.record()->getIndividualNameSuffix(_proband);

    QStringList names = _kernel.record()->getStringsGivenNames(gender);
    QStringList surnames = _kernel.record()->getStringsSurnames(gender);
    QStringList tit1s = _kernel.record()->getStringsPrefixes();
    QStringList tit2s = _kernel.record()->getStringsSuffixes();

    _subboxGeneralLeft->update(givenName, marName, birthName, names, surnames, surnames);
    _subboxGeneralRight->update(gender, tit1, tit2, tit1s, tit2s);

    // Set Name LineEdit to focus
    QTimer::singleShot(0, _subboxGeneralLeft, SLOT(setFocus()));
}

void BoxGeneral::fill()
{
    // Initialize
    _subboxGeneralLeft = new SubboxGeneralLeft();
    _subboxGeneralRight = new SubboxGeneralRight();

    // Set layout
    _layout.addWidget(_subboxGeneralLeft, 0, 0);
    _layout.addWidget(_subboxGeneralRight, 0, 1);

    // Adjust widgets
    _layout.setColumnStretch(0,10);
    _layout.setColumnStretch(1,1);
}

void BoxGeneral::genderChanged(int index)
{
    Gender newGender;
    Gender oldGender = _kernel.record()->getIndividualGender(_proband);

    (index >= 0 && index < 3) ? newGender = static_cast<Gender>(index) : newGender = Gender::UNDET;

    if(newGender == oldGender)
        return;

    auto fams = _kernel.record()->getFamiliesOfIndividualParent(_proband);

    if(fams.size() > 0)
    {
        newGender = oldGender;
        _subboxGeneralRight->setGenderIndex(newGender);

        MessageBox dialogSetGenderFailed(MessageBox::Icon::Information,
                                                tr("Unable to change gender"),
                                                tr("Unable to change gender of a person who "
                                                   "figures in a relationship or has children.\n"
                                                   "Please remove all relationships and children of the "
                                                   "person and try again."),
                                                MessageBox::StandardButton::Ok);
        dialogSetGenderFailed.exec();
    }
    else
    {
        _kernel.record()->setIndividualGender(_proband, newGender);
    }
}

void BoxGeneral::nameGivenChanged(const QString &str)
{
    _kernel.record()->setIndividualNameGiven(_proband, str);
    emit(this->dataChanged());
}

void BoxGeneral::nameMarnameChanged(const QString &str)
{
    _kernel.record()->setIndividualNameMarname(_proband, str);
    emit(this->dataChanged());
}

void BoxGeneral::nameBirthnameChanged(const QString &str)
{
    _kernel.record()->setIndividualNameSurname(_proband, str);
    emit(this->dataChanged());
}

void BoxGeneral::nameTit1Changed(const QString &str)
{
    _kernel.record()->setIndividualNamePrefix(_proband, str);
}

void BoxGeneral::nameTit2Changed(const QString &str)
{
    _kernel.record()->setIndividualNameSuffix(_proband, str);
}
