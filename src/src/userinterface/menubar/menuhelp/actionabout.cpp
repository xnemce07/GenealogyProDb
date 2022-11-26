/*!
 *  \file   actionabout.cpp
 *  \author Eva Navratilova
 */

#include "actionabout.h"

const char* ActionHelpAbout::_aboutText = QT_TR_NOOP("About ProGenealogy...");

ActionHelpAbout::ActionHelpAbout(QWidget *parent)
    : Action(parent)
{

}

void ActionHelpAbout::translate()
{
    this->setText(tr(_aboutText));
}

void ActionHelpAbout::process()
{
    if(_message == nullptr)
    {
        _message = new MessageBox(MessageBox::Icon::NoIcon,
                                  tr(_aboutText),
                                  tr("<h3>%1 %2</h3>"
                                     "<p>Based on Qt 5.12.3</p>"
                                     "<p>The program is licensed as GNU LGPL v3.0.</p>"
                                     "<p><a href=\"https://www.facebook.com/progenealogy/\">ProGenealogy on Facebook</a></p>"
                                     "<p>The program is provided AS IS with "
                                     "NO WARRANTY OF ANY KIND, INCLUDING "
                                     "THE WARRANTY OF DESIGN, MERCHANTABILITY "
                                     "AND FITNESS FOR A PARTICULAR PURPOSE.</p>")
                                  .arg(APP_NAME).arg(APP_VERS_CURR),
                                  MessageBox::StandardButton::Close);
        _message->exec();
        _message->deleteLater();
        _message = nullptr;
    }
}
