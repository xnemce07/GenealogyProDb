/*!
 *  \file   list.h
 *  \author Eva Navratilova
 */

#ifndef LIST_H
#define LIST_H

#include <QListWidget>
#include <QItemSelectionModel>
#include <QVector>

#include "kernel.h"
#include "listitem.h"

class List : public QListWidget
{
    Q_OBJECT
protected:
    Kernel &_kernel;
    Identifier &_ref;
    QVector<Identifier> _refs;

    QVector<ListItem*> _items;

public:
    List(Kernel &k, Identifier &ref, QWidget *parent = nullptr);
    virtual ~List();

    Identifier getCurrent();
    void update(QVector<Identifier> refs);

protected:
    virtual ListItem* initialize(Identifier ref) = 0;

    void remove();
    void restore(bool hide);

signals:
    void itemChanged(Identifier ref);
    void selectedChanged(Identifier ref);

public slots:
    void itemClicked(const QModelIndex &index);
    void changeSelected(ListItem *item);
    void selectFirst();
    void selectLine(const QString &text);
};

#endif // LIST_H
