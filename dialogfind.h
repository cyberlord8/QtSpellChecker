/****************************************************************************
**
** Copyright (C) 2016 - 2021 Timothy Millea <timothy.j.millea@gmail.com> dba Green Radio Software Systems (GRSS)
**
** All rights reserved
**
****************************************************************************/

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
