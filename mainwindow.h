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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "classspellchecker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plainTextEditEditor_textChanged();
    void on_plainTextEditEditor_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;

    ClassSpellChecker *spellChecker = nullptr;
//    QThread *spellCheckerThread = nullptr; //removed as not used for direct calls to class methods
    QFile *dictionaryFile = nullptr;
    QString editorDocument;
};

#endif // MAINWINDOW_H
