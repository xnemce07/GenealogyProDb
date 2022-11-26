/*!
 *  \file   subboxpersonref.h
 *  \author Eva Navratilova
 */

#ifndef SUBBOXPERSONREF_H
#define SUBBOXPERSONREF_H

#include <QCollator>

#include "subbox.h"
#include "userinterface/objects/comboboxnarrow.h"
#include "userinterface/objects/elidebutton.h"
#include "userinterface/objects/narrowbutton.h"
#include "../../../../../textformatter.h"
#include "../../../../../kernel.h"
#include "../../../../dialogs/messageboxes/messagedelete.h"

class SubboxPersonRef : public Subbox
{
    Q_OBJECT
private:
    Kernel &_kernel;
    QVector<Identifier> _individuals;

    QString _textLabel;
    Date _date;
    Identifier _ref;

    Label _laPerson;
    ElideButton _buPerson;
    NarrowButton _buRemove;


    MessageDelete *_dialogDelete;

public:
    explicit
    SubboxPersonRef(const QString title, Kernel &k, QWidget* parent = nullptr);

    void update(Identifier ref);

    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

private:
    void fill() override;
    void remove();

signals:
    void probandChanged(Identifier ref);
    void addClicked();
    void removeClicked();

private slots:
    void clickPerson(bool checked);
    void clickRemove(bool checked);

};

#endif // SUBBOXPERSONREF_H
