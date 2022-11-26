/*!
 *  \file   narrowbutton.h
 *  \author Eva Navratilova
 */

#ifndef NARROWBUTTON_H
#define NARROWBUTTON_H

#include <QPushButton>
#include <QSizePolicy>
#include <QFont>
#include <QFontMetrics>

class NarrowButton : public QPushButton
{
    Q_OBJECT
public:
    NarrowButton(QWidget *parent = nullptr);
    virtual ~NarrowButton() = default;

public slots:
    void setText(const QString &text);
};

#endif // NARROWBUTTON_H
