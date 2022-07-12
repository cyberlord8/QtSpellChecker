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

#include "classspellchecker.h"
#include "dialogeditor.h"

#include <QSet>

bool ClassSpellChecker::getIsRehighlighting() const
{
    return isRehighlighting;
}//getIsRehighlighting

void ClassSpellChecker::setIsRehighlighting(bool value)
{
    isRehighlighting = value;
}//setIsRehighlighting

bool ClassSpellChecker::parseDictionaryFile(QFile *dictionaryFile)
{
    if(dictionaryFile->open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream inStream(dictionaryFile);
        QString dictionaryData = inStream.readAll();
        dictionaryData.replace('\r','\n');
        QStringList list = dictionaryData.split('\n', Qt::SkipEmptyParts);
        QSet<QString> dictionary1(list.begin(), list.end());
        this->dictionary = dictionary1;
        dictionaryFile->close();
        return (dictionary.count() > 0);//hopefully true
    }//if file open
    else {
        return (dictionary.count() > 0);//false
    }
}//parseDictionaryFile

QStringList ClassSpellChecker::findSubstituteWords(QString word)
{
    QStringList substituteWords;
    bool isCapitalized = IsCapitalized(word);
    bool isMixedCase = IsMixedCase(word);
    for (int alpha = 97; alpha < 122; ++alpha) {
        QString subWord = word;
        /*************************************************************/
        //add a letter to the begining
        /*************************************************************/
        subWord.prepend(QChar(alpha));
        if(isCapitalized || isMixedCase){
            subWord = subWord.toLower();
            subWord[0] = subWord.at(0).toUpper();
        }
        else {
            subWord = subWord.toLower();
        }

        if(dictionary.contains(subWord.toLower())){
            if(!substituteWords.contains(subWord))
                substituteWords.append(subWord);
        }//if subWord is in dictionary add it to the sub list
        subWord = word;
        /*************************************************************/
        //add a letter to the end
        /*************************************************************/
        subWord.append(QChar(alpha));
        if(isCapitalized || isMixedCase){
            subWord = subWord.toLower();
            subWord[0] = subWord.at(0).toUpper();
        }
        else {
            subWord = subWord.toLower();
        }

        if(dictionary.contains(subWord.toLower())){
            if(!substituteWords.contains(subWord))
                substituteWords.append(subWord);
        }//if subWord is in dictionary add it to the sub list
        /*************************************************************/
        //swap letters in word
        /*************************************************************/
        for (int i = 0; i < word.count(); ++i) {
            subWord = word;
            subWord[i] = QChar(alpha);

            if(isCapitalized || isMixedCase){
                subWord = subWord.toLower();
                subWord[0] = subWord.at(0).toUpper();
            }
            else {
                subWord = subWord.toLower();
            }

            if(dictionary.contains(subWord.toLower())){
                if(!substituteWords.contains(subWord))
                    substituteWords.append(subWord);
            }//if subWord is in dictionary add it to the sub list
        }//for each letter in the word
        /*************************************************************/
        //insert letters in word
        /*************************************************************/
        for (int i = 0; i < word.count(); ++i) {
            subWord = word;
            subWord.insert(i, QChar(alpha));
            if(isCapitalized || isMixedCase){
                subWord = subWord.toLower();
                subWord[0] = subWord.at(0).toUpper();
            }
            else {
                subWord = subWord.toLower();
            }

            if(dictionary.contains(subWord.toLower())){
                if(!substituteWords.contains(subWord))
                    substituteWords.append(subWord);
            }//if subWord is in dictionary add it to the sub list
        }//for each letter in the word
    }//for each letter in the alphabet
    /*************************************************************/
    //check for transposed letters
    /*************************************************************/
    for (int i = 0; i < word.size()-1; ++i) {
        QString subWord = word;
        QChar char1;
        char1 = subWord.at(i);
        subWord[i] = subWord.at(i+1);
        subWord[i+1] = char1;
        if(isCapitalized || isMixedCase){
            subWord = subWord.toLower();
            subWord[0] = subWord.at(0).toUpper();
        }
        else {
            subWord = subWord.toLower();
        }

        if(dictionary.contains(subWord.toLower())){
            if(!substituteWords.contains(subWord))
                substituteWords.append(subWord);
        }//if subWord is in dictionary add it to the sub list
    }//check for transposed letters
    /*************************************************************/
    //check for compound words
    /*************************************************************/
    for (int i = 0; i < word.size()-1; ++i) {
        QString word1, word2;
        word1 = word.left(i+1);
        word2 = word.right(word.size() - i-1);
        if(dictionary.contains(word1.toLower()) && dictionary.contains(word2.toLower())){
            substituteWords.append(word1+" "+word2);
            substituteWords.append(word1+"-"+word2);
        }
    }//check for compound words
    /*************************************************************/
    //check for random letter
    /*************************************************************/
    for (int i = 0; i < word.size(); ++i) {
        QString subWord = word;
        subWord.remove(i,1);
        if(isCapitalized || isMixedCase){
            subWord = subWord.toLower();
            subWord[0] = subWord.at(0).toUpper();
        }
        else {
            subWord = subWord.toLower();
        }

        if(dictionary.contains(subWord.toLower())){
            if(!substituteWords.contains(subWord)){
                substituteWords.append(subWord);
            }
        }
    }//check for random letter

    return substituteWords;
}//findSubstituteWords

