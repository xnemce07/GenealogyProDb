#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include <QTabWidget>
#include <QSettings>

#include "../../kernel.h"
#include "tabview/tabindividual.h"

class MainTabWidget : public QTabWidget
{
private:
    Kernel &_kernel;
    Identifier &_proband;

    TabIndividual* _tabIndividual;

public:
    MainTabWidget(Kernel &k, Identifier &p);


    void saveSettings();
};

#endif // MAINTABWIDGET_H
