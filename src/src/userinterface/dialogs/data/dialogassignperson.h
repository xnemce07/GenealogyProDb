/*!
 *  \file   dialogassignperson.h
 *  \author Eva Navratilova
 */

#ifndef DIALOGADDEXISTINGPERSON_H
#define DIALOGADDEXISTINGPERSON_H

#include <QDialog>
#include <QGridLayout>
#include <QVector>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QFont>
#include <QFontMetrics>

#include "kernel.h"
#include "textformatter.h"
#include "userinterface/dialogs/dialog.h"
#include "userinterface/objects/personlist.h"

class DialogAssignPerson : public Dialog
{
    Q_OBJECT
private:
    Kernel &_kernel;
    QVector<Identifier> _people;
    Identifier _selectedRef;

    QLineEdit _lineSearch;
    PersonList *_table;

    QPushButton _buAddPerson;
    QPushButton _buSelectPerson;

public:
    /**
     * @brief Constructor
     *
     * @param k         Kernel reference
     * @param p         Proband reference
     * @param g         Which gender should be included in the person list (UDET == ANY gender)
     * @param parent    Parent widget pointer
     */
    DialogAssignPerson(Kernel &k, QVector<Identifier> p, QWidget *parent = nullptr);
    ~DialogAssignPerson() override;

    /**
     * @brief Returns the Identifier of selected individual
     *
     * If dialog was accepted and returned Identifier is invalid -> New Person
     * If dialog was accepted and returned Identifier is valid -> Existing Person selected
     * If dialog was rejected -> Cancel action
     *
     * @return Identifier of selected existing person or invalid Identifier in case of new person
     */
    int getSelectedId(Identifier& ref);

private:
    void fill() override;
    int exec() override;

private slots:
    void doubleClickAccept(const QModelIndex& i);

    void addClicekd();
    void selectClicked();
};

#endif // DIALOGADDEXISTINGPERSON_H
