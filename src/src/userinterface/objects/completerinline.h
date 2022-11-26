/*!
 *  \file   completerinline.h
 *  \author Eva Navratilova
 */

#ifndef COMPLETERINLINE_H
#define COMPLETERINLINE_H

#include <QCompleter>

class CompleterInline : public QCompleter
{
public:
    CompleterInline(const QStringList &list, QObject *parent = nullptr);
};

#endif // COMPLETERINLINE_H
