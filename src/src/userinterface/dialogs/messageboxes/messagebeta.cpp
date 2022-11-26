/*!
 *  \file   messagebeta.cpp
 *  \author Eva Navratilova
 */

#include "messagebeta.h"

MessageBeta::MessageBeta(QWidget *parent, Qt::WindowFlags f)
    : MessageBox(QMessageBox::Warning,
                  tr("Warning"),
                  tr("THIS IS A BETA VERSION.\n"
                     "PLEASE MAKE SURE TO BACKUP YOUR DATA BEFORE USING THIS APPLICATION."

                     /*"\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS"
                     "OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
                     "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL "
                     "THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
                     "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, "
                     "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS "
                     "IN THE SOFTWARE."*/

                     ),
                  QMessageBox::Ok | QMessageBox::Close,
                  QMessageBox::Ok,
                  parent,
                  f)
{
    this->setDefaultButton(QMessageBox::Close);

    this->initCheckBox();

    connect(this->button(Ok), &QAbstractButton::released, this, &MessageBeta::accept);
    connect(this->button(Close), &QAbstractButton::released, this, &MessageBeta::reject);
    // Invalid null parameter Escape - connect(this->button(Escape), &QAbstractButton::released, this, &MessageBeta::reject);
}

void MessageBeta::accept()
{
    QSettings settings;

    QMessageBox::accept();

    settings.setValue("message/beta/dontShow", _dontShow.checkState() == Qt::Checked);
}

void MessageBeta::initCheckBox()
{
    QSettings settings;

    _dontShow.setText(tr("Don't show again"));
    _dontShow.setCheckable(true);
    _dontShow.setChecked(settings.value("message/beta/dontShow").toBool());
    _dontShow.setTristate(false);
    this->setCheckBox(&_dontShow);
}
