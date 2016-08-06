#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QMultiMap>
#include <QtAlgorithms>
#include <QStandardItemModel>
#include <QQueue>
#include <QStandardItem>
#include <QStandardItemModel>

#include "huffmannode.h"

class Huffman
{
public:
    Huffman();
    void compress(const QString& filePath);

    //testing and diagnostics
    void printNodesWithoutChildren();

    //prints the encoding for each character. Assumes the Huffman tree had already been built and traversed with 0s and 1s
    void printCharEncodings();

    //fills the model with the node data in order to visually display it
    void populateItemModel(QStandardItemModel* model);

private:
    QHash<QChar, int> charCounts; //contains the number of time each character occurs

    QMultiMap<int, HuffmanNode*> nodesWithoutParent; //all nodes we operate on come from this (sorted) map

    QHash<QChar, QString> charEncodings; //contains the 0s and 1s pattern for each character

    HuffmanNode* root = nullptr; //the root of the Huffman tree. Found when there exists only one node remaining in the QMultiMap
    void countCharsInString(const QString& s);  //appends key/values to charCounts
    void readFile(const QString& filePath);

    //creates HuffmanNodes* associated with each character and their frequency count from the file
    void createNodesFromFrequency(const QHash<QChar, int>& charCounts);

    //constructs the Huffman tree with all original nodes at bottom and one at top (root). Returns the root
    HuffmanNode* constructHuffmanTree(QMultiMap<int, HuffmanNode*>&);

    //encodes the original characters with 0s and 1s. The original characters are in nodes at the most "bottom" and don't contain children nodes
    void encodeChar(HuffmanNode* root, QString encoding);


    HuffmanNode* createNode(const QString &chars, const int &frequency); //used to create the very bottom (initial) nodes, who don't have children
    HuffmanNode* createNode(HuffmanNode* leftChild, HuffmanNode* rightChild); //used to create nodes that aren't at the very bottom


};


#endif // HUFFMAN_H
