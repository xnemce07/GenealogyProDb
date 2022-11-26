/*!
 *  \file   partnerstabwidget.h
 *  \author Eva Navratilova
 */

#ifndef PARTNERSTABWIDGET_H
#define PARTNERSTABWIDGET_H

#include <QTabWidget>
#include <QVector>
#include <QGridLayout>
#include <QToolButton>
#include <QPushButton>
#include <QFont>
#include <QFontMetrics>
#include <qglobal.h>
#include <QObject>
#include <QtGlobal>

#include "../../../../../kernel.h"
#include "../../../../../textformatter.h"
#include "partnerwidget.h"
#include "partneroverview.h"
#include "../../../../dialogs/messageboxes/messagedelete.h"
//#include "../../../../dialogs/data/dialogaddperson.h"
#include "../../../../dialogs/data/dialogassignperson.h"

class PartnersTabWidget : public QTabWidget
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_proband;

    QVector<Identifier> _families;

    PartnerOverview* _tabOverview;
    QVector<PartnerWidget*> _tabsPartner;
    QToolButton _buAddPartner;
    QWidget *_emptyWidget;
    int _tabHeight;

    MessageDelete *_dialogDelete;
    //DialogAddPerson *_dialogAddPerson;
    DialogAssignPerson *_dialogAddExistingPerson;

public:
    PartnersTabWidget(Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update();
    //void addPartnerTab(Identifier family);
    //void addPlusTab();

private:
    void fill();

    Gender getSpouseGender();
    void addPartner(const Identifier spouse);
    void addNewPartner();
    void addExistingPartner();
    void swapPartners(Identifier fam1, Identifier fam2);
    void remove();

signals:
    void probandChanged(Identifier ref);
    void sourceChanged(const Identifier &ref);

private slots:
    void tabsMovable(int index);

    void changeProbandPartner(int index);
    void addPartnerClicked(bool checked);
    void movePartner(int to, int from);
    void removePartner(int index);

};

#endif // PARTNERSTABWIDGET_H
