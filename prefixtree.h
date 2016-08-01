#ifndef PREFIXTREE_H
#define PREFIXTREE_H

#include "prefixtreenode.h"
#include <QStringList>
#include <QDebug>

class PrefixTree
{
public:
    PrefixTree();
    void insertWords(const QStringList& words);
    bool searchWord(const QString& word);

private:
    PrefixTreeNode root;
};

#endif // PREFIXTREE_H
