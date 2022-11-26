/*!
 *  \file   boxreligion.h
 *  \author Eva Navratilova
 */

#ifndef BOXRELIGION_H
#define BOXRELIGION_H

#include "boxeditablelist.h"
#include "../../../dialogs/data/dialogeditabledescription.h"

class BoxReligion : public BoxEditableList
{
    Q_OBJECT
public:
    BoxReligion(Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update() override;

private:
    void swapIndexes(unsigned int index1, unsigned int index2) override;

private slots:
    void clickAdd() override;
    void clickEdit(unsigned int index) override;
    void clickDelete(unsigned int index) override;
    void saveData(const unsigned int index, QString &description, DateType &datetype, Date &date1, Date &date2);

};

#endif // BOXRELIGION_H
