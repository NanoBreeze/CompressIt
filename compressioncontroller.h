#ifndef COMPRESSIONCONTROLLER_H
#define COMPRESSIONCONTROLLER_H


#include <QDebug>
#include <QUrl>
#include <QQueue>


#include "Algorithms/huffman.h"
#include "Algorithms/huffmandecode.h"
#include "Algorithms/lz77.h"
#include "Algorithms/arithmetic.h"
#include "algorithmenum.h"

//a Controller class that acts as the middleman between the compression algorithms and the mainwindow GUI. Responsible for queues urls, calling algorithms for encoding and decoding
class CompressionController
{
public:
    CompressionController();
    void compress(const QString& filePath, AlgorithmEnum); //applies compression algorithm to each file with corresponding URL in urls queue. Assumes queue already contains url
    void decompress(const QString& filePath); //use Huffman
private:
    void compressHuffman(const QString& filePath);
    void compressArithmetic(const QString& filePath);
    void compressLZ77(const QString& filePath);

};

#endif // COMPRESSIONCONTROLLER_H
