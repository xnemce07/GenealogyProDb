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
#include "gedcomparser.h"
#include "gedcomnode.h"
#include "anselcodec.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>
#include <QStack>

namespace cg
{
    GedcomParser::GedcomParser()
        : _rootNode(nullptr)
    {

    }

    GedcomParser::~GedcomParser()
    {
        clear();
    }

    void GedcomParser::clear()
    {
        _nodeMap.clear();

        if (_rootNode)
        {
            delete _rootNode;
            _rootNode = nullptr;
        }
    }

    bool GedcomParser::getEncoding(const QString &filename, QString &correctedEncoding, QString &source)
    {
        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }

        QTextStream in(&file);

        QString encoding;
        QString version;

        for (int i = 0;  !in.atEnd(); i++)
        {
            QString line = in.readLine();
            QStringList split = line.split(QRegularExpression("\\s+"));
            if (split.length() == 3)
            {
                if (source.isEmpty() && split[0] == "1" && split[1] == "SOUR")
                {
                    source = split[2];
                }
                else if (split[0] == "1" && (split[1] == "CHAR" || split[1] == "CHARACTER"))
                {
                    encoding = split[2].toUpper();

                    line = in.readLine();
                    split = line.split(QRegularExpression("\\s+"));

                    if (split.length() == 3 && split[0] == "2" && split[1] == "VERS")
                    {
                        version = split[2];
                    }
                }
            }

            if (!source.isEmpty() && !encoding.isEmpty())
                break;
        }

        file.close();

        // default is ANSEL
        if (!encoding.isEmpty())
            encoding = "ANSEL";

        correctedEncoding = getCorrectedEncoding(source, encoding, version);
        return true;
    }

    QString GedcomParser::getCorrectedEncoding(const QString &source, const QString &sourceEncoding, const QString &version)
    {
        QString encoding = sourceEncoding;

        // correct incorrectly-assigned encoding values
        if ("GeneWeb" == source && "ASCII" == encoding) {
            // GeneWeb ASCII -> Cp1252 (ANSI)
            encoding = "Windows-1252";
        }
        else if ("Geni.com" == source && "UNICODE" == encoding) {
            // Geni.com UNICODE -> UTF-8
            encoding = "UTF-8";
        }
        else if ("Geni.com" == source && "ANSEL" == encoding) {
            // Geni.com ANSEL -> UTF-8
            encoding = "UTF-8";
        }
        else if ("GENJ" == source && "UNICODE" == encoding) {
            // GENJ UNICODE -> UTF-8
            encoding = "UTF-8";
        }

        // make encoding value qt-friendly
        else if ("ASCII" == encoding) { // ASCII followed by VERS MacOS Roman is MACINTOSH
            if ("MacOS Roman" == version) {
                encoding = "Apple Roman";
            }
        }
        else if ("ATARIST_ASCII" == encoding) {
            encoding = "ASCII";
        }
        else if ("MACROMAN" == encoding || "MACINTOSH" == encoding) {
            encoding = "Apple Roman";
        }
        else if ("ANSI" == encoding || "IBM WINDOWS" == encoding) {
            encoding = "Windows-1252";
        }
        else if ("WINDOWS-874" == encoding) {
            encoding = "IBM 874";
        }
        else if ("WINDOWS-1251" == encoding) {
            encoding = "Windows-1251";
        }
        else if ("WINDOWS-1254" == encoding) {
            encoding = "Windows-1254";
        }
        else if ("IBMPC" == encoding || "IBM DOS" == encoding) {
            encoding = "IBM 850";
        }
        else if ("UNICODE" == encoding) {
            encoding = "UTF-16";
        }

        return encoding;
    }

    void GedcomParser::parse(const QString &filename)
    {
        QString encoding, source;
        if (!getEncoding(filename, encoding, source))
        {
            // error
            return;
        }

        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            // error
            return;
        }

        clear();
        _rootNode = new GedcomNode();

        QStack<GedcomNode*> nodeStack;
        nodeStack.push(_rootNode);

        QTextStream in(&file);

        if (encoding == "ANSEL")
        {
            // an AnselCodec object needs to have been created on the heap (i.e. new AnselCodec)
            QTextCodec *anselCodec = QTextCodec::codecForName("ANSEL");
            Q_ASSERT(anselCodec);
            if (anselCodec)
                in.setCodec(anselCodec);
        }

        QRegularExpression lineExpression("^\\s*(\\d)\\s+(@([^@ ]+)@\\s+)?(\\w+)(\\s+@([^@ ]+)@)?(\\s(.*))?$");

        while (!in.atEnd())
        {
            QString line = in.readLine();
            QRegularExpressionMatch match = lineExpression.match(line);
            if (match.isValid())
            {
                int level = match.captured(1).toInt();
                QString id = match.captured(3);
                QString tag = match.captured(4);
                QString xref = match.captured(6);
                QString value = match.captured(8);

                GedcomNode *node = new GedcomNode(tag, id, xref, value);
                _nodeMap.insert(id, node);

                while (nodeStack.count() > level + 1)
                    nodeStack.pop();

                nodeStack.top()->addChild(node);
                nodeStack.push(node);
            }
            else
            {
                qDebug() << "Error: Unable to parse line \"" << line << "\"";
            }
        }

        file.close();
    }

    GedcomNode * GedcomParser::rootNode() const
    {
        return _rootNode;
    }

    GedcomNode * GedcomParser::node(const QString &id) const
    {
        return _nodeMap.value(id);
    }

    GedcomParser::NodeList GedcomParser::nodesWithTag(const QString & tag) const
    {
        NodeList list;

        for (auto & pNode : _nodeMap.values())
        {
            if (pNode->tag() == tag)
                list.append(pNode);
        }

        return list;
    }
}
