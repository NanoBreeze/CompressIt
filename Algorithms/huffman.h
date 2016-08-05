#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QtAlgorithms>

#include "huffmannode.h"

class Huffman
{
public:
    Huffman();
    void compress(const QString& filePath);

    //testing and diagnostics
    void printNodesWithoutChildren();

private:
    QHash<QChar, int> charCounts; //contains the number of time each character occurs

    QHash<HuffmanNode*, int> nodesWithoutParent; //all nodes we operate on come from this (sorted) map

    void countCharsInString(const QString& s);  //appends key/values to charCounts
    void readFile(const QString& filePath);

    //creates HuffmanNodes* associated with each character and their frequency count from the file
    void createNodesFromFrequency(const QHash<QChar, int>&charCounts);

    HuffmanNode* createNode(const QString &chars, const int &frequency); //used to create the very bottom (initial) nodes, who don't have children
    HuffmanNode* createNode(HuffmanNode* leftChild, HuffmanNode* rightChild); //used to create nodes that aren't at the very bottom

};


#endif // HUFFMAN_H
