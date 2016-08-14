#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <QString>
#include <QHash>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QList>
#include <QtMath>

class Arithmetic
{
public:
    Arithmetic();
    void compress(const QString& filePath);
private:

    QMap<QChar, int> symbolFrequency; //contains the number of time each character occurs, thus, used to also find c_j and d_j
    QString text; //stores original data
    QString encoding;
    QString decoding;

    void readFile(const QString& filePath);
    void countSymbolFrequency(const QString& s);  //appends key/values to charCounts
    void encode(const QString& text);
    double getD_xi(const int& j) const; //returns d_j = c_j + r_j
    double getC_xi(const int& j) const; //returns c_j = r_0 + r_1 + r_2 + ... r_j-1, where the r_i are frequencies and stable! (we don't necessarily need to know the order as long as one exists. Using a QMap ensures that an order exists
    double getR_xi(const int& j) const; //returns the frequency of the symbol at position j

    //determines the character associated with this index to its position in QMap
    int findCharIndex(const QChar& ch) const;

    void decode(const QString& binaryString);
};

#endif // ARITHMETIC_H
