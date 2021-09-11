# QtSpellChecker

I wrote and shared this 2 years ago, but somehow the repo got messed up and was missing files and would not compile.

Here it is again all fixed/cleaned up.

## Spell Check Class and Find/Replace Dialog written for Qt5

Qt5 based class with no dependencies on other libraries.

Stores dictionary words in a QSet (hash) for quick lookups. 

Uses QSyntaxHighlighter to mark misspelled words. 

<b>You can change the location of the dictionary.txt file, I have it located in <i>appfolder/../spellchecker/</i> as I had other apps dependent on the same dictionary.</b>

![image](https://user-images.githubusercontent.com/8164529/132950308-129c9bd8-4830-4bde-a8a8-159ba877cb4b.png)

Also includes a Find/Replace dialog.
![image](https://user-images.githubusercontent.com/8164529/132951546-6afe9716-f862-416f-a107-17e6692bfff4.png)

   ```
   public:
    explicit ClassSpellChecker(bool allowRecursion,
                               QFile *dictionaryFile,
                               QPlainTextEdit *textEditor,
                               QObject *parent = nullptr);

    bool isValid();//did ClassSpellChecker initialize OK?
    bool addWordtoDictionary(QString word);
    bool addWordtoDictionary(QStringList wordList);
    void createContextMenu(const QPoint &pos);

    //spellCheck returns a map of words not found in the dictionary and a list of possible substitutes
    QMap<QString, QStringList> spellCheck(QStringList wordList, bool clearLists);
    QMap<QString, QStringList> spellCheck(QString words, bool clearLists);

    bool getIsRehighlighting() const;
    void setIsRehighlighting(bool value);
 
