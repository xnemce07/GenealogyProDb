/*!
 *  \file   boxdivorce.h
 *  \author Eva Navratilova
 */

#ifndef BOXDIVORCED_H
#define BOXDIVORCED_H

#include <QSpacerItem>

#include "box.h"
#include "subbox/subboxdate.h"

class BoxDivorce : public Box
{
    Q_OBJECT
private:
    Identifier &_family;

    SubboxDate *_subboxDate;

    QSpacerItem *_spacer;

public:
    BoxDivorce(QString title, Kernel &k, Identifier &p, Identifier &f, QWidget *parent = nullptr);

    void update() override;

private:
    void fill() override;

private slots:
    void changeDivorceState(bool checked);

    void changeDatetype(const DateType datetype);
    void changeDate1(const Date date);
    void changeDate2(const Date date);
};

#endif // BOXDIVORCED_H
