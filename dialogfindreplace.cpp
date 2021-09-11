/****************************************************************************
**
** Copyright (C) 2016 - 2021 Timothy Millea <timothy.j.millea@gmail.com> dba Green Radio Software Systems (GRSS)
**
** All rights reserved
**
****************************************************************************/

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
