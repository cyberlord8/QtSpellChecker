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
    void moveEvent(QMoveEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

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
//    QList<ClassSpellChecker *> spellCheckerList;
    ClassSpellChecker * spellChecker;
//    ClassSettings *settings;
    DialogFind *findDialog;
    DialogFindReplace *replaceDialog;
    bool atStart = false, atEnd = false, replaceAll = false;
    int numberReplacements = 0;

};

#endif // DIALOGEDITOR_H
