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
#include <QDataStream>

#include "huffmannode.h"
#include "code.h"

class Huffman
{
public:
    Huffman();
    void compress(const QString& filePath);

    //testing and diagnostics
    void printNodesWithoutChildren();

    //prints the encoding for each character. Assumes the Huffman tree had already been built and traversed with 0s and 1s
    void printCodewordLengths();

    //fills the model with the node data in order to visually display it
    void populateItemModel(QStandardItemModel* model);

private:
    QHash<QChar, int> symbolFrequency; //contains the number of time each character occurs

    QMultiMap<int, HuffmanNode*> nodesWithoutParent; //all nodes we operate on come from this (sorted) map

    QList<Code> codes; //stores the codes
    QString text; //stores the text of the read file. Used when encoding characters with canonical Huffman. Might change later because this takes up too much space
    QString encodedText; //binary string of the text from canonical Huffman encoding

    HuffmanNode* root = nullptr; //the root of the Huffman tree. Found when there exists only one node remaining in the QMultiMap
    void countSymbolFrequency(const QString& s);  //appends key/values to charCounts
    void readFile(const QString& filePath);

    //creates HuffmanNodes* associated with each character and their frequency count from the file
    void createNodesFromFrequency(const QHash<QChar, int>& symbolFrequency);

    //constructs the Huffman tree with all original nodes at bottom and one at top (root). Returns the root
    HuffmanNode* constructHuffmanTree(QMultiMap<int, HuffmanNode*>&);

    //encodes the original characters with 0s and 1s. The original characters are in nodes at the most "bottom" and don't contain children nodes
    void createCodewordLengths(HuffmanNode* root, int length);
    void sortCanonically(QList<Code>&);
    void assignCanonicalCodewords(QList<Code>&); //assigns codewords, eg, 100, 110 to values
    QString padLeftZeros(const int& codeword, const int& requiredCodewordLength); //left pads the given string with specified amount of 0s

    void encodeText(const QString& text); //encodes the text from the read file with the canonical binary encodingS
    QList<int> byteAlignEncodedText(const QString& encodedText); //make encoded binary text into 8-bit chunks so that they can be hex-represented. The final chunk will have padded 0s AT END!

    void writeBinaryFile(const QList<int>&); //turns the ints into hex values and write them to binary file

    int getNumberOfCodesOfBitLength(const int& length); //returns the number of codes whose codeword is of the specified lenght
    HuffmanNode* createNode(const QString &chars, const int &frequency); //used to create the very bottom (initial) nodes, who don't have children
    HuffmanNode* createNode(HuffmanNode* leftChild, HuffmanNode* rightChild); //used to create nodes that aren't at the very bottom


};


#endif // HUFFMAN_H
