#ifndef CODE_H
#define CODE_H

#include <QChar>
#include <QString>

struct Code
{
    Code(QChar symbol, int codewordLength);
    QChar symbol;
    QString codeword; //possibly replace with bits later
    int codewordLength;
};

inline bool operator <(const Code& lhs, const Code& rhs) {
    if( lhs.codewordLength == rhs.codewordLength)
    {
        return lhs.symbol < rhs.symbol;
    }
    return lhs.codewordLength < rhs.codewordLength;
}

#endif // CODE_H
