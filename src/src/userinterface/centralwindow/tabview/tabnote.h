/*!
 *  \file   tabnote.h
 *  \author Eva Navratilova
 */

#ifndef TABNOTE_H
#define TABNOTE_H

#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>

#include "kernel.h"
#include "userinterface/objects/label.h"

class TabNote : public QWidget
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_proband;

    QGridLayout _layout;
    Label _laNote;
    QTextEdit _textNote;

public:
    explicit TabNote(Kernel &k, Identifier &p, QWidget *parent = nullptr);

private:
    void fill();

signals:

public slots:
    void update();
    void noteChanged();

};

#endif // TABNOTE_H
