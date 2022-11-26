/*!
 *  \file   boxchildren.h
 *  \author Eva Navratilova
 */

#ifndef BOXCHILDREN_H
#define BOXCHILDREN_H

#include <QListWidget>
#include <QStringList>
#include <QPushButton>

#include "box.h"
#include "userinterface/objects/personlist.h"
#include "userinterface/objects/label.h"
#include "userinterface/objects/narrowbutton.h"

class BoxChildren : public Box
{
    Q_OBJECT
private:
    QVector<Identifier> _children;

    PersonList* _listChildren;

    QPushButton _buAddBoy;
    QPushButton _buAddGirl;
    NarrowButton _buAddChild;
    Label _laCount;


public:
    BoxChildren(QString title, Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update(QVector<Identifier> ch);


signals:
    void newBoy();
    void newGirl();
    void newChild();

private slots:
    void boyClicked(bool checked);
    void girlClicked(bool checked);
    void childClicked(bool checked);

private:
    void fill() override;
    void update() override;
    void remove();
};

#endif // BOXCHILDREN_H
