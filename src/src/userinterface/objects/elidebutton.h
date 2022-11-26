/*!
 *  \file   elidebutton.h
 *  \author Eva Navratilova
 */

#ifndef ELIDEBUTTON_H
#define ELIDEBUTTON_H

#include <QPainter>

#include "narrowbutton.h"

class ElideButton : public NarrowButton
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(bool isElided READ isElided)
private:
    bool _elided = false;
    QString _content;

public:
    ElideButton(QWidget *parent = nullptr);
    ~ElideButton() = default;

public slots:
    void setText(const QString &text);
    const QString &text() const { return _content; }

    bool isElided() const { return _elided; }

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // ELIDEBUTTON_H
