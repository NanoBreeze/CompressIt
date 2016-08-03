#ifndef PREFIXTREE_H
#define PREFIXTREE_H

#include "prefixtreenode.h"
#include <QStringList>
#include <QDebug>
#include <QQueue>

#include <QStandardItemModel>
#include <QStandardItem>

class PrefixTree
{
public:
    PrefixTree();
    void insertWords(const QStringList& words);
    bool searchWord(const QString& word);

    //Adds PrefixTreeNode data to model, hierachially. Might be better to place this function in another class, like a controller.
    void populateModel(QStandardItemModel* model);

private:
    PrefixTreeNode root;

    //Sets the background of the specified standard item to indicate whether this node is the end of a word or not. Might need to place this in a controller class instead of here in the data.
    QBrush getStandardItemBackgroundBrush(const bool& isSetColour);
};

#endif // PREFIXTREE_H
