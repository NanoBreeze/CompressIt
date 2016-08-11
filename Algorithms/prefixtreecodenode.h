#ifndef PREFIXTREECODENODE_H
#define PREFIXTREECODENODE_H

#include <QList>
#include <QChar>

class PrefixTreeCodeNode
{
public:
    PrefixTreeCodeNode();
    bool isLastDigit; //represents this is the last binary digit for a code
    QChar symbol;
    QChar digit; //either 0 or 1
    PrefixTreeCodeNode* left = nullptr;
    PrefixTreeCodeNode* right = nullptr;

    //checks if this node's children contains a PrefixTreeCodeNode whose digit is the specified digit
//    bool isChildExists(const short& digit) const;

    //returns the PrefixTreeNode's whose letter corresponds with the specified letter
//    PrefixTreeCodeNode* getChild(const QChar& letter);
};

#endif // PREFIXTREECODENODE_H
