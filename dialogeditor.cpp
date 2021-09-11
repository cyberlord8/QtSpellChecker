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

#include "dialogeditor.h"
#include "ui_dialogeditor.h"

#include "dialogfind.h"
#include "dialogfindreplace.h"

#include "globals.h"

#include <QThread>
#include <QMessageBox>

DialogEditor::DialogEditor(QPlainTextEdit *plaintextEditor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditor)
{
    ui->setupUi(this);

    findDialog = new DialogFind(this);
    connect(findDialog, &DialogFind::signalFindNext,
            this, &DialogEditor::slotFindNext);
    replaceDialog = new DialogFindReplace(this);
    connect(replaceDialog, &DialogFindReplace::signalFindNext,
            this, &DialogEditor::slotFindNext);
    connect(replaceDialog, &DialogFindReplace::signalReplaceText,
            this, &DialogEditor::slotReplaceText);
    connect(replaceDialog, &DialogFindReplace::signalReplaceAllText,
            this, &DialogEditor::slotReplaceAllText);

    this->plaintextEditor = plaintextEditor;
    ui->plainTextEdit->setPlainText(plaintextEditor->toPlainText());
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged,
            this, &DialogEditor::slotPlaintextChanged);
    ui->plainTextEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->plainTextEdit, &QPlainTextEdit::customContextMenuRequested,
            this, &DialogEditor::slotContextMenuRequested);

    QThread * spellCheckerThread;
    QFile *dictionaryFile = new QFile;
    dictionaryFile->setFileName(QApplication::applicationDirPath()+"/../spellchecker/dictionary.txt");
    if(!dictionaryFile->exists()){
        spellCheckerThread = nullptr;
    }
    else {
        spellCheckerThread = new QThread(this);
        spellChecker = new ClassSpellChecker(false, dictionaryFile,ui->plainTextEdit,nullptr);
        if(spellCheckerThread != nullptr){
            spellChecker->moveToThread(spellCheckerThread);
        }
    }

}

DialogEditor::~DialogEditor()
{
    this->spellChecker->deleteLater();
    delete ui;
}

void DialogEditor::slotFindNext(QString textToFind, bool matchCase, bool matchWholeWord, bool reverse)
{
    QTextDocument::FindFlags options;
    if(matchCase)
        options |= QTextDocument::FindCaseSensitively;
    if(matchWholeWord)
        options |= QTextDocument::FindWholeWords;
    if(reverse)
        options |= QTextDocument::FindBackward;

    if(ui->plainTextEdit->find(textToFind, options)){
        this->activateWindow();
    }//if found
    else {
        if(!replaceAll){
            QMessageBox messageBox;
            QString errorString;
            messageBox.setWindowTitle("Not Found!");
            if(reverse){
                errorString = "Reached start of document, \""+textToFind+"\" not found.";
            }
            else {
                errorString = "Reached end of document, \""+textToFind+"\" not found.";
            }
            messageBox.setText(errorString);
            messageBox.exec();
        }
        else {
            QMessageBox messageBox;
            QString errorString;
            messageBox.setWindowTitle("Replace text");
            errorString = "Replaced "+QString::number(numberReplacements)+" occurances of \""+textToFind+"\"";
            messageBox.setText(errorString);
            messageBox.exec();

            if(reverse)
                atStart = true;
            else {
                atEnd = true;
            }
        }
    }//else not found
}

void DialogEditor::slotReplaceText(QString textToReplace, QString replacementText,
                                   bool matchCase, bool matchWholeWord, bool reverse)
{
    if(ui->plainTextEdit->textCursor().hasSelection()){
        ui->plainTextEdit->textCursor().insertText(replacementText);
        if(replaceAll){
            numberReplacements++;
        }
        else {
            slotFindNext(textToReplace,matchCase,matchWholeWord,reverse);
        }
    }
    else {
        //        qDebug() << "No selection";
        return;
    }
}

void DialogEditor::slotReplaceAllText(QString textToReplace, QString replacementText, bool matchCase, bool matchWholeWord, bool reverse)
{
    atStart = atEnd = false;
    replaceAll = true;
    numberReplacements = 0;
    if(reverse){
        while (!atStart) {
            slotFindNext(textToReplace, matchCase, matchWholeWord, reverse);
            slotReplaceText(textToReplace, replacementText, matchCase, matchWholeWord, reverse);
        }
    }
    else {
        while (!atEnd) {
            slotFindNext(textToReplace, matchCase, matchWholeWord, reverse);
            slotReplaceText(textToReplace, replacementText, matchCase, matchWholeWord, reverse);
        }
    }
    replaceAll = false;
}

void DialogEditor::slotPlaintextChanged()
{
    static bool isBusy = false;
    if(isBusy){
        return;
    }

    isBusy = true;

    QObject * objSender = sender();
    QPlainTextEdit * editor = static_cast<QPlainTextEdit*>(objSender);
    if(editor->toPlainText().isEmpty()){
        isBusy = false;
        return;
    }

    if(spellChecker->getIsRehighlighting()){
        spellChecker->setIsRehighlighting(false);
    }//if we're just highlighting no need to spellcheck again
    else {
        //qDebug() << "Let's do some spell checking...";
        spellChecker->spellCheck(editor->toPlainText(),true);
    }//else let's spellcheck
    isBusy = false;
}

void DialogEditor::slotContextMenuRequested(const QPoint &pos)
{
    if(this->spellChecker != nullptr){
        spellChecker->createContextMenu(pos);
    }//if spellChecker is valid
    else {
        ui->plainTextEdit->createStandardContextMenu()->exec(ui->plainTextEdit->viewport()->mapToGlobal(pos));
    }
}

void DialogEditor::on_buttonBox_accepted()
{
    this->plaintextEditor->setPlainText(ui->plainTextEdit->toPlainText());
}

void DialogEditor::on_buttonBox_rejected()
{

}

void DialogEditor::on_pushButtonFind_clicked()
{
    replaceDialog->hide();
    highlightedText = ui->plainTextEdit->textCursor().selectedText();
    findDialog->show();

}

void DialogEditor::on_pushButtonReplace_clicked()
{
    findDialog->hide();
    highlightedText = ui->plainTextEdit->textCursor().selectedText();
    replaceDialog->show();
}
