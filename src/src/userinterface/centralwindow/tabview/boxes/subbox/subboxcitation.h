/*!
 *  \file   subboxcitation.h
 *  \author Eva Navratilova
 */

#ifndef SUBBOXCITATION_H
#define SUBBOXCITATION_H

#include <QComboBox>
#include <QLineEdit>
#include <QFrame>
#include <QUrl>
#include <QDebug>

#include "subbox.h"
#include "subboxsimple.h"
#include "subboxweb.h"
#include "userinterface/objects/comboboxnarrow.h"
#include "userinterface/dialogs/messageboxes/messagebox.h"

class SubboxCitation : public Subbox
{
    Q_OBJECT
private:
    QVector<Identifier> _sources;
    Identifier _source;

    //QFrame _hline;

    Label _laSource;

    ComboBoxNarrow _comboSource;
    NarrowButton _buAddSource;
    NarrowButton _buGotoSource;

    SubboxSimple *_subboxPage;
    SubboxWeb* _subboxWeb;

    QSpacerItem *_spacer;

public:
    SubboxCitation(QWidget *parent = nullptr);

    /**
     * @brief Updates user-changeable values in subbox
     *
     * @param srcIndex  Index of currently selected source in source
     *                  if no source selected -1
     */
    void update(Kernel &k, CommonEventType t, const QString plac, QVector<Identifier> source, Identifier srcRef, QString page, QString url);
    void setEnabled(bool enabled);

    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

private:
    void fill() override;
    void remove();

    void setEnabledEdit(bool enabled = true);


signals:
    void sourceChanged(const Identifier ref);
    void pageChanged(const QString text);
    void urlChanged(const QString text);

    void updateCombo();

    void addSource();
    void gotoSource(const Identifier &src);

private slots:
    void changeSource(int index);
    void addSourceClicked(bool checked);
    void gotoSourceClicked(bool checked);
};

#endif // SUBBOXCITATION_H
