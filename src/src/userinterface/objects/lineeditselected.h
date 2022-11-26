/*!
 *  \file   lineeditselected.h
 *  \author Eva Navratilova
 */

#ifndef LINEEDITSELECTED_H
#define LINEEDITSELECTED_H

#include <QLineEdit>
#include <QTimer>

class LineEditSelected : public QLineEdit
{
    Q_OBJECT
public:
    LineEditSelected();

private:
    void focusInEvent(QFocusEvent *e) override;
};

#endif // LINEEDITSELECTED_H
