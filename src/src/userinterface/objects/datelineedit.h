/*!
 *  \file   datelineedit.h
 *  \author Eva Navratilova
 */

#ifndef DATELINEEDIT_H
#define DATELINEEDIT_H

#include <QLineEdit>

#include "datevalidator.h"
#include "userinterface/dialogs/messageboxes/messagebox.h"

class DateLineEdit : public QLineEdit
{
    Q_OBJECT
private:
    DateValidator _validator;
    MessageBox *_message = nullptr;

public:
    DateLineEdit();

private:
    Date getDate() const;

signals:
    void dateChanged(const Date date);

private slots:
    void changeDate();
    void focusOutEvent(QFocusEvent *event) override;
};

#endif // DATELINEEDIT_H
