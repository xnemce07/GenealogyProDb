/*!
 *  \file   splitter.h
 *  \author Eva Navratilova
 */

#ifndef SPLITTER_H
#define SPLITTER_H

#include <QSplitter>
#include <QSplitterHandle>
#include <QVBoxLayout>
#include <QFrame>

class Splitter : public QSplitter
{
    Q_OBJECT
private:
    QVector<QVBoxLayout*> _layouts;
    QVector<QSplitterHandle*> _handles;
    QVector<QFrame*> _lines;

public:
    Splitter(QWidget* parent = nullptr);
    ~Splitter() override;

    void decorate();
};

#endif // SPLITTER_H
