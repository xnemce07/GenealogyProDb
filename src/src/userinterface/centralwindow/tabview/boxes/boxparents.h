/*!
 *  \file   boxparents.h
 *  \author Eva Navratilova
 */

#ifndef BOXPARENTS_H
#define BOXPARENTS_H

#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "../../../../kernel.h"
#include "box.h"
#include "userinterface/objects/labelwidthadjuster.h"
#include "subbox/subboxpersonref.h"
//#include "../../../dialogs/data/dialogaddperson.h"
#include "../../../dialogs/data/dialogassignperson.h"
/// TODO - change parent to Box

class BoxParents : public Box, public LabelWidthAdjuster
{
    Q_OBJECT
private:
    SubboxPersonRef *_subboxFather;
    SubboxPersonRef *_subboxMother;

    //DialogAddPerson *_dialogAddPerson;
    DialogAssignPerson *_dialogAddExistingPerson;

public:
    BoxParents(QString title, Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update() override;

private:
    void fill() override;
    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

private slots:
    void addFather();
    void removeFather();
    void addMother();
    void removeMother();
};

#endif // BOXPARENTS_H
