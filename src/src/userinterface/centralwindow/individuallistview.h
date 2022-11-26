#ifndef INDIVIDUALLISTVIEW_H
#define INDIVIDUALLISTVIEW_H

#include <QTableWidget>
#include <QHeaderView>
#include <QSettings>
#include <QStringList>
#include <QCollator>

#include "../../kernel.h"
#include "listview/tablecellref.h"
#include "listview/tablecelltext.h"
#include "listview/tablecelldate.h"

class IndividualListView : public QTableWidget
{

    Q_OBJECT

public:
    IndividualListView(Kernel &k);

    void saveSettings();

signals:
    void probandChanged(Identifier ref);

public slots:
    void columnHeaderClicked(int index);
    void individualDoubleClicked(int row, int col);

    // TODO - updates

private:
    Kernel &_kernel;

    QVector<QVector <TableCell *> > _items;

};

#endif // INDIVIDUALLISTVIEW_H
