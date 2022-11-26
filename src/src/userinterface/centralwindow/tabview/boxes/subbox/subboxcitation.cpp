/*!
 *  \file   subboxcitation.cpp
 *  \author Eva Navratilova
 */

#include "subboxcitation.h"

/// TODO - When I add Florians Father, source pages are deleted for some reason!!!!

SubboxCitation::SubboxCitation(QWidget *parent)
    :Subbox (parent)
{
    this->fill();

    _layout.setVerticalSpacing(this->tightSpacing());
    _layout.setHorizontalSpacing(this->mediumSpacing());

    connect(&_comboSource, SIGNAL(currentIndexChanged(int)), this, SLOT(changeSource(int)));
    connect(_subboxPage, &SubboxSimple::textChanged, this, &SubboxCitation::pageChanged);
    connect(_subboxWeb, &SubboxWeb::urlChanged, this, &SubboxCitation::urlChanged);
    connect(&_comboSource, &ComboBoxNarrow::updateCombo, this, &SubboxCitation::updateCombo);

    connect(&_buAddSource, &NarrowButton::clicked, this, &SubboxCitation::addSourceClicked);
    connect(&_buGotoSource, &NarrowButton::clicked, this, &SubboxCitation::gotoSourceClicked);
}

void SubboxCitation::update(Kernel &k, CommonEventType t, const QString plac, QVector<Identifier> source, Identifier srcRef, QString page, QString url)
{
    this->remove();

    _comboSource.blockSignals(true);
    //this->blockSignals(true);

    _sources = source;
    _source = srcRef;

    _comboSource.addItem(tr("No source"));
    // Add items only if place is non-empty!
    if(!plac.isEmpty())
    {
        for(auto it = _sources.begin(); it != _sources.end(); it++)
        {
            /// TODO - check if right
            _comboSource.addItem(TextFormatter::getCitationText(k, *it, t, plac));
        }
    }
    int currentIndex = _sources.indexOf(srcRef) + 1;

    _comboSource.setCurrentIndex(currentIndex);

    // Hide appropriate button
    bool isGotoVisible = (currentIndex > 0);
    _buAddSource.setVisible(!isGotoVisible);
    _buGotoSource.setVisible(isGotoVisible);

    _comboSource.updateWidth();

    _subboxPage->update(page);
    _subboxWeb->update(url);

    //this->blockSignals(false);
    _comboSource.blockSignals(false);
}

void SubboxCitation::setEnabled(bool enabled)
{
    _laSource.setEnabled(enabled);
    _subboxPage->setEnabled(enabled);

    _comboSource.setEnabled(enabled);
    _buAddSource.setEnabled(enabled);
    _buGotoSource.setEnabled(enabled);

    this->setEnabledEdit(enabled);

    if(enabled)
    {
        this->setToolTip("");
    }
    else
    {
        this->setToolTip(tr("Set exact date and place of event before setting a source citation"));
    }
}

void SubboxCitation::fill()
{
    // Initialize
    _spacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    _subboxPage = new SubboxSimple(tr("Page"));
    _subboxWeb = new SubboxWeb();

    // Set static values
    //_hline.setFrameShape(QFrame::HLine);
    //_hline.setFrameShadow(QFrame::Sunken);
    _laSource.setText(tr("Source"));
    _buAddSource.setIcon(QIcon(":icons/add"));
    _buAddSource.setToolTip(tr("Add new source..."));
    _buGotoSource.setIcon(QIcon(":icons/arrow-right"));
    _buGotoSource.setToolTip(tr("Go to source..."));

    // Adjust widgets
    this->adjustLabelsWidth();

    // Set layout
    //_layout.addWidget(&_hline, 0, 0, 1, 3);
    _layout.addWidget(&_laSource, 1, 0, Qt::AlignVCenter | Qt::AlignRight);
    _layout.addWidget(&_comboSource, 1, 1);
    _layout.addWidget(&_buAddSource, 1, 2);
    _layout.addWidget(&_buGotoSource, 1, 2);
    _layout.addWidget(_subboxPage, 2, 0, 1, 3);
    _layout.addWidget(_subboxWeb, 3, 0, 1, 3);
    _layout.addItem(_spacer, 4, 0, 1, 3);

    // Adjust layout
    _layout.setColumnStretch(0, 10);
    _layout.setColumnStretch(1, 1000);
    _layout.setColumnStretch(2, 1);
}

void SubboxCitation::remove()
{
    _comboSource.blockSignals(true);
    _comboSource.clear();
    _comboSource.blockSignals(false);
}

void SubboxCitation::setEnabledEdit(bool enabled)
{
    _subboxPage->setEnabled(enabled);
    _subboxWeb->setEnabled(enabled);
}

int SubboxCitation::maxLabelWidth() const
{
    QFont font;
    QFontMetrics metrics(font);
    QVector<int> widths;
    widths.push_back(metrics.horizontalAdvance(_laSource.text()));
    widths.push_back(_subboxPage->maxLabelWidth());
    widths.push_back(_subboxWeb->maxLabelWidth());
    return *std::max_element(widths.begin(), widths.end());
}

void SubboxCitation::setLabelsWidth(int width)
{
    _laSource.setFixedWidth(width);
    _subboxPage->setLabelsWidth(width);
    _subboxWeb->setLabelsWidth(width);
}

void SubboxCitation::changeSource(int index)
{
    if(index >= 0 && index <= _sources.length())
    {
        bool apply = false;
        bool isSource = (index > 0);

        if(isSource)
        {
            // Update identifier and apply
            apply = true;
            _source = _sources.at(index - 1);
        }
        // If citation deleted and citation was present before
        // -> ask user if really delete citation and data
        else if(_source != Identifier())
        {
            MessageBox message(MessageBox::Icon::Warning,
                               tr("Do you really want to remove the source citation?"),
                               tr("Removing source citation also removes all additional citation data (e.g. page and web).\n"
                                  "\n"
                                  "Do you really want to remove the source citation?"),
                               MessageBox::StandardButton::Yes | MessageBox::StandardButton::No,
                               MessageBox::StandardButton::Yes);
            int procceed = message.exec();
            if(procceed)
            {
                // Remove identifier and apply
                apply = true;
                _source = Identifier();
            }
            else
            {
                // Restore previous data
                _comboSource.blockSignals(true);
                _comboSource.setCurrentIndex(_sources.indexOf(_source) + 1);
                _comboSource.blockSignals(false);
            }
        }

        if(apply)
        {
            // Hide appropriate button
            _buAddSource.setVisible(!isSource);
            _buGotoSource.setVisible(isSource);

            emit(this->sourceChanged(_source));

            this->setEnabledEdit(isSource);
        }
    }
}

void SubboxCitation::addSourceClicked(bool checked)
{
    Q_UNUSED(checked);

    emit(this->addSource());
}

void SubboxCitation::gotoSourceClicked(bool checked)
{
    Q_UNUSED(checked);

    int index = _comboSource.currentIndex();
    if(index > 0)
    {
        Identifier src = _sources.at(index - 1);
        emit(this->gotoSource(src));
    }
}
