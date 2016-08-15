#ifndef HUFFMANNODE
#define HUFFMANNODE

#include <QString>

struct HuffmanNode {
    HuffmanNode();
    ~HuffmanNode();
    HuffmanNode* left = nullptr;
    HuffmanNode* right = nullptr;
    //a node is availalbe to have its accumulatedFrequency be added to another node if this is false.
    //After the tree has been constructred, top-most node has this set to false
    bool hasParent;

    //represents the "number" associated with this node. Used to help determine another node's accumulatedFrequency
    int frequency;

    QString characters; //stores the string associated with this. Original nodes have characters only

};

inline bool operator <(const HuffmanNode& lhs, const HuffmanNode& rhs)
{
    return lhs.frequency <  rhs.frequency;
}

inline bool operator > (const HuffmanNode& lhs, const HuffmanNode& rhs)
{
    return lhs.frequency > rhs.frequency;
}

inline bool operator == (const HuffmanNode& lhs, const HuffmanNode& rhs)
{
    return lhs.frequency == rhs.frequency;
}

#endif // HUFFMANNODE

