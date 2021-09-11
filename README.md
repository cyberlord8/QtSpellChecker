# QtSpellChecker
Spell check class written for Qt

Qt based class with no dependencies on other libraries.

Stores dictionary words in a QSet (hash) for quick lookups. 

Uses QSyntaxHighlighter to mark misspelled words. 

    // class constructor - pass QFile, QPlaintextEdit, and optional parent
    explicit ClassSpellChecker(QFile *dictionaryFile, QPlainTextEdit *textEditor, QObject *parent = nullptr);
    ~ClassSpellChecker();

    bool isValid();//did ClassSpellChecker initialize OK?
    bool addWordtoDictionary(QString word);
    bool addWordtoDictionary(QStringList wordList);
    //creates context menu of suggested words
    void createContextMenu(const QPoint &pos);

    //spellCheck returns a map of words not found in the dictionary and a list of possible substitutes
    QMap<QString, QStringList> spellCheck(QStringList wordList, bool clearLists);
    QMap<QString, QStringList> spellCheck(QString words, bool clearLists);

    bool getIsRehighlighting() const;
    void setIsRehighlighting(bool value);
