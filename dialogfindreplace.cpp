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


#include "dialogfindreplace.h"
#include "ui_dialogfindreplace.h"

#include "globals.h"

DialogFindReplace::DialogFindReplace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFindReplace)
{
    ui->setupUi(this);
}

DialogFindReplace::~DialogFindReplace()
{
    delete ui;
}

void DialogFindReplace::on_pushButtonFindNext_clicked()
{
    emit signalFindNext(ui->lineEditFindText->text(),
                        ui->checkBoxMatchCase->isChecked(),
                        ui->checkBoxMatchWholeWord->isChecked(),
                        ui->checkBoxFindBackwards->isChecked());
}//on_pushButtonFindNext_clicked

void DialogFindReplace::on_pushButtonReplace_clicked()
{
    emit signalReplaceText(ui->lineEditFindText->text(),
                           ui->lineEditReplaceText->text(),
                           ui->checkBoxMatchCase->isChecked(),
                           ui->checkBoxMatchWholeWord->isChecked(),
                           ui->checkBoxFindBackwards->isChecked());
}//on_pushButtonReplace_clicked

void DialogFindReplace::on_pushButtonReplaceAll_clicked()
{
    emit signalReplaceAllText(ui->lineEditFindText->text(),
                              ui->lineEditReplaceText->text(),
                              ui->checkBoxMatchCase->isChecked(),
                              ui->checkBoxMatchWholeWord->isChecked(),
                              ui->checkBoxFindBackwards->isChecked());
}//on_pushButtonReplaceAll_clicked

void DialogFindReplace::on_lineEditFindText_textChanged(const QString &arg1)
{
    ui->pushButtonFindNext->setEnabled(!arg1.isEmpty());
    ui->pushButtonReplace->setEnabled(!arg1.isEmpty());
    ui->pushButtonReplaceAll->setEnabled(!arg1.isEmpty());
}//on_lineEditFindText_textChanged

void DialogFindReplace::showEvent(QShowEvent *event)
{
    ui->lineEditFindText->setText(highlightedText);
    event->accept();
}//showEvent
