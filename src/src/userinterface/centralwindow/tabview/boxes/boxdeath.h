/*!
 *  \file   boxdeath.h
 *  \author Eva Navratilova
 */

#ifndef BOXDEATH_H
#define BOXDEATH_H

#include <QLabel>
#include <QLineEdit>

#include "box.h"
#include "subbox/subboxdate.h"
#include "subbox/subboxsimple.h"
#include "subbox/subboxcitation.h"
#include "userinterface/objects/labelwidthadjuster.h"
#include "userinterface/objects/completerinline.h"
#include "boxburial.h"

class BoxDeath : public Box, public LabelWidthAdjuster
{
    Q_OBJECT
private:
    SubboxDate *_subboxDate;
    SubboxSimple *_subboxPlace;
    SubboxSimple *_subboxCause;
    SubboxCitation *_subboxSource;

    BoxBurial *_boxBurial;
    QSpacerItem *_spacer;


    CompleterInline *_comPlace = nullptr;
    CompleterInline *_comCause = nullptr;

public:
    explicit BoxDeath(QString title, Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update() override;

    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

private:
    void fill() override;
    void remove();

    void setSourceEnabled();

private slots:
    void changeDeathState(bool checked);

    void changeDatetype(const DateType datetype);
    void changeDate1(const Date date);
    void changeDate2(const Date date);
    void changePlace(const QString plac);
    void changeCause(const QString caus);
    void changeSourceRef(const Identifier src);
    void changeSourcePage(const QString page);
    void changeSourceUrl(const QString url);

    void addSource();

};

#endif // BOXDEATH_H
