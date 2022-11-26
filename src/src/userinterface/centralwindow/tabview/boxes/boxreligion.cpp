/*!
 *  \file   boxreligion.cpp
 *  \author Eva Navratilova
 */

#include "boxreligion.h"

BoxReligion::BoxReligion(Kernel &k, Identifier &p, QWidget *parent)
    : BoxEditableList (tr("Religion"), k, p, parent)
{

}

void BoxReligion::update()
{
    this->remove();

    const unsigned int count = _kernel.record()->getIndividualReliCount(_proband);
    for(unsigned int i = 0; i < count; i++)
    {
        _list.addItem(TextFormatter::getReligionFullText(_kernel, _proband, i));
    }
}

void BoxReligion::swapIndexes(unsigned int index1, unsigned int index2)
{
    _kernel.record()->swapIndividualReli(_proband, index1, index2);
}

void BoxReligion::clickAdd()
{
    QString description;
    DateType datetype = DateType::PERIOD;
    Date date1;
    Date date2;

    _dialogEdit = new DialogEditableDescription(tr("Add %1").arg(_title), description, datetype, date1, date2,
                                                _kernel.record()->getStringsReligion());
    int accepted = _dialogEdit->exec();

    if(accepted)
    {
        unsigned int index = _kernel.record()->setIndividualReli(_proband);
        this->saveData(index, description, datetype, date1, date2);
        _list.addItem(TextFormatter::getReligionFullText(_kernel, _proband, index));
    }

    _dialogEdit->deleteLater();
}

void BoxReligion::clickEdit(unsigned int index)
{
    Q_UNUSED(index);

    QString description = _kernel.record()->getIndividualReliDescription(_proband, index);
    DateType datetype = _kernel.record()->getIndividualReliDateType(_proband, index);
    Date date1 = _kernel.record()->getIndividualReliDate1(_proband, index);
    Date date2 = _kernel.record()->getIndividualReliDate2(_proband, index);

    _dialogEdit = new DialogEditableDescription(tr("Edit %1").arg(_title), description, datetype, date1, date2,
                                                _kernel.record()->getStringsReligion());
    int accepted = _dialogEdit->exec();

    if(accepted)
    {
        this->saveData(index, description, datetype, date1, date2);
        _list.currentItem()->setText(TextFormatter::getReligionFullText(_kernel, _proband, index));
    }

    _dialogEdit->deleteLater();
}

void BoxReligion::clickDelete(unsigned int index)
{
    _kernel.record()->removeIndividualReli(_proband, index);
}

void BoxReligion::saveData(const unsigned int index, QString &description, DateType &datetype, Date &date1, Date &date2)
{
    _kernel.record()->setIndividualReliDescription(_proband, index, description);
    _kernel.record()->setIndividualReliDateType(_proband, index, datetype);
    _kernel.record()->setIndividualReliDate1(_proband, index, date1);
    _kernel.record()->setIndividualReliDate2(_proband, index, date2);
}
