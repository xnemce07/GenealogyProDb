/*!
 *  \file   tabindividual.h
 *  \author Eva Navratilova
 */

#ifndef TABINDIVIDUAL_H
#define TABINDIVIDUAL_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollBar>
#include <QApplication>
#include <QScreen>

#include "../../../kernel.h"
#include "tabindividual/individuallist.h"
#include "tabindividual/individualdetail.h"
#include "userinterface/objects/sizer.h"
#include "userinterface/objects/splitter.h"

class TabIndividual : public QWidget
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_proband;

    QGridLayout _layout;

    IndividualList  *_listView = nullptr;      // List View on the left

    Splitter _splitter;
    QWidget _widget;

    IndividualDetail *_detail;


public:
    explicit TabIndividual(Kernel &k, Identifier &p, QWidget *parent = nullptr);
    ~TabIndividual();
    void fill();

signals:
    void probandChanged(Identifier ref);
    void sourceChanged(const Identifier &ref);
    void dataChanged();

public slots:
    void update();

    static void defaultSettings();
    void saveSettings() const;

};

#endif // TABINDIVIDUAL_H
