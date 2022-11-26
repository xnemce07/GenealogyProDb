/*!
 *  \file   datevalidator.h
 *  \author Eva Navratilova
 */

#ifndef DATEVALIDATOR_H
#define DATEVALIDATOR_H

#include <QValidator>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "kernel.h"
#include "textformatter.h"

class DateValidator : public QValidator
{
public:
    DateValidator();

    void fixup(QString &input) const override;
    State validate(QString &input, int &pos) const override;
};

#endif // DATEVALIDATOR_H
