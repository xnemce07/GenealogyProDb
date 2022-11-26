/*!
 *  \file   action.h
 *  \author Eva Navratilova
 */

#ifndef ACTION_H
#define ACTION_H

#include <QAction>

#include "../../kernel.h"
#include "userinterface/objects/translatableobject.h"

class Action : public QAction, public TranslatableObject
{
    Q_OBJECT
public:
    Action(QWidget *parent = nullptr);
    virtual ~Action() override = default;
    void enable();
    void disable();
    virtual void translate() override = 0;

signals:
    void probandChanged(Identifier ref);

protected slots:
    void triggerAction(bool checked);
    virtual void process() = 0;
};

#endif // ACTION_H
