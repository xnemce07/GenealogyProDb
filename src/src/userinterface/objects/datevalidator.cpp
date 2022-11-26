/*!
 *  \file   datevalidator.cpp
 *  \author Eva Navratilova
 */

#include "datevalidator.h"

DateValidator::DateValidator()
{

}

void DateValidator::fixup(QString &input) const
{
    Q_UNUSED(input);

    // Can contain only dots and digits
    input = input.remove(QRegularExpression("[^\\d\\.]"));

    // Cannot contain more than two dots
    if(input.count(".") > 2)
    {
        input = input.remove(input.lastIndexOf("."), 1);
    }
}

QValidator::State DateValidator::validate(QString &input, int &pos) const
{
    Q_UNUSED(pos);

    this->fixup(input);

    Date d = TextFormatter::dateFromText(input);
    State state = (d.isValid() || input.isEmpty())? State::Acceptable : State::Intermediate;

    return state;
}
