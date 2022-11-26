/*!
 *  \file   comboboxnarrow.h
 *  \author Eva Navratilova
 */

#ifndef COMBOBOXNARROW_H
#define COMBOBOXNARROW_H

#include <QComboBox>
#include <QAbstractItemView>
#include <QTableView>
#include <QHeaderView>
#include <QFontMetrics>
#include <QCompleter>
#include <QSettings>

#include "kernel.h"

class ComboBoxNarrow : public QComboBox
{
    Q_OBJECT
private:
    int _minWidth;
    QCompleter _completer;
    QTableView *_comboView;

public:
    ComboBoxNarrow(QWidget *parent = nullptr);

    //void addItem(const QString& text, const Identifier ref);
    //void setItemIdentifier(int index, const Identifier ref);
    //Identifier itemIdentifier(int index);
    void updateWidth();


private:
    int margin() const;
    int minItemLength() const;
    int maxItemLength() const;

    void initializeCompleter();

    void showPopup() override;

signals:
    void updateCombo();

};

#endif // COMBOBOXNARROW_H