bool ClassSpellChecker::IsCapitalized(QString word)
{
    bool isCapitalized = (word.at(0).isUpper() && QString(word).remove(0,1).isLower());
    return  isCapitalized;
}//IsCapatalized

bool ClassSpellChecker::IsMixedCase(QString word)
{
    bool isMixedCase=false;
    bool foundUpper = false, foundLower = false;
    for(int i = 0; i< word.size(); i++){
        if(word.at(i).isUpper())
            foundUpper=true;
        else {
            foundLower=true;
        }
    }//for each letter in word

    isMixedCase = (foundLower && foundUpper);
    return (isMixedCase && word.at(0).isUpper());
}//IsMixedCase

bool ClassSpellChecker::writeWordsToDictionary(QStringList wordList)
{
    wordList.removeAll("");
    wordList.removeAll(" ");

    if(dictionaryFile->open(QIODevice::Append | QIODevice::Text)){
        QTextStream out(dictionaryFile);
        foreach (QString word, wordList) {
            out << word.toLower() << Qt::endl;
            dictionary.insert(word.toLower());
            substituteWords.remove(word);
            ignoreWordsList.removeAll(word);
            spellCheckHighlighter->removeHighlightRule(word);
        }
        dictionaryFile->flush();
        dictionaryFile->close();
        spellCheckHighlighter->rehighlight();
        this->isRehighlighting = true;
        return true;
    }
    else {
        qDebug() << dictionaryFile->errorString();
        return false;
    }
}//writeWordsToDictionary

