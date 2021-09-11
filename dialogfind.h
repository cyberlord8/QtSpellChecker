/*
 * Copyright 2019 Green Radio Software Solutions (GRSS)
 * Released under GPL3 License
 * Find/Replace Dialog - A find/replace dialog  written in Qt

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


#ifndef DIALOGFIND_H
#define DIALOGFIND_H

#include <QDialog>

//#include "globals.h"

namespace Ui {
class DialogFind;
}

class DialogFind : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFind(QWidget *parent = nullptr);
    ~DialogFind();


private slots:
    void on_pushButtonFind_clicked();
    void on_lineEditFindText_textChanged(const QString &arg1);

signals:
    void signalFindNext(QString findText, bool matchCase, bool matchWholeWord, bool findBackwards);

private:
    Ui::DialogFind *ui;

protected:
    void showEvent(QShowEvent *event);

};

#endif // DIALOGFIND_H
