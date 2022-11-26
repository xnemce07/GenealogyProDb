/*!
 *  \file   boxoccupation.cpp
 *  \author Eva Navratilova
 */

#include "boxoccupation.h"


BoxOccupation::BoxOccupation(Kernel &k, Identifier &p, QWidget *parent)
    : BoxEditableList (tr("Occupation"), k, p, parent)
{

}

void BoxOccupation::update()
{
    this->remove();

    const unsigned int count = _kernel.record()->getIndividualOccuCount(_proband);
    for(unsigned int i = 0; i < count; i++)
    {
        _list.addItem(TextFormatter::getOccupationFullText(_kernel, _proband, i));
    }
}

void BoxOccupation::swapIndexes(unsigned int index1, unsigned int index2)
{
    _kernel.record()->swapIndividualOccu(_proband, index1, index2);
}

void BoxOccupation::clickAdd()
{
    QString description;
    DateType datetype = DateType::PERIOD;
    Date date1;
    Date date2;

    _dialogEdit = new DialogEditableDescription(tr("Add %1").arg(_title), description, datetype, date1, date2,
                                                _kernel.record()->getStringsOccupation());
    int accepted = _dialogEdit->exec();

    if(accepted)
    {
        unsigned int index = _kernel.record()->setIndividualOccu(_proband);
        this->saveData(index, description, datetype, date1, date2);
        _list.addItem(TextFormatter::getOccupationFullText(_kernel, _proband, index));
    }

    _dialogEdit->deleteLater();
}

void BoxOccupation::clickEdit(unsigned int index)
{
    Q_UNUSED(index);

    QString description = _kernel.record()->getIndividualOccuDescription(_proband, index);
    DateType datetype = _kernel.record()->getIndividualOccuDateType(_proband, index);
    Date date1 = _kernel.record()->getIndividualOccuDate1(_proband, index);
    Date date2 = _kernel.record()->getIndividualOccuDate2(_proband, index);

    _dialogEdit = new DialogEditableDescription(tr("Edit %1").arg(_title), description, datetype, date1, date2,
                                                _kernel.record()->getStringsOccupation());
    int accepted = _dialogEdit->exec();

    if(accepted)
    {
        this->saveData(index, description, datetype, date1, date2);
        _list.currentItem()->setText(TextFormatter::getOccupationFullText(_kernel, _proband, index));
    }

    _dialogEdit->deleteLater();
}

void BoxOccupation::clickDelete(unsigned int index)
{
    _kernel.record()->removeIndividualOccu(_proband, index);
}

void BoxOccupation::saveData(const unsigned int index, QString &description, DateType &datetype, Date &date1, Date &date2)
{
    _kernel.record()->setIndividualOccuDescription(_proband, index, description);
    _kernel.record()->setIndividualOccuDateType(_proband, index, datetype);
    _kernel.record()->setIndividualOccuDate1(_proband, index, date1);
    _kernel.record()->setIndividualOccuDate2(_proband, index, date2);
}
