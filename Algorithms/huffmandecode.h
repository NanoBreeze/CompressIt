#ifndef HUFFMANDECODE_H
#define HUFFMANDECODE_H

#include <QString>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>


#include "code.h"
#include "prefixtreecodenode.h"

//decodes the binary file WriteBin.bin from "C://Users//Lenny//Desktop//Testing.txt"
class HuffmanDecode
{
public:
    HuffmanDecode();
    void decompress(const QString& filePath);

private:
    QByteArray bytes;
    QString hexString; //contains the binary bytes in terms of hex values
    QList<Code> codes; //code, containing the symbol and the decoded codeword
    int symbolCountForCodewordLengths[16]; //the number of symbols that have 1, 2, 3, etc. codeword length
    int symbolCount; //equal to sum of elements in symbolCountForCodewordLengths
    QString readFile(const QString& filePath);

    // Get number of symbols for each bit length, eg, amount of symbols of codeword length 1,
    //codeword length2, etc. There are a max of 16 symbols, each amount occupies 1 byte,
    //thus interpret first 16 bytes
    void getSymbolCountForCodewordLengths();
    void addSymbolsAndCodewordLengths(); //finds the symbol and codeword associated with that symbol
    int getCodewordLength(const int& symbolIndex) const; //returns the length of the codeword associated at the given index, which is matched to symbolCountForCodewordLength[...]

    void deduceCanonicalEncoding(QList<Code>&); //finds the encoding associated with each symbol base upon their codelength and canonical algorithm
    QString padLeftZeros(const int& codeword, const int& requiredCodewordLength); //left pads the given string with specified amount of 0s

    PrefixTreeCodeNode root; //root of the prefix tree containing code nodes
    void createCodewordPrefixTree(QList<Code>&); //enables matching binary patterns in encoded file to the associated symbol
    QList<QChar> decodeBinaryEncoding(PrefixTreeCodeNode& root); //converts the binary strings (codewords) in file into their respective symbols
    QString padLeftZeros(const QString& binaryString, const int& zerosNeededCount); //used by decodeBinaryEncoding

    void writeOriginalFile(const QList<QChar>& message); //creates original text in a new file
};


#endif // HUFFMANDECODE_H
