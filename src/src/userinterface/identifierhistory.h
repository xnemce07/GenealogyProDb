/*!
 *  \file   identifierhistory.h
 *  \author Eva Navratilova
 */

#ifndef IDENTIFIERHISTORY_H
#define IDENTIFIERHISTORY_H

#include <QVector>

#include "../kernel.h"

class IdentifierHistory : public QObject
{
    Q_OBJECT
private:
    QVector<Identifier> _identifiers;
    int _index; /**< Stores index of next item to be added -> ie. current is equal to (_index-1) */
    const int _maxLength;

public:
    IdentifierHistory(int maxLength);
    virtual ~IdentifierHistory();

    void reset();

private:
    int currentIndex() const;

signals:
    void probandChanged(const Identifier ref);
    void updated();

public slots:
    bool isPreviousAvailable() const;
    bool isNextAvailable() const;

    void previous();
    void next();

    void update(Identifier ref);
    void remove(Identifier ref);

};

#endif // IDENTIFIERHISTORY_H
