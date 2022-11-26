/*!
 *  \file   boxburial.h
 *  \author Eva Navratilova
 */

#ifndef BOXBURIAL_H
#define BOXBURIAL_H

#include "box.h"
#include "userinterface/objects/labelwidthadjuster.h"
#include "userinterface/objects/completerinline.h"
#include "subbox/subboxdate.h"
#include "subbox/subboxsimple.h"
#include "subbox/subboxpersonref.h"
//#include "../../../dialogs/data/dialogaddperson.h"
#include "../../../dialogs/data/dialogassignperson.h"

class BoxBurial : public Box, public LabelWidthAdjuster
{
    Q_OBJECT
private:
    SubboxDate *_subboxDate;
    SubboxSimple *_subboxPlace;
    SubboxPersonRef *_subboxPriest;

    //DialogAddPerson *_dialogAddPerson;
    DialogAssignPerson *_dialogAddExistingPerson;

    CompleterInline *_comPlace = nullptr;

public:
    BoxBurial(QString title, Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update() override;

private:
    void fill() override;
    void remove();
    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

private slots:
    void changeDatetype(const DateType datetype);
    void changeDate1(const Date date);
    void changeDate2(const Date date);
    void changePlace(const QString plac);

    void addPriest();
    void removePriest();

};

#endif // BOXBURIAL_H
