/*!
 *  \file   tabsource.h
 *  \author Eva Navratilova
 */

#ifndef TABSOURCE_H
#define TABSOURCE_H

#include <QWidget>
#include <QGridLayout>
#include <QApplication>
#include <QScreen>

#include "../../../kernel.h"
#include "tabsource/sourcesearchlist.h"
#include "tabsource/sourcescrollarea.h"
#include "userinterface/objects/splitter.h"

class TabSource : public QWidget
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_source;

    QGridLayout _layout;
    Splitter _splitter;

    SourceSearchList*   _list;
    SourceScrollArea* _detail;

public:
    explicit TabSource(Kernel &k, Identifier &s, QWidget *parent = nullptr);
    ~TabSource() override;

    void update();

    static void defaultSettings();
    void saveSettings() const;

private:
    void fill();
    void remove();

signals:
    void sourceChanged(Identifier ref);

};

#endif // TABSOURCE_H
