#ifndef PREFIXTREENODE
#define PREFIXTREENODE

#include <QChar>
#include <QList>
#include <QDebug>

class PrefixTreeNode
{
public:
    PrefixTreeNode();
    bool isLastLetter;
    QChar letter;
    QList<PrefixTreeNode*> children;

    //checks if this node's children contains a PrefixNode whose letter is the provided letter
    bool isChildExists(const QChar& letter) const;

    //returns the PrefixTreeNode's whose letter corresponds with the specified letter
    PrefixTreeNode* getChild(const QChar& letter);
};



#endif // PREFIXTREENODE

