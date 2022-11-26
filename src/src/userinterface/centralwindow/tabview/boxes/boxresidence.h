/*!
 *  \file   boxresidence.h
 *  \author Eva Navratilova
 */

#ifndef BOXRESIDENCE_H
#define BOXRESIDENCE_H

#include "boxeditablelist.h"
#include "../../../dialogs/data/dialogeditableresidence.h"

class BoxResidence : public BoxEditableList
{
    Q_OBJECT
public:
    BoxResidence(Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update() override;

private:
    void swapIndexes(unsigned int index1, unsigned int index2) override;

private slots:
    void clickAdd() override;
    void clickEdit(unsigned int index) override;
    void clickDelete(unsigned int index) override;
    void saveData(const unsigned int index, QString &city, QString &addr, DateType &datetype, Date &date1, Date &date2);
};

#endif // BOXRESIDENCE_H
