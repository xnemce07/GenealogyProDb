/**
* Copyright 2017 Charles Glancy (charles@glancyfamily.net)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction, including  without limitation the rights to use, copy,
* modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
* is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef CGGEDCOM_ANSELCODEC_H
#define CGGEDCOM_ANSELCODEC_H
#pragma once

#include "cggedcom.h"
#include <QTextCodec>

namespace cg
{
    class CGGEDCOM_API AnselCodec : public QTextCodec
    {
    public:
        AnselCodec();
        ~AnselCodec();

        QByteArray name() const;
        QList<QByteArray> aliases() const;
        int mibEnum() const;

    protected:
        QString convertToUnicode(const char *chars, int len, ConverterState *state) const;
        QByteArray convertFromUnicode(const QChar *input, int number, ConverterState *state) const;

    private:
        ushort anselToUnicode(uchar ansel) const;
        ushort anselToUnicode2(uchar first, uchar second) const;
        ushort unicodeToAnsel(ushort unicode) const;
    };
}

#endif // CGGEDCOM_ANSELCODEC_H
