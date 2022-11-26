/*!
 *  \file   subboxweb.cpp
 *  \author Eva Navratilova
 */

#include "subboxweb.h"

SubboxWeb::SubboxWeb(QString title, QWidget *parent)
    : Subbox(parent)
{
    _textLabel = title;

    this->fill();

    connect(&_lineUrl, &QLineEdit::textEdited, this, &SubboxWeb::changeUrl);
    connect(&_lineUrl, &QLineEdit::textChanged, this, &SubboxWeb::changeUrlButtonState);
    connect(&_buUrl, &QPushButton::clicked, this, &SubboxWeb::openUrl);
}

void SubboxWeb::update(const QString &url)
{
    _lineUrl.setText(url);
}

void SubboxWeb::setEnabled(bool enabled)
{
    _laUrl.setEnabled(enabled);
    _lineUrl.setEnabled(enabled);
    this->changeUrlButtonState(_lineUrl.text());
}

int SubboxWeb::maxLabelWidth() const
{
    QFont font;
    QFontMetrics metrics(font);
    return metrics.horizontalAdvance(_laUrl.text());
}

void SubboxWeb::setLabelsWidth(int width)
{
    _laUrl.setFixedWidth(width);
}

void SubboxWeb::fill()
{
    // Set static values
    _laUrl.setText(_textLabel);
    _buUrl.setIcon(QIcon(":/icons/web"));
    _buUrl.setToolTip(tr("View page in the browser"));
    _buUrl.setCursor(Qt::CursorShape::PointingHandCursor);

    // Adjust widgets
    _buUrl.setDisabled(true);

    // Set layout
    _layout.addWidget(&_laUrl, 0, 0, Qt::AlignVCenter | Qt::AlignRight);
    _layout.addWidget(&_lineUrl, 0, 1);
    _layout.addWidget(&_buUrl, 0, 2);
}

void SubboxWeb::changeUrl()
{
    QString text = _lineUrl.text();
    emit(this->urlChanged(text));
}

void SubboxWeb::changeUrlButtonState(const QString &text)
{
    QUrl url = QUrl::fromUserInput(text);
    _buUrl.setEnabled(url.isValid());
}

void SubboxWeb::openUrl(bool checked)
{
    Q_UNUSED(checked);

    QString urlText = _lineUrl.text();
    _url.setUrl(urlText);
    if(!urlText.isEmpty())
    {
        QDesktopServices::openUrl(_url);
    }
}
