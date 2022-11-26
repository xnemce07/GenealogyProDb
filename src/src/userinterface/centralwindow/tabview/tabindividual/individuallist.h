/*!
 *  \file   individuallist.h
 *  \author Eva Navratilova
 */

#ifndef INDIVIDUALLISTVIEW_H
#define INDIVIDUALLISTVIEW_H

#include <QTableWidget>
#include <QHeaderView>
#include <QSettings>
#include <QStringList>
#include <QCollator>
#include <QFontMetrics>

#include "kernel.h"
#include "listview/tablecellref.h"
#include "listview/tablecelltext.h"
#include "listview/tablecelldate.h"

class IndividualList : public QTableWidget
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_proband;

    QVector<QVector <TableCell *> > _items;
    QVector<int> _columnClickedMemory;

    const QFont _defaultFont;
    const int   _cellPadding = 0;
public:
    IndividualList(Kernel &k, Identifier &p, QWidget *parent = nullptr);
    ~IndividualList() override;

    static void defaultSettings();
    void saveSettings() const;

signals:
    void probandChanged(Identifier ref);


public slots:
    void columnHeaderClicked(int index);
    void individualClicked(int row, int col);
    void update();
    void remove();

    // TODO - updates

private:
    void fill();
    void applySettings();
    void sortByColumnHeader(int index);
    void saveColumnSorting(int index);
    void restoreColumnSorting();

};

#endif // INDIVIDUALLISTVIEW_H
