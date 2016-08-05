#include "huffman.h"

Huffman::Huffman()
{

}

/*
 * 1. [Optional] Sort nodes in numerical order. This facilitates thinking about and debugging Huffman algorithms
 * 2. Find the two nodes without parents and have lowest frequency (likely store all these nodes in a sorted list to facilitate finding them) and then create a new node,
 * 		a) whose frequency is the sum of the previously found two node's frequency
 * 		b) has left and right pointers are to the left and right previously found nodes
 * 		c) has no parent (set hasParent to false)
 * 3. Continue executing step 2 until there exists only one node without parent (this is the top-most node). There are several sanity checks:
 * 		a) the frequency of this one node is the sum of all original node's frequencies
 * 		b) this is the only node without parent (redundant)
 * 		c) all nodes have non-null left and right pointers (because they have children) except for the original nodes
 * 4. Assign all left and right branches  0 or 1, consistently and recursively
 * 5. Traverse top to bottom to accumulate 0s and 1s. When traversal reaches an original node, the conglomerate of 0s and 1s represents its encoding
 */

void Huffman::compress(const QString &filePath)
{
    readFile(filePath);
    createNodesFromFrequency(charCounts);
}

void Huffman::readFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&file);
        while (!textStream.atEnd())
        {
            QString line = textStream.readLine();
            countCharsInString(line);
            qDebug() << line;
        }
        file.close();
    }
    else {
        qDebug() << "The specified file can't be opened";
    }
}

void Huffman::createNodesFromFrequency(const QHash<QChar, int> &charCounts)
{
    QHash<QChar, int>::const_iterator i = charCounts.constBegin();
    while (i != charCounts.constEnd())
    {
       //create a HuffmanNode and add it to the the QMap
        HuffmanNode* node = createNode(QString(i.key()), i.value());
//        qDebug() << "Creating node with key: " << i.key() << " and value: " << i.value();
        nodesWithoutParent.insert(node, node->frequency);
        ++i;
    }
}

void Huffman::countCharsInString(const QString &s)
{
    for (QChar c: s)
    {
        charCounts[c]++;
    }
}

HuffmanNode* Huffman::createNode(const QString &chars, const int &frequency)
{
    HuffmanNode* node = new HuffmanNode();
    node->frequency 	= frequency;
    node->characters 	= chars;
    return node;
}

HuffmanNode* Huffman::createNode(HuffmanNode *leftChild, HuffmanNode *rightChild)
{
    HuffmanNode* node = new HuffmanNode();
    node->left		 = leftChild;
    node->right 	 = rightChild;
    node->frequency	 = leftChild->frequency + rightChild->frequency;
    node->characters = leftChild->characters + rightChild->characters;

    return node;

}

void Huffman::printNodesWithoutChildren()
{
QSet<int> vals = nodesWithoutParent.values().toSet();
foreach( int val, vals )
{
    QList<HuffmanNode*> keys = nodesWithoutParent.keys( val );
    foreach( HuffmanNode* key, keys )
    {
        qDebug() << key->characters << " :" << val;
    }
}//    QHash<HuffmanNode*, int>::const_iterator i = nodesWithoutParent.constBegin();
//    while (i != nodesWithoutParent.constEnd())
//    {
//       //create a HuffmanNode and add it to the the QMap
//        qDebug() << "HuffmanNode with frequency of: " << i.value();
//        ++i;
//    }
}
