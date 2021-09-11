/****************************************************************************
**
** Copyright (C) 2016 - 2021 Timothy Millea <timothy.j.millea@gmail.com> dba Green Radio Software Systems (GRSS)
**
** All rights reserved
**
****************************************************************************/

#ifndef DIALOGFINDREPLACE_H
#define DIALOGFINDREPLACE_H

#include <QDialog>
#include <QShowEvent>

//#include "globals.h"

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
