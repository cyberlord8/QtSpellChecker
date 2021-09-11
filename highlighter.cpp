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

#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    spellingErrorFormat.setUnderlineColor(Qt::red);
    spellingErrorFormat.setUnderlineStyle(QTextCharFormat::WaveUnderline);
}//Highlighter

//Highlighter::~Highlighter()
//{
//    qDebug() << "Deleting Highlighter...";
//}//Highlighter

void Highlighter::addHighlightRule(QString word)
{
    HighlightingRule rule;
    rule.pattern = QRegularExpression("\\b"+word+"\\b");
    rule.format = spellingErrorFormat;
    if(!this->containsRule(rule))
        highlightingRules.append(rule);
}//addHighlightRule

void Highlighter::removeHighlightRule(QString word)
{
    for (int i = 0; i < highlightingRules.size(); ++i) {
        HighlightingRule rule = highlightingRules.value(i);
        if(rule.pattern == QRegularExpression("\\b"+word+"\\b")){
            highlightingRules.removeAt(i);
        }
    }
}//removeHighlightRule

void Highlighter::clearHighlightRules()
{
    highlightingRules.clear();
}//clearHighlightRules

bool Highlighter::containsRule(HighlightingRule chkRule)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        if(rule.pattern  == chkRule.pattern){
            return true;
        }
    }//foreach rule
    return false;
}//contains

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }//foreach rule
}//highlightBlock
