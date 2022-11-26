#include "maintabwidget.h"

MainTabWidget::MainTabWidget(Kernel &k, Identifier &p)
    : _kernel(k), _proband(p)
{
    this->_tabIndividual = new TabIndividual(_kernel, _proband);
    this->addTab(_tabIndividual, tr("Individual"));
}

void MainTabWidget::saveSettings()
{

}
