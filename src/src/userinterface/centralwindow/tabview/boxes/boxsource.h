/*!
 *  \file   boxsource.h
 *  \author Eva Navratilova
 */

#ifndef BOXSOURCE_H
#define BOXSOURCE_H

#include <QFrame>
#include <QScrollArea>

#include "box.h"
#include "subbox/subboxsourcedata.h"
#include "userinterface/objects/label.h"
#include "userinterface/objects/narrowbutton.h"

class BoxSource : public Box
{
    Q_OBJECT
private:
    Identifier &_source;
    CommonEventType _type;

    /*QWidget _widgetScrollArea;
    QGridLayout _layoutScrollArea;*/

    QLabel _laPlaces;
    QLabel _laDates;
    QLabel _laPages;
    QLabel _laUrls;

    //QScrollArea _scrollArea;

    NarrowButton _buAdd;

    QVector<SubboxSourceData*> _subboxesSourceData;

public:
    BoxSource(QString title, Kernel &k, Identifier &src, CommonEventType t, QWidget *parent = nullptr);
    virtual ~BoxSource() override;


private:
    void fill() override;
    void remove();

signals:
    void dataChanged();

public slots:
    void update() override;

private slots:
    void addSourceClicked(bool checked);
};

#endif // BOXSOURCE_H
