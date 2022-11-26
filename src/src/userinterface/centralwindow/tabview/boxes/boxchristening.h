/*!
 *  \file   boxchristening.h
 *  \author Eva Navratilova
 */

#ifndef BOXCHRISTENING_H
#define BOXCHRISTENING_H

#include "box.h"
#include "userinterface/objects/labelwidthadjuster.h"
#include "./subbox/subboxdate.h"
#include "./subbox/subboxpersonref.h"
//#include "../../../dialogs/data/dialogaddperson.h"
#include "../../../dialogs/data/dialogassignperson.h"

class BoxChristening : public Box, public LabelWidthAdjuster
{

    Q_OBJECT

private:
    SubboxDate *_subboxDate;
    SubboxPersonRef *_subboxPriest;
    SubboxPersonRef *_subboxGodfather;
    SubboxPersonRef *_subboxGodmother;

    //DialogAddPerson *_dialogAddPerson;
    DialogAssignPerson *_dialogAddExistingPerson;

public:
    BoxChristening(QString title, Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update() override;

private:
    void fill() override;
    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

private slots:
    void changeDatetype(const DateType datetype);
    void changeDate1(const Date date);
    void changeDate2(const Date date);

    void addPriest();
    void removePriest();
    void addGodfather();
    void removeGodfather();
    void addGodmother();
    void removeGodmother();

};

#endif // BOXCHRISTENING_H
