/*!
 *  \file   boxpartners.h
 *  \author Eva Navratilova
 */

#ifndef BOXPARTNERS_H
#define BOXPARTNERS_H

#include "box.h"
#include "partners/partnerstabwidget.h"

class BoxPartners : public Box
{
    Q_OBJECT
private:
    PartnersTabWidget* _tabsWidget;

public:
    explicit BoxPartners(QString title, Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update() override;

private:
    void fill() override;
};

#endif // BOXPARTNERS_H
