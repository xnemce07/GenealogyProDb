/*!
 *  \file   partnerstabwidget.cpp
 *  \author Eva Navratilova
 */

#include "partnerstabwidget.h"

PartnersTabWidget::PartnersTabWidget(Kernel &k, Identifier &p, QWidget *parent)
    : QTabWidget(parent), _kernel(k), _proband(p)
{
    this->setUsesScrollButtons(true);
    this->setTabsClosable(true);
    QFont font;
    QFontMetrics metrics(font);
    _tabHeight = metrics.height();
    this->tabBar()->setContentsMargins(5,0,5,0);
    this->tabBar()->setStyleSheet("QTabBar{padding: 0px;}");

    this->fill();

    connect(this, &PartnersTabWidget::tabBarClicked, this, &PartnersTabWidget::tabsMovable);
    connect(this, &PartnersTabWidget::tabBarDoubleClicked, this, &PartnersTabWidget::changeProbandPartner);
    connect(&_buAddPartner, &QToolButton::clicked, this, &PartnersTabWidget::addPartnerClicked);
    connect(this->tabBar(), &QTabBar::tabMoved, this, &PartnersTabWidget::movePartner);
    connect(this, &PartnersTabWidget::tabCloseRequested, this, &PartnersTabWidget::removePartner);
}

void PartnersTabWidget::update()
{
    this->remove();

    // Update family vector
    _families = _kernel.record()->getFamiliesOfIndividualParent(_proband);

    // Update the Overview tab
    _tabOverview->update(_families);

    // Add tab for every partner of proband
    for(auto family = _families.begin(); family != _families.end(); family++)
    {
        Identifier partner = _kernel.record()->getFamilyHusband(*family);
        if(partner == _proband)
        {
            partner = _kernel.record()->getFamilyWife(*family);
        }
        if(!_kernel.record()->isIndividual(partner))
        {
            continue;
        }
        _tabsPartner.append(new PartnerWidget(_kernel, _proband, *family));
        this->addTab(_tabsPartner.last(), TextFormatter::getPersonLineText(_kernel, partner));
        this->tabBar()->tabButton(this->count() - 1, QTabBar::RightSide)->setToolTip(tr("Remove partner"));
        _tabsPartner.last()->update();

        /*QToolButton* bu = new QToolButton();
        bu->setText("×");
        bu->setToolTip(tr("Remove partner"));
        bu->setContentsMargins(0,0,0,0);
        bu->setStyleSheet("QToolButton{padding: 2px;}");
        bu->setFixedSize(_tabHeight, _tabHeight);
        _buDeletePartner.push_back(bu);
        this->tabBar()->setTabButton(this->count() - 1, QTabBar::RightSide, _buDeletePartner.last());*/

        connect(_tabsPartner.last(), &PartnerWidget::probandChanged, this, &PartnersTabWidget::probandChanged);
        connect(_tabsPartner.last(), &PartnerWidget::sourceChanged, this, &PartnersTabWidget::sourceChanged);
    }
    if(this->count() > 1)
    {
        this->setCurrentIndex(1);
    }
}

void PartnersTabWidget::fill()
{
    // Initialize values

    _tabOverview = new PartnerOverview(_kernel, _proband, _families);
    this->addTab(_tabOverview, tr("Overview"));
    this->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);
    connect(_tabOverview, &PartnerOverview::probandChanged, this, &PartnersTabWidget::probandChanged);

    this->setCornerWidget(&_buAddPartner, Qt::TopLeftCorner);

    // Set static values
    this->setContentsMargins(0,0,0,0);

    _buAddPartner.setIcon(QIcon(":/icons/partners"));
    _buAddPartner.setToolTip(tr("Add Partner..."));
    //_buAddPartner.setAutoRaise(true);
    _buAddPartner.setVisible(true);

    // Set layout
    //this->updateGeometry();
}

Gender PartnersTabWidget::getSpouseGender()
{
    Gender g;
    Gender probandGender = _kernel.record()->getIndividualGender(_proband);
    if(probandGender == Gender::MALE)
    {
        g = Gender::FEMALE;
    }
    else
    {
        g = Gender::MALE;
    }
    return g;
}

void PartnersTabWidget::addPartner(const Identifier spouse)
{
    Identifier husb, wife;
    Gender probandGender = _kernel.record()->getIndividualGender(_proband);
    if(probandGender == Gender::MALE)
    {
        husb = _proband;
        wife = spouse;
    }
    else
    {
        husb = spouse;
        wife = _proband;
    }
    _kernel.record()->setIndividualCouple(husb, wife);
    QSettings settings;
    Identifier family = _kernel.record()->getFamilyOfCouple(husb, wife);
    _kernel.record()->setFamilyMarried(family, settings.value("dataConstraints/autoMarried").toBool());
}

void PartnersTabWidget::addNewPartner()
{
    QSettings settings;
    Identifier spouse = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(spouse, settings.value("dataConstraints/autoDead").toBool());
    Gender g = this->getSpouseGender();
    _kernel.record()->setIndividualGender(spouse, g);

    this->addPartner(spouse);

    emit(this->probandChanged(spouse));
}

