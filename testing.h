#ifndef TESTING_H
#define TESTING_H

#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QStringList>

#include <QDebug>
#include <typeinfo>
#include <QCharRef>

#include "prefixtreenode.h"

class Testing
{
public:
    Testing();

    void readFile(const QString& filePath);
    void buildPrefixTree(const QStringList& words);
    bool search(const QString& word);
    int getLetterIndex(const QChar& letter);

    PrefixTreeNode root;

//    PrefixTreeNode returnPointer(PrefixTreeNode* node);
};

#endif // TESTING_H
