/*!
 *  \file   label.h
 *  \author Eva Navratilova
 */

#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QFont>
#include <QFontMetrics>

class Label : public QLabel
{
    Q_OBJECT
public:
    Label();

public slots:
    void setText(const QString &text);
};

#endif // LABEL_H
