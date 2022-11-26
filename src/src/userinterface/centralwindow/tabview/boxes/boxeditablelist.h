/*!
 *  \file   boxeditablelist.h
 *  \author Eva Navratilova
 */

#ifndef BOXEDITABLELIST_H
#define BOXEDITABLELIST_H

#include <QListWidget>
#include <QPushButton>

#include "box.h"
#include "../../../dialogs/data/dialogeditable.h"
#include "../../../dialogs/messageboxes/messagedelete.h"

class BoxEditableList : public Box
{
    Q_OBJECT
protected:
    DialogEditable *_dialogEdit;
    MessageDelete *_dialogDelete;

protected:
    QListWidget _list;

    QPushButton _buNew;
    QPushButton _buEdit;
    QPushButton _buDelete;

    QPushButton _buUp;
    QPushButton _buDown;

public:
    BoxEditableList(QString title, Kernel &k, Identifier &p, QWidget *parent = nullptr);

    virtual void update() = 0;

private:
    void fill();

    virtual void swapIndexes(unsigned int index1, unsigned int index2) = 0;

protected:
    virtual void remove();

private slots:
    void clickAddButton(bool clicked);
    void clickEditButton(bool clicked);
    void clickDeleteButton(bool clicked);
    void clickUpButton(bool clicked);
    void clickDownButton(bool clicked);
    void listRowChanged(int row);
    void doubleClickItem(QListWidgetItem *item);
    void moveRows(const QModelIndex& sourceParent, int sourceStart, int sourceEnd, const QModelIndex& destinationParent, int destinationRow);

protected slots:
    virtual void clickAdd() = 0;
    virtual void clickEdit(unsigned int index) = 0;
    virtual void clickDelete(unsigned int index) = 0;
};

#endif // BOXEDITABLELIST_H
