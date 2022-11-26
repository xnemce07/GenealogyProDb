/*!
 *  \file   subboxsourcedata.h
 *  \author Eva Navratilova
 */

#ifndef SUBBOXSOURCEDATA_H
#define SUBBOXSOURCEDATA_H

#include "../../../../../kernel.h"
#include "subboxdate.h"
#include "subboxsimple.h"
#include "subboxweb.h"
#include "userinterface/dialogs/messageboxes/messagedelete.h"

class SubboxSourceData : public QWidget
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_source;
    const CommonEventType _type;
    const unsigned int _index;
    int _row;

    QGridLayout &_layout;

    SubboxSimple* _subboxPlace;
    SubboxDate* _subboxDate1;
    SubboxDate* _subboxDate2;
    SubboxSimple* _subboxPage1;
    SubboxSimple* _subboxPage2;
    SubboxWeb* _subboxUrl;
    NarrowButton _buDelete;


public:
    SubboxSourceData(Kernel &k, Identifier &s, CommonEventType t, unsigned int index, int row, QGridLayout &layout, QWidget* parent = nullptr);
    ~SubboxSourceData();

    void update();
    void setFocus();

private:
    void fill();

signals:
    void dataChanged();

private slots:
    void placeChanged(const QString &place);
    void date1Changed(const Date &date);
    void date2Changed(const Date &date);
    void page1Changed(const QString &page);
    void page2Changed(const QString &page);
    void urlChanged(const QString &url);
    void deleteClicked(bool checked);

};

#endif // SUBBOXSOURCEDATA_H
