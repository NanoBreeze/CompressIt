#include "arithmetic.h"

Arithmetic::Arithmetic() : encoding("")
{

}

void Arithmetic::compress(const QString &filePath)
{
    readFile(filePath);
    encode(text);

}

void Arithmetic::readFile(const QString& filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&file);
        while (!textStream.atEnd())
        {
            QString line = textStream.readLine();
            text += line;	//store the text so it can be encoded after finding the canonical Huffman code associated with each character.
            countSymbolFrequency(line);
            qDebug() << line;
        }
        file.close();
    }
    else {
        qDebug() << "The specified file can't be opened";
    }
}


void Arithmetic::countSymbolFrequency(const QString &s)
{
    for (QChar c: s)
    {
        symbolFrequency[c]++;
    }
}

//algorithm from https://www.youtube.com/watch?v=9vhbKiwjJo8
void Arithmetic::encode(const QString& text)
{
    qlonglong lower = 0;
    qlonglong upper = LONG_LONG_MAX/text.length()/2; //2^63 / length (to ensure overflow doesn't happen)
    qlonglong half = upper/2;
    qlonglong quarter = upper/4;

    int splitCount = 0;

    qlonglong width = 0;

    for (int i = 0; i < text.length(); ++i)
    {
        width = upper - lower;

        int charIndex = findCharIndex(text.at(i));
        qDebug() << "i is: " << i << " and charIndex is: " << charIndex;

        qlonglong c = getC_xi(charIndex);
        double d = getD_xi(charIndex);
        upper = lower + width * (getD_xi(charIndex) / text.length());
        lower = lower + width * (getC_xi(charIndex) /  text.length());

        Q_ASSERT(upper > 0);
        Q_ASSERT(lower >= 0);
        Q_ASSERT(upper >= lower); //the upper bound MUST be greater than or equal to (very rare) to lower bound

        qDebug() << "========================";
        qDebug() << "upper: " << upper;
        qDebug() << "lower: " << lower;

        while (upper < half || lower > half)
        {
            if (upper < half)
            {
                //emit 0111...111 (s 1s)
                encoding += "0";
                for (int i = 0; i < splitCount; ++i)
                {
                    encoding += "1";
                }

                upper = 2 * upper;
                lower = 2 * lower;
            }
            else //else if (lower > half)
            {
                //emit 1000...000 (s 0s)
                encoding += "1";
                for (int i = 0; i < splitCount; ++i)
                {
                    encoding += "0";
                }

                upper = 2 * (upper - half);
                lower = 2 * (lower - half);
            }

            splitCount = 0;
        }

        while (upper < 3 * quarter && lower > quarter )
        {
            splitCount++;
            upper = 2 * (upper - quarter);
            lower = 2 * (lower - quarter);
        }
    }

    splitCount++;
    if (lower <= quarter) //emit 011.1111 (s 1s)
    {
        encoding += "0";
        for (int i = 0; i < splitCount; ++i)
        {
            encoding += "1";
        }
    }
    else
    {
        encoding += "1";
        for (int i = 0; i < splitCount; ++i)
        {
            encoding += "0";
        }
    }
    qDebug() << encoding;
}

double Arithmetic::getD_xi(const int& j) const
{
    return getC_xi(j) + getR_xi(j);
}

double Arithmetic::getC_xi(const int &j) const
{
    //c_j = r_0 + r_1 + ... + r_(j-1)
    //c_0 = 0, c_1 = r_0; c_2 = r_0 + r_1
    //can be recursive too!

    int c_j = 0;

    for (int i = 0; i < j; ++i)
    {
        c_j += getR_xi(i);
    }

    return c_j;

}

double Arithmetic::getR_xi(const int &j) const
{
    QMap<QChar, int>::const_iterator iterator = symbolFrequency.constBegin();

    for (int i = 0; i < j; ++i)
    {
        iterator++;
    }

    //    qDebug() << iterator.key();
    return iterator.value();

}

int Arithmetic::findCharIndex(const QChar& ch) const
{
    QMap<QChar, int>::const_iterator iterator = symbolFrequency.constBegin();
    int index = 0;

    while (iterator.key() != ch)
    {
        iterator++;
        index++;
    }

    //    qDebug() << "The iterator's key is: " << iterator.key() << " and its value is: " << iterator.value();
    return index;
}
