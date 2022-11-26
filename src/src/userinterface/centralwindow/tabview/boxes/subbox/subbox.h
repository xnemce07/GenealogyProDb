/*!
 *  \file   subbox.h
 *  \author Eva Navratilova
 */

#ifndef SUBBOX_H
#define SUBBOX_H

#include <QWidget>
#include <QGridLayout>

#include "userinterface/objects/label.h"
#include "userinterface/objects/sizer.h"
#include "userinterface/objects/labelwidthadjuster.h"
#include "kernel.h"
#include "textformatter.h"

class Subbox : public QWidget, public Sizer, public LabelWidthAdjuster
{
    Q_OBJECT
protected:
    QGridLayout _layout;

public:
    explicit Subbox(QWidget *parent = nullptr);
    virtual ~Subbox() = default;

protected:
    virtual void fill() = 0;

signals:

public slots:
};

#endif // SUBBOX_H
