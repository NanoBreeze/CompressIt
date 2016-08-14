#include "arithmetic.h"

Arithmetic::Arithmetic() : encoding(""), decoding("")
{

}

void Arithmetic::compress(const QString &filePath)
{
    readFile(filePath);
    encode(text);
    decode("00110");

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
    qlonglong upper = LONG_LONG_MAX; //2^63
    const qlonglong HALF = upper/2;
    const qlonglong QUARTER = upper/4;

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

        while (upper < HALF || lower > HALF)
        {
            if (upper < HALF)
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

                upper = 2 * (upper - HALF);
                lower = 2 * (lower - HALF);
            }

            splitCount = 0;
        }

        while (upper < 3 * QUARTER && lower > QUARTER )
        {
            splitCount++;
            upper = 2 * (upper - QUARTER);
            lower = 2 * (lower - QUARTER);
        }
    }

    splitCount++;
    if (lower <= QUARTER) //emit 011.1111 (s 1s)
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

    return index;
}

//algorithm from https://www.youtube.com/watch?v=RFPwltOz1IU
void Arithmetic::decode(const QString &binaryString)
{

    qlonglong lower = 0;
    qlonglong upper = LONG_LONG_MAX;

    qlonglong lower_0 = 0;
    qlonglong upper_0 = 0;

    const qlonglong HALF = upper/2;
    const qlonglong QUARTER = upper/4;

    qlonglong z = 0;

    int i = 0;
    qlonglong width = 0;

    const int PRECISION = 31-1;

    while (i < PRECISION && i < binaryString.length())
    {
        if (binaryString.at(i) == '1')
        {
            z += qPow(2, PRECISION - i);
        }
        ++i;
    }

    while (true)
    {        for (int j = 0; j < symbolFrequency.count(); ++j)
        {
            width = upper - lower;

            qlonglong c = getC_xi(j);
            double d = getD_xi(j);

            upper_0 = lower + width * (getD_xi(j) / text.length()); //I THINK? we must have the order and size of text given
            lower_0 = lower + width * (getC_xi(j) /  text.length());

            Q_ASSERT(upper_0 > 0);
            Q_ASSERT(lower_0 >= 0);
            Q_ASSERT(upper_0 >= lower_0); //the upper bound MUST be greater than or equal to (very rare) to lower bound

            if (lower_0 <= z && z < upper_0)
            {
                decoding += QString::number(j);
                lower = lower_0;
                upper = upper_0;
                if (j == 0) { break; }
            }
        }

        while (upper < HALF || lower > HALF)
        {
            if (upper < HALF)
            {
                z = 2 * z;
                lower = 2 * lower;
                upper = 2 * upper;
            }
            else //else if (a < HALF)
            {
                z = 2 * (z - HALF);
                lower = 2 * (lower - HALF);
                upper = 2 * (upper - HALF);
            }

            if (i < binaryString.length() && binaryString.at(i) == '1'  )
            {
                z += 1;
            }
            ++i;
        }

        while (lower > QUARTER && upper < 3 * QUARTER)
        {
            z = 2 * (z - QUARTER);
            lower = 2 * (lower - QUARTER);
            upper = 2 * (upper - QUARTER);

            if (i < binaryString.length() && binaryString.at(i) == '1' )
            {
                z += 1;
            }
            ++i;
        }

    }
    qDebug() << "Decoded text: " << decoding;
}
