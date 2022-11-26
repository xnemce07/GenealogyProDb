/*!
 *  \file   sourcesearchlist.h
 *  \author Eva Navratilova
 */

#ifndef SOURCESEACRHLIST_H
#define SOURCESEACRHLIST_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QListWidget>

#include "../../../../kernel.h"
#include "userinterface/objects/sourcelist.h"
#include "userinterface/objects/narrowbutton.h"
#include "../../../dialogs/messageboxes/messagedelete.h"

class SourceSearchList : public QWidget
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_source;

    QGridLayout _layout;

    QVector<Identifier> _sources;

    NarrowButton _buAdd;
    NarrowButton _buDelete;
    QLineEdit _lineSearch;
    SourceList* _table = nullptr;

public:
    explicit SourceSearchList(Kernel &k, Identifier &s, QWidget *parent = nullptr);

    void update();

private:
    void fill();
    void remove();

signals:
    void sourceChanged(Identifier ref);

private slots:
    void sourceAddClicked(bool checked);
    void sourceRemoveClicked(bool checked);
};

#endif // SOURCESEACRHLIST_H
