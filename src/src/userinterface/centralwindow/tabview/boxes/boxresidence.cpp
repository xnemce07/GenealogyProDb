/*!
 *  \file   boxresidence.cpp
 *  \author Eva Navratilova
 */

#include "boxresidence.h"

BoxResidence::BoxResidence(Kernel &k, Identifier &p, QWidget *parent)
    : BoxEditableList (tr("Residence"), k, p, parent)
{

}

void BoxResidence::update()
{
    this->remove();

    const unsigned int count = _kernel.record()->getIndividualResiCount(_proband);
    for(unsigned int i = 0; i < count; i++)
    {
        _list.addItem(TextFormatter::getResidenceFullText(_kernel, _proband, i));
    }
}

void BoxResidence::swapIndexes(unsigned int index1, unsigned int index2)
{
    _kernel.record()->swapIndividualResi(_proband, index1, index2);
}

void BoxResidence::clickAdd()
{
    QString city;
    QString addr;
    DateType datetype = DateType::PERIOD;
    Date date1;
    Date date2;

    _dialogEdit = new DialogEditableResidence(tr("Add %1").arg(_title), city, addr, datetype, date1, date2,
                                              _kernel.record()->getStringsCities(),
                                              _kernel.record()->getStringsAddress(city));
    int accepted = _dialogEdit->exec();

    if(accepted)
    {
        unsigned int index = _kernel.record()->setIndividualResi(_proband);
        this->saveData(index, city, addr, datetype, date1, date2);
        _list.addItem(TextFormatter::getResidenceFullText(_kernel, _proband, index));
    }

    _dialogEdit->deleteLater();
}

void BoxResidence::clickEdit(unsigned int index)
{
    Q_UNUSED(index);

    QString city = _kernel.record()->getIndividualResiAddrCity(_proband, index);
    QString addr = _kernel.record()->getIndividualResiAddrAddr(_proband, index);
    DateType datetype = _kernel.record()->getIndividualResiDateType(_proband, index);
    Date date1 = _kernel.record()->getIndividualResiDate1(_proband, index);
    Date date2 = _kernel.record()->getIndividualResiDate2(_proband, index);

    _dialogEdit = new DialogEditableResidence(tr("Edit %1").arg(_title), city, addr, datetype, date1, date2,
                                              _kernel.record()->getStringsCities(),
                                              _kernel.record()->getStringsAddress(city));
    int accepted = _dialogEdit->exec();

    if(accepted)
    {
        this->saveData(index, city, addr, datetype, date1, date2);
        _list.currentItem()->setText(TextFormatter::getResidenceFullText(_kernel, _proband, index));
    }

    _dialogEdit->deleteLater();
}

void BoxResidence::clickDelete(unsigned int index)
{
    _kernel.record()->removeIndividualResi(_proband, index);
}

void BoxResidence::saveData(const unsigned int index, QString &city, QString &addr, DateType &datetype, Date &date1, Date &date2)
{
    _kernel.record()->setIndividualResiAddrCity(_proband, index, city);
    _kernel.record()->setIndividualResiAddrAddr(_proband, index, addr);
    _kernel.record()->setIndividualResiDateType(_proband, index, datetype);
    _kernel.record()->setIndividualResiDate1(_proband, index, date1);
    _kernel.record()->setIndividualResiDate2(_proband, index, date2);
}
