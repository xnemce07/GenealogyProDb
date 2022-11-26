/*!
 *  \file   boxmarriage.h
 *  \author Eva Navratilova
 */

#ifndef BOXMARRIAGE_H
#define BOXMARRIAGE_H

#include <QLineEdit>
#include <QSpacerItem>

#include "box.h"
#include "subbox/subboxdate.h"
#include "subbox/subboxsimple.h"
#include "subbox/subboxcitation.h"
#include "subbox/subboxpersonref.h"
#include "userinterface/objects/labelwidthadjuster.h"
#include "userinterface/objects/completerinline.h"
//#include "../../../dialogs/data/dialogaddperson.h"
#include "../../../dialogs/data/dialogassignperson.h"

class BoxMarriage : public Box, public LabelWidthAdjuster
{
    Q_OBJECT
private:
    Identifier &_family;

    SubboxDate *_subboxDate;
    SubboxSimple *_subboxPlace;
    SubboxCitation *_subboxSource;

    SubboxPersonRef *_subboxPriest;
    SubboxPersonRef *_subboxWitness1;
    SubboxPersonRef *_subboxWitness2;

    CompleterInline *_comPlace = nullptr;

    QSpacerItem *_spacer;

    //DialogAddPerson *_dialogAddPerson;
    DialogAssignPerson *_dialogAddExistingPerson;

public:
    BoxMarriage(QString title, Kernel &k, Identifier &p, Identifier &f, QWidget *parent = nullptr);

    void update() override;
    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

private:
    void fill() override;
    void remove();

    void setSourceEnabled();

private slots:
    void changeMarriageState(bool checked);

    void changeDatetype(const DateType datetype);
    void changeDate1(const Date date);
    void changeDate2(const Date date);
    void changePlace(const QString plac);
    void changeSourceRef(const Identifier src);
    void changeSourcePage(const QString page);
    void changeSourceUrl(const QString url);

    void addPriest();
    void removePriest();
    void addWitness1();
    void removeWitness1();
    void addWitness2();
    void removeWitness2();

    void addSource();
};

#endif // BOXMARRIAGE_H
