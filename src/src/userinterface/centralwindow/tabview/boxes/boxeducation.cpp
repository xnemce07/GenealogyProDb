/*!
 *  \file   boxeducation.cpp
 *  \author Eva Navratilova
 */

#include "boxeducation.h"


BoxEducation::BoxEducation(Kernel &k, Identifier &p, QWidget *parent)
    :BoxEditableList (tr("Education"), k, p, parent)
{

}

void BoxEducation::update()
{
    this->remove();

    const unsigned int count = _kernel.record()->getIndividualEducCount(_proband);
    for(unsigned int i = 0; i < count; i++)
    {
        _list.addItem(TextFormatter::getEducationFullText(_kernel, _proband, i));
    }
}

void BoxEducation::swapIndexes(unsigned int index1, unsigned int index2)
{
    _kernel.record()->swapIndividualEduc(_proband, index1, index2);
}

void BoxEducation::clickAdd()
{
    QString description;
    DateType datetype = DateType::PERIOD;
    Date date1;
    Date date2;

    _dialogEdit = new DialogEditableDescription(tr("Add %1").arg(_title), description, datetype, date1, date2,
                                                _kernel.record()->getStringsEducation());
    int accepted = _dialogEdit->exec();

    if(accepted)
    {
        unsigned int index = _kernel.record()->setIndividualEduc(_proband);
        this->saveData(index, description, datetype, date1, date2);
        _list.addItem(TextFormatter::getEducationFullText(_kernel, _proband, index));
    }

    _dialogEdit->deleteLater();
}

void BoxEducation::clickEdit(unsigned int index)
{
    Q_UNUSED(index);

    QString description = _kernel.record()->getIndividualEducDescription(_proband, index);
    DateType datetype = _kernel.record()->getIndividualEducDateType(_proband, index);
    Date date1 = _kernel.record()->getIndividualEducDate1(_proband, index);
    Date date2 = _kernel.record()->getIndividualEducDate2(_proband, index);

    _dialogEdit = new DialogEditableDescription(tr("Edit %1").arg(_title), description, datetype, date1, date2,
                                                _kernel.record()->getStringsEducation());
    int accepted = _dialogEdit->exec();

    if(accepted)
    {
        this->saveData(index, description, datetype, date1, date2);
        _list.currentItem()->setText(TextFormatter::getEducationFullText(_kernel, _proband, index));
    }

    _dialogEdit->deleteLater();
}

void BoxEducation::clickDelete(unsigned int index)
{
    _kernel.record()->removeIndividualEduc(_proband, index);
}

void BoxEducation::saveData(const unsigned int index, QString &description, DateType &datetype, Date &date1, Date &date2)
{
    _kernel.record()->setIndividualEducDescription(_proband, index, description);
    _kernel.record()->setIndividualEducDateType(_proband, index, datetype);
    _kernel.record()->setIndividualEducDate1(_proband, index, date1);
    _kernel.record()->setIndividualEducDate2(_proband, index, date2);
}