bool ClassSpellChecker::isContraction(QString word)
{
    if(word.contains('\'')){
        QStringList splitWord = word.split('\'');
        if(splitWord.size() !=2){
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}//isContraction

bool ClassSpellChecker::isNumber(QString word)
{
    if(word.count('0') == word.size()){
//        qDebug() << "Stop";
    }

    if(word.endsWith("th")){
        word.remove("th");
    }
    else if (word.endsWith("nd")) {
        word.remove("nd");
    }
    else if (word.endsWith("rd")) {
        word.remove("rd");
    }
    else if (word.endsWith("st")) {
        word.remove("st");
    }
    else if (word.toLower().endsWith("z")) {
        word.remove(word.size()-1,1);
    }
    double number = word.toDouble();
    return (number > 0);
}//isNumber

ClassSpellChecker::ClassSpellChecker(bool allowRecursion, QFile *dictionaryFile,
                                     QPlainTextEdit *textEditor,
                                     QObject *parent) : QObject(parent)
{
    isSpellCheckerValid = parseDictionaryFile(dictionaryFile);
    this->dictionaryFile = dictionaryFile;
    this->textDocument = textEditor->document();
    this->textEditor = textEditor;
    spellCheckHighlighter = new Highlighter(this->textDocument);
    this->allowRecursion = allowRecursion;
//    this->settings = settings;
}//ClassSpellChecker

ClassSpellChecker::~ClassSpellChecker()
{
    //    qDebug() << "Deleting ClassSpellChecker";
    spellCheckHighlighter->deleteLater();
//    editorDialog->deleteLater();
}//~ClassSpellChecker

bool ClassSpellChecker::isValid()
{
    return (isSpellCheckerValid && (dictionary.count() > 0));//hopefully true
}//isValid

bool ClassSpellChecker::addWordtoDictionary(QString word)
{
    return writeWordsToDictionary(word.split(' ', Qt::SkipEmptyParts));
}//addWordtoDictionary word

bool ClassSpellChecker::addWordtoDictionary(QStringList wordList)
{
    return writeWordsToDictionary(wordList);
}//addWordtoDictionary wordList

void ClassSpellChecker::createContextMenu(const QPoint &pos)
{
    QTextCursor textCursor(this->textEditor->cursorForPosition(pos));
    textCursor.select(QTextCursor::WordUnderCursor);
    QString selectedWord = textCursor.selectedText();

    if(!selectedWord.isEmpty() && substituteWords.contains(selectedWord)){
        QMenu menu;
        QAction *suggestedWords;
        if(substituteWords.value(selectedWord).size() > 0){
            suggestedWords = menu.addAction("Suggested Words");
        }
        else {
            suggestedWords = menu.addAction("No Suggestions");
        }
        suggestedWords->setEnabled(false);

        foreach (QString word, substituteWords.value(selectedWord)) {
            QAction *fixWordAction = menu.addAction(word);
            fixWordAction->setObjectName(word);
        }

        menu.addSeparator();
        QAction *ignoreAllAction = menu.addAction("Ignore all");
        QAction *addWordtoDictionaryAction = menu.addAction("Add to dictionary");

        QAction *action = menu.exec(textEditor->viewport()->mapToGlobal(pos));

        if(action == ignoreAllAction){
            if(!ignoreWordsList.contains(selectedWord))
                ignoreWordsList.append(selectedWord);
            substituteWords.remove(selectedWord);
            spellCheckHighlighter->removeHighlightRule(selectedWord);
            this->isRehighlighting = true;
            QApplication::processEvents();
            spellCheckHighlighter->rehighlight();
            QApplication::processEvents();
        }//ignoreAllAction
        else if (action == addWordtoDictionaryAction) {
            writeWordsToDictionary(selectedWord.split(' ', Qt::SkipEmptyParts));
        }//addWordtoDictionaryAction
        else {
            if(!(action == nullptr)){
                textCursor.beginEditBlock();
                textCursor.removeSelectedText();
                textCursor.insertText(action->objectName());
                textCursor.endEditBlock();
            }//if action is not null
        }//Fix mispelled word
    }//show context menu for misspelled word
    else {
        //        textEditor->createStandardContextMenu()->exec(textEditor->viewport()->mapToGlobal(pos));
        //        QPlainTextEdit * textEditor = static_cast<QPlainTextEdit*>(sender());

        QMenu *editorMenu = textEditor->createStandardContextMenu();
        if(this->allowRecursion){
            QAction *editorOpenEditorAction = editorMenu->addAction("Open Editor");
            //        connect(editorOpenEditorAction, &QAction::triggered,
            //                this, &ClassSpellChecker::slotOpenEditor);
            QAction *selectedAction = editorMenu->exec(textEditor->viewport()->mapToGlobal(pos));
            if(selectedAction == editorOpenEditorAction){
                this->slotOpenEditor();
            }
        }
        else {
            editorMenu->exec(textEditor->viewport()->mapToGlobal(pos));
        }
    }//not a mispelled word
}//createContextMenu

void ClassSpellChecker::slotOpenEditor()
{
    //    qDebug() << "slotOpenEditor";
    DialogEditor * editorDialog = new DialogEditor(this->textEditor, nullptr);
//    qDebug() << this->property("stylesheet").toString();
    editorDialog->setStyleSheet(this->property("stylesheet").toString());
//    DialogEditor * editorDialog = new DialogEditor(this->textEditor,this->textEditor);//this causes duplicate text in preview
    editorDialog->exec();
}//slotOpenEditor

QMap<QString, QStringList> ClassSpellChecker::spellCheck(QStringList wordList, bool clearLists)
{
    if(clearLists){
        substituteWords.clear();
        spellCheckHighlighter->clearHighlightRules();
    }
    QRegularExpression regex("[^A-Za-z0-9']");
    foreach (QString worda, wordList) {
        worda.replace(regex, " ");
        if(!worda.contains(' ')){
            if(!dictionary.contains(worda.toLower()) && worda.size() > 1 && !isNumber(worda)){
                if(!ignoreWordsList.contains(worda)){
                    substituteWords.insert(worda, findSubstituteWords(worda));
                    spellCheckHighlighter->addHighlightRule(worda);
                }
                else {
                    substituteWords.remove(worda);
                    spellCheckHighlighter->removeHighlightRule(worda);
                }
                this->isRehighlighting = true;
                spellCheckHighlighter->rehighlight();
            }
        }//if no whitespace
        else {
            foreach (QString wordb, worda.split(' ', Qt::SkipEmptyParts)) {
                wordb.replace(regex, " ");
                if(!dictionary.contains(wordb.toLower()) && wordb.size() > 1 && !isNumber(wordb)){
                    if(!ignoreWordsList.contains(wordb)){
                        substituteWords.insert(wordb, findSubstituteWords(wordb));
                        spellCheckHighlighter->addHighlightRule(wordb);
                    }
                    else {
                        substituteWords.remove(wordb);
                        spellCheckHighlighter->removeHighlightRule(wordb);
                    }
                }            }//foreach wordb in worda
        }//else split worda into wordb
    }//foreach worda in wordlist
    this->isRehighlighting = true;
    spellCheckHighlighter->rehighlight();
    return substituteWords;
}//spellCheck QStringList

QMap<QString, QStringList> ClassSpellChecker::spellCheck(QString words, bool clearLists)
{
    if(words.isEmpty()){
        return substituteWords;
    }

    if(clearLists){
        substituteWords.clear();
        spellCheckHighlighter->clearHighlightRules();
    }

    QRegularExpression regex("[^A-Za-z0-9']");
    QStringList wordList;
    if(!words.endsWith(' ') && !words.endsWith('.') && !words.endsWith(", ")){
        words.replace(regex, " ");
        wordList = words.split(' ', Qt::SkipEmptyParts);
        if(!wordList.isEmpty()){
            wordList.removeLast();
        }
    }
    else {
        words.replace(regex, " ");
        wordList = words.split(' ', Qt::SkipEmptyParts);
    }
    foreach (QString word, wordList) {
        if(!isContraction(word)){
            if(!dictionary.contains(word.toLower()) && word.size() > 1 && !isNumber(word)){
                if(!ignoreWordsList.contains(word)){
                    substituteWords.insert(word, findSubstituteWords(word));
                    spellCheckHighlighter->addHighlightRule(word);
                }//if we're not ignoring this word
                else {
                    substituteWords.remove(word);
                    spellCheckHighlighter->removeHighlightRule(word);
                }//else we're ignoring the word - remove it from highlighting rules
            }//if word not found in dictionary
        }//if not a contracted word
        else {
            if(word.contains("n't")){
                QStringList wordList = word.split("n't",Qt::SkipEmptyParts);
                if(!dictionary.contains(wordList.first().toLower()) && wordList.first().size() > 1 && !isNumber(word)){
                    if(!ignoreWordsList.contains(wordList.first())){
                        substituteWords.insert(wordList.first(), findSubstituteWords(wordList.first()));
                        spellCheckHighlighter->addHighlightRule(wordList.first());
                    }//if we're not ignoring this word
                    else {
                        substituteWords.remove(wordList.first());
                        spellCheckHighlighter->removeHighlightRule(wordList.first());
                    }//else we're ignoring the word - remove it from highlighting rules
                }//if word not found in dictionary
            }//if words contains n't
            else {
                QStringList wordList = word.split('\'',Qt::SkipEmptyParts);
                if(wordList.isEmpty())
                    continue;
                if(!dictionary.contains(wordList.first().toLower()) && wordList.first().size() > 1 && !isNumber(word)){
                    if(!ignoreWordsList.contains(wordList.first())){
                        substituteWords.insert(wordList.first(), findSubstituteWords(wordList.first()));
                        spellCheckHighlighter->addHighlightRule(wordList.first());
                    }//if we're not ignoring this word
                    else {
                        substituteWords.remove(wordList.first());
                        spellCheckHighlighter->removeHighlightRule(wordList.first());
                    }//else we're ignoring the word - remove it from highlighting rules
                }//if word not found in dictionary

                if(!dictionary.contains(wordList.last().toLower()) && wordList.last().size() > 1 && !isNumber(word)){
                    if(!ignoreWordsList.contains(wordList.last())){
                        substituteWords.insert(wordList.last(), findSubstituteWords(wordList.last()));
                        spellCheckHighlighter->addHighlightRule(wordList.last());
                    }//if we're not ignoring this word
                    else {
                        substituteWords.remove(wordList.last());
                        spellCheckHighlighter->removeHighlightRule(wordList.last());
                    }//else we're ignoring the word - remove it from highlighting rules
                }//if word not found in dictionary
            }//else word does not contain n't
        }//else is a contracted word
    }//for each word
    this->isRehighlighting = true;
    spellCheckHighlighter->rehighlight();
    return substituteWords;
}//spellCheck QString
