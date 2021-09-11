# QtSpellChecker
Spell check class written for Qt

Qt based class with no dependencies on other libraries.

Stores dictionary words in a QSet (hash) for quick lookups. 

Uses QSyntaxHighlighter to mark misspelled words. 

![image](https://user-images.githubusercontent.com/8164529/132950308-129c9bd8-4830-4bde-a8a8-159ba877cb4b.png)


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
    ```
