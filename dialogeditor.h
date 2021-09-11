/*
 * Copyright 2019 Green Radio Software Solutions (GRSS)
 * Released under GPL3 License
 * Dialog Editor - A simple text editor with find/replace written in Qt

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

#ifndef DIALOGEDITOR_H
#define DIALOGEDITOR_H

#include "classspellchecker.h"
#include "dialogfind.h"
#include "dialogfindreplace.h"

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class DialogEditor;
}

class DialogEditor : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditor(QPlainTextEdit * plaintextEditor,
                          QWidget *parent = nullptr);
    ~DialogEditor() override;

protected:

private slots:
    void slotFindNext(QString textToFind, bool matchCase, bool matchWholeWord, bool reverse);
    void slotReplaceText(QString textToReplace, QString replacementText, bool matchCase, bool matchWholeWord, bool reverse);
    void slotReplaceAllText(QString textToReplace, QString replacementText,
                            bool matchCase, bool matchWholeWord, bool reverse);

    void slotPlaintextChanged();
    void slotContextMenuRequested(const QPoint &pos);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_pushButtonFind_clicked();
    void on_pushButtonReplace_clicked();

private:
    Ui::DialogEditor *ui;
    QPlainTextEdit * plaintextEditor;
    ClassSpellChecker * spellChecker;
    DialogFind *findDialog;
    DialogFindReplace *replaceDialog;
    bool atStart = false, atEnd = false, replaceAll = false;
    int numberReplacements = 0;

};

#endif // DIALOGEDITOR_H
