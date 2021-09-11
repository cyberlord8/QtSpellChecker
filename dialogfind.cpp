/****************************************************************************
**
** Copyright (C) 2016 - 2021 Timothy Millea <timothy.j.millea@gmail.com> dba Green Radio Software Systems (GRSS)
**
** All rights reserved
**
****************************************************************************/

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
