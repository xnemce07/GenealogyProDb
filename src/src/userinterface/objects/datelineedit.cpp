/*!
 *  \file   datelineedit.cpp
 *  \author Eva Navratilova
 */

#include "datelineedit.h"

DateLineEdit::DateLineEdit()
{    
    this->setValidator(&_validator);

    connect(this, &DateLineEdit::textEdited, this, &DateLineEdit::changeDate);
}

Date DateLineEdit::getDate() const
{
    return TextFormatter::dateFromText(this->text());
}

void DateLineEdit::changeDate()
{
    if(this->hasAcceptableInput())
    {
        this->setStyleSheet("color: black;");
        emit(this->dateChanged(this->getDate()));
    }
    else
    {
        this->setStyleSheet("color: red;");
    }
}

void DateLineEdit::focusOutEvent(QFocusEvent *event)
{
    if(!this->hasAcceptableInput())
    {
        if(_message == nullptr)
        {
            _message = new MessageBox(MessageBox::Icon::Warning,
                               tr("Invalid date"),
                               tr("The date entry is not valid.\n"
                                  "\n"
                                  "Please modify the date in accordance to the formats:\n"
                                  "d.m.yyyy\n"
                                  "m.yyyy\n"
                                  "yyyy\n"
                                  "\n"
                                  "Valid example: 1.12.1900"),
                               MessageBox::StandardButton::Ok,
                               MessageBox::StandardButton::Ok);
            _message->exec();
            _message->deleteLater();
            _message = nullptr;
            this->setFocus();
        }
    }
    else
    {
        QLineEdit::focusOutEvent(event);
    }
}
