/*!
 *  \file   completerinline.cpp
 *  \author Eva Navratilova
 */

#include "completerinline.h"

CompleterInline::CompleterInline(const QStringList &list, QObject *parent)
    : QCompleter (list, parent)
{
    this->setCompletionMode(QCompleter::CompletionMode::InlineCompletion);
    this->setCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
}