void PartnersTabWidget::addExistingPartner()
{
    QVector<Identifier> potentialSpouses;
    QVector<Identifier> currentSpouses = _kernel.record()->getIndividualPartners(_proband);

    Gender spouseGender = this->getSpouseGender();
    Identifier first = _kernel.record()->getIdentifierIndividualFirst();
    Identifier last = _kernel.record()->getIdentifierIndividualLast();
    for(Identifier current = first; current < last; _kernel.record()->getIdentifierIndividualNext(current))
    {
        // Skip existing spouses
        if(currentSpouses.contains(current))
        {
            continue;
        }

        if(_kernel.record()->getIndividualGender(current) == spouseGender)
        {
            // Newest added first
            potentialSpouses.push_front(current);
        }
    }

    _dialogAddExistingPerson = new DialogAssignPerson(_kernel, potentialSpouses);
    Identifier spouse;
    int result = _dialogAddExistingPerson->getSelectedId(spouse);
    if(_kernel.record()->isIndividual(spouse))
    {
        this->addPartner(spouse);
        this->update();

        for(int index = 0; index < _tabsPartner.length(); index++)
        {
            if(_tabsPartner.at(index)->getPartnerIdentifier() == spouse)
            {
                /// TODO - values ok, but gui doesnt show the right tab sometimes
                //qDebug() << "INDEX IS " << index;
                this->setCurrentIndex(index + 1);
                //qDebug() << "CURRENT is "<< this->currentIndex();
                //this->repaint(); // Does nothing
                break;
            }
        }
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(spouse))
    {
        this->addNewPartner();
    }
}

void PartnersTabWidget::swapPartners(Identifier fam1, Identifier fam2)
{
    _kernel.record()->swapFamilies(fam1, fam2);
}

void PartnersTabWidget::remove()
{
    _families.clear();
    for(int it = 1; it < this->count(); it++)
    {
        this->removeTab(it);
    }
    for(auto it = _tabsPartner.begin(); it != _tabsPartner.end(); it++)
    {
        (*it)->deleteLater();
    }
    _tabsPartner.clear();
    /*for(auto it = _buDeletePartner.begin(); it != _buDeletePartner.end(); it++)
    {
        (*it)->deleteLater();
    }
    _buDeletePartner.clear();*/
}

void PartnersTabWidget::tabsMovable(int index)
{
    this->setMovable(index != 0);
}

void PartnersTabWidget::changeProbandPartner(int index)
{
    if(index >= 1 && index < this->count())
    {
        Identifier spouse = _tabsPartner.at(index - 1)->getPartnerIdentifier();
        emit(this->probandChanged(spouse));
    }
}

void PartnersTabWidget::addPartnerClicked(bool checked)
{
    Q_UNUSED(checked);

    Gender probandGender = _kernel.record()->getIndividualGender(_proband);
    if(probandGender != Gender::UNDET)
    {
        /*_dialogAddPerson = new DialogAddPerson();
        int r = _dialogAddPerson->exec();
        _dialogAddPerson->deleteLater();

        if(r == static_cast<int>(Result::NEW))
        {
            this->addNewPartner();
        }
        else if(r == static_cast<int>(Result::EXISTING))
        {*/
            this->addExistingPartner();
        //}
    }
    else
    {
        // Undetermined gender indi cannot have a spouse
        MessageBox dialogUndetGender(MessageBox::Information,
                                            tr("Unable to add partner"),
                                            tr("Unable to add partner to a person with undetermined gender.\n"
                                               "Please set the person's gender and try again."),
                                            MessageBox::StandardButton::Ok);
        dialogUndetGender.exec();
    }
}

void PartnersTabWidget::movePartner(int to, int from)
{
    bool fromValid = (from >= 1   && from <  this->count());
    bool toValid   = (to   >= 1   && to   <= this->count());
    if(fromValid && toValid)
    {
        // Align indexes to _tabsPartner vector
        int src = from - 1;
        int dst = to - 1;

        if(src < dst)
        {
            while(src < dst)
            {
                Identifier fam1, fam2;
                fam1 = _tabsPartner.at(src)->getFamilyIdentifier();
                fam2 = _tabsPartner.at(src + 1)->getFamilyIdentifier();

                this->swapPartners(fam1, fam2);
                src++;
            }
        }
        else // src >= dst
        {
            while(src > dst)
            {
                Identifier fam1, fam2;
                fam1 = _tabsPartner.at(src)->getFamilyIdentifier();
                fam2 = _tabsPartner.at(src - 1)->getFamilyIdentifier();

                this->swapPartners(fam1, fam2);
                src--;
            }
        }
    }
    else if (to == 0)
    {
        this->tabBar()->moveTab(from, to);
    }
}

void PartnersTabWidget::removePartner(int index)
{
    if(index >= 1 && index < this->count())
    {
        _dialogDelete = new MessageDelete(tr("this partnership"));
        if(_dialogDelete->exec() == MessageDelete::Accepted)
        {
            Identifier spouse = _tabsPartner.at(index - 1)->getPartnerIdentifier();
            Identifier fam = _kernel.record()->getFamilyOfCouple(_proband, spouse);
            _kernel.record()->removeFamilySpouse(fam, spouse);
        }
    }
    this->update();
}
