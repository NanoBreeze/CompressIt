#ifndef TESTING_H
#define TESTING_H

#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QStringList>

#include <QDebug>
#include <typeinfo>
#include <QCharRef>
#include <QHash>
#include <QByteArray>

#include "prefixtreenode.h"

class Testing
{
public:
    Testing();

    void experimentOnByteArray();
    void readFile(const QString& filePath);
    void buildPrefixTree(const QStringList& words);
    bool search(const QString& word);
    int getLetterIndex(const QChar& letter);

    PrefixTreeNode root;

//    PrefixTreeNode returnPointer(PrefixTreeNode* node);

private:
    QHash<QChar, int> charCounts; //contains the number of time each character occurs
    void countCharsInString(const QString& s);  //appends key/values to charCounts

    int totalCharacterCount;

    QHash<QChar, double> charFrequencies; //contains the probability/frequency of each character appearing.
    void createCharFrequency(); //uses values in charCounts to populate charFrequencies with probability of each character
};

#endif // TESTING_H
