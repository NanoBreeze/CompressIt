#include "compressioncontroller.h"

CompressionController::CompressionController()
{

}
void CompressionController::compress(const QString& filePath, AlgorithmEnum algo)
{
    switch (algo)
    {
        case AlgorithmEnum::Huffman:

        qDebug() << "Huffman enum";
        compressHuffman(filePath);
        break;
    case AlgorithmEnum::Arithmetic:
        qDebug() << "Arithmetic enum";
        compressArithmetic(filePath);
        break;
    case AlgorithmEnum::LZ77:
        qDebug() << "LZ77 enum";
        compressLZ77(filePath);
        break;
    default:
        qCritical() << "Default. This Algorithmenum is not allowed";
    }
}

void CompressionController::decompress(const QString &filePath)
{
    HuffmanDecode huffmanDecode;
    huffmanDecode.decompress(filePath);
}

//consider using polymorphism here
void CompressionController::compressHuffman(const QString& filePath)
{
    Huffman huffman;
        huffman.compress(filePath);
}

void CompressionController::compressArithmetic(const QString& filePath)
{
    Arithmetic arithmetic;

        arithmetic.compress(filePath);
}

void CompressionController::compressLZ77(const QString& filePath)
{
    LZ77 lz77;
        lz77.compress(filePath);
}
