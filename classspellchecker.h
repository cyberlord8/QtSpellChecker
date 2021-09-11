/*
 * Copyright 2019 Green Radio Software Solutions (GRSS)
 * Released under GPL3 License
 * QtSpellChecker - A spell check library written in Qt

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */

#ifndef CLASSSPELLCHECKER_H
#define CLASSSPELLCHECKER_H

#include <QDebug>

#include <QObject>
#include <QSet>
#include <QFile>
#include <QStringList>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QByteArray>
#include <QRegExp>
#include <QTextDocument>
#include <QTextCursor>
#include <QCursor>
#include <QMenu>
#include <QPoint>
#include <QPlainTextEdit>
#include <QApplication>

#include "highlighter.h"

class ClassSpellChecker : public QObject
{
    Q_OBJECT
    QSet<QString> dictionary;
    QStringList ignoreWordsList;
    QFile *dictionaryFile;
    QTextDocument *textDocument;
    QPlainTextEdit *textEditor;
    Highlighter *spellCheckHighlighter;
    bool isSpellCheckerValid = false;
    bool isRehighlighting = false;
    bool parseDictionaryFile(QFile *dictionaryFile);
    QMap<QString, QStringList> substituteWords;
    bool writeWordsToDictionary(QStringList wordList);
    bool isContraction(QString word);
    bool isNumber(QString word);
    bool allowRecursion = true;

    QStringList findSubstituteWords(QString word);
    bool IsCapitalized(QString word);
    bool IsMixedCase(QString word);

public:
    explicit ClassSpellChecker(bool allowRecursion,
                               QFile *dictionaryFile,
                               QPlainTextEdit *textEditor,
                               QObject *parent = nullptr);
    ~ClassSpellChecker();

    bool isValid();//did ClassSpellChecker initialize OK?
    bool addWordtoDictionary(QString word);
    bool addWordtoDictionary(QStringList wordList);
    void createContextMenu(const QPoint &pos);

    //spellCheck returns a map of words not found in the dictionary and a list of possible substitutes
    QMap<QString, QStringList> spellCheck(QStringList wordList, bool clearLists);
    QMap<QString, QStringList> spellCheck(QString words, bool clearLists);

    bool getIsRehighlighting() const;
    void setIsRehighlighting(bool value);

signals:

public slots:

private slots:
    void slotOpenEditor();

};

#endif // CLASSSPELLCHECKER_H
