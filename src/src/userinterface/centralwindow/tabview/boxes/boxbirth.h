/*!
 *  \file   boxbirth.h
 *  \author Eva Navratilova
 */

#ifndef BOXBIRTH_H
#define BOXBIRTH_H

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QVector>

#include "./box.h"
#include "./subbox/subboxdate.h"
#include "./subbox/subboxsimple.h"
#include "./subbox/subboxcitation.h"
#include "./subbox/subboxpersonref.h"
#include "userinterface/objects/labelwidthadjuster.h"
#include "userinterface/objects/completerinline.h"
#include "boxchristening.h"
//#include "../../../dialogs/data/dialogaddperson.h"
#include "../../../dialogs/data/dialogassignperson.h"

class BoxBirth : public Box, public LabelWidthAdjuster
{
    Q_OBJECT
private:
    SubboxDate *_subboxDate;
    SubboxSimple *_subboxPlace;
    SubboxCitation *_subboxSource;
    SubboxPersonRef *_subboxObstetrix;

    BoxChristening *_boxChristening;
    QSpacerItem *_spacer;

    CompleterInline *_comPlace = nullptr;

    //DialogAddPerson *_dialogAddPerson;
    DialogAssignPerson *_dialogAddExistingPerson;

public:
    BoxBirth(QString title, Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update() override;

private:
    void fill() override;
    void remove();
    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

    void setSourceEnabled();

signals:
    void dataChanged();

private slots:
    void changeDatetype(const DateType datetype);
    void changeDate1(const Date date);
    void changeDate2(const Date date);
    void changePlace(const QString plac);
    void changeSourceRef(const Identifier src);
    void changeSourcePage(const QString page);
    void changeSourceUrl(const QString url);

    void addObstetrix();
    void removeObstetrix();

    void addSource();
};

#endif // BOXBIRTH_H
