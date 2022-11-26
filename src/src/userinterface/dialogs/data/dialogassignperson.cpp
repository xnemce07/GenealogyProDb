/*!
 *  \file   dialogassignperson.cpp
 *  \author Eva Navratilova
 */

#include "dialogassignperson.h"

DialogAssignPerson::DialogAssignPerson(Kernel &k, QVector<Identifier> p, QWidget *parent)
    : Dialog (parent), _kernel(k), _people(p)
{
    this->setWindowTitle(tr("Select person"));

    this->fill();

    connect(&_buAddPerson, &QPushButton::released, this, &DialogAssignPerson::addClicekd);
    connect(&_buSelectPerson, &QPushButton::released, this, &DialogAssignPerson::selectClicked);
    connect(_buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::released, this, &DialogAssignPerson::reject);
    connect(_table, &PersonList::doubleClicked, this, &DialogAssignPerson::doubleClickAccept);

    _lineSearch.setFocus();
}

DialogAssignPerson::~DialogAssignPerson()
{
    delete _buttonBox;
    delete _table;
}

int DialogAssignPerson::getSelectedId(Identifier& ref)
{
    int result = this->exec();
    ref = _selectedRef;
    return result;
}

void DialogAssignPerson::fill()
{
    // Initialize
    Identifier selected;
    if(! _people.isEmpty())
    {
        selected = _people.first();
    }
    _table = new PersonList(_kernel, selected);
    _table->update(_people);

    _buttonBox = new QDialogButtonBox(QDialogButtonBox::StandardButton::Cancel);

    // Set static text
    _buAddPerson.setText(tr("New Person"));
    _buSelectPerson.setText(tr("Select Person"));

    // Adjust items
    _table->selectFirst();
    _buSelectPerson.setEnabled(_table->count() != 0);

    // Connect
    connect(&_lineSearch, &QLineEdit::textEdited, _table, &PersonList::selectLine);

    _layout.addWidget(&_lineSearch, 0, 0, 1, 3);
    _layout.addWidget(_table, 1, 0, 1, 3);
    _layout.addWidget(&_buAddPerson, 2, 0);
    _layout.addWidget(&_buSelectPerson, 2, 1);
    _layout.addWidget(_buttonBox, 2, 2);
}

int DialogAssignPerson::exec()
{
    return QDialog::exec();
}

void DialogAssignPerson::doubleClickAccept(const QModelIndex &i)
{
    Q_UNUSED(i);

    this->selectClicked();
}

void DialogAssignPerson::addClicekd()
{
    _selectedRef = Identifier();
    this->accept();
}

void DialogAssignPerson::selectClicked()
{
    _selectedRef = _table->getCurrent();
    this->accept();
}

