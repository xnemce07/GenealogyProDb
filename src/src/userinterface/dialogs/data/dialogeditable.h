/*!
 *  \file   dialogeditable.h
 *  \author Eva Navratilova
 */

#ifndef DIALOGEDITABLE_H
#define DIALOGEDITABLE_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>

#include "userinterface/dialogs/dialog.h"
#include "userinterface/objects/labelwidthadjuster.h"
#include "../../centralwindow/tabview/boxes/subbox/subboxdate.h"
#include "../../centralwindow/tabview/boxes/subbox/subboxsimple.h"


class DialogEditable : public Dialog
{
    Q_OBJECT
protected:
    SubboxDate *_subboxDate = nullptr;

    DateType &_datetype;
    Date &_date1;
    Date &_date2;

public:
    DialogEditable(const QString title, DateType &datetype, Date &date1, Date &date2, QWidget *parent = nullptr);
    virtual ~DialogEditable() override;

private:
    virtual void fill() override = 0;

private slots:
    void changeDateType(const DateType datetype);
    void changeDate1(const Date date);
    void changeDate2(const Date date);

};

#endif // DIALOGEDITABLE_H
