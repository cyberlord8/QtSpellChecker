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


#ifndef DIALOGFINDREPLACE_H
#define DIALOGFINDREPLACE_H

#include <QDialog>
#include <QShowEvent>


namespace Ui {
class DialogFindReplace;
}

class DialogFindReplace : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFindReplace(QWidget *parent = nullptr);
    ~DialogFindReplace();

private slots:
    void on_pushButtonFindNext_clicked();
    void on_pushButtonReplace_clicked();
    void on_pushButtonReplaceAll_clicked();
    void on_lineEditFindText_textChanged(const QString &arg1);

signals:
    void signalFindNext(QString findText, bool matchCase, bool matchWholeWord, bool findBackwards);
    void signalReplaceText(QString, QString, bool matchCase, bool matchWholeWord, bool findBackwards);
    void signalReplaceAllText(QString, QString, bool matchCase, bool matchWholeWord, bool reverse);

private:
    Ui::DialogFindReplace *ui;

protected:
    void showEvent(QShowEvent *event);

};

#endif // DIALOGFINDREPLACE_H
