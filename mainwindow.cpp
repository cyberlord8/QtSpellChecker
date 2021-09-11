/*
 * Copyright 2019 Green Radio Software Solutions (GRSS)
 * Released under GPL3 License
 * Test app - An app written to test spell check library

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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "globals.h"

QString highlightedText;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dictionaryFile = new QFile(qApp->applicationDirPath()+"/../spellchecker/dictionary.txt",this);
    if(dictionaryFile->exists()){
        ui->plainTextEditEditor->appendPlainText("Found dictionary... OK");
        spellChecker = new ClassSpellChecker(true, dictionaryFile, ui->plainTextEditEditor);
        //threading not used until signal/slots are incoporated
        //seems to run fine in main thread
//        spellCheckerThread = new QThread(this);
//        spellChecker->moveToThread(spellCheckerThread);
    }
    else {
        spellChecker = nullptr;
        ui->plainTextEditEditor->appendPlainText("ERROR: Dictionary not found!");
        ui->plainTextEditEditor->appendPlainText(qApp->applicationDirPath()+"/../spellchecker/dictionary.txt");
    }
}//MainWindow

MainWindow::~MainWindow()
{
    delete ui;
    if(spellChecker != nullptr){
        delete spellChecker;
        delete dictionaryFile;
//        delete spellCheckerThread;
    }
}//MainWindow

void MainWindow::on_plainTextEditEditor_textChanged()
{
    static bool isBusy = false;
    if(isBusy){
        if(spellChecker != nullptr){
            if(spellChecker->getIsRehighlighting()){
                spellChecker->setIsRehighlighting(false);
                QApplication::processEvents();
            }
        }
        return;
    }

    isBusy = true;

    if(spellChecker != nullptr){
        if(ui->plainTextEditEditor->toPlainText().size() > (editorDocument.size()+10)){
            spellChecker->spellCheck(ui->plainTextEditEditor->toPlainText(), true);
        }
        else {
            QTextCursor textCursor(ui->plainTextEditEditor->textCursor());
            textCursor.select(QTextCursor::LineUnderCursor);
            QString selectedWord = textCursor.selectedText();
            spellChecker->spellCheck(selectedWord, false);
        }
        editorDocument = ui->plainTextEditEditor->toPlainText();
    }
    isBusy = false;
}//on_plainTextEditEditor_textChanged

void MainWindow::on_plainTextEditEditor_customContextMenuRequested(const QPoint &pos)
{
    spellChecker->createContextMenu(pos);
}//on_plainTextEditEditor_customContextMenuRequested
