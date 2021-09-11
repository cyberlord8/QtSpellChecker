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


#include "dialogfind.h"
#include "ui_dialogfind.h"

#include "globals.h"

#include <QShowEvent>

DialogFind::DialogFind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFind)
{
    ui->setupUi(this);

}

DialogFind::~DialogFind()
{
    delete ui;
}

void DialogFind::on_pushButtonFind_clicked()
{
    emit signalFindNext(ui->lineEditFindText->text(),
                        ui->checkBoxMatchCase->isChecked(),
                        ui->checkBoxMatchWholeWord->isChecked(),
                        ui->checkBoxFindBackwards->isChecked());
}//on_pushButtonFind_clicked

void DialogFind::on_lineEditFindText_textChanged(const QString &arg1)
{
    ui->pushButtonFind->setEnabled(!arg1.isEmpty());
}//on_lineEditFindText_textChanged

void DialogFind::showEvent(QShowEvent *event)
{
    ui->lineEditFindText->setText(highlightedText);
    event->accept();
}//showEvent
