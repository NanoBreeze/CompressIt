#include "huffmandecode.h"

HuffmanDecode::HuffmanDecode() : symbolCount(0)
{

}

void HuffmanDecode::decompress(const QString &filePath)
{
    hexString = readFile(filePath);

    getSymbolCountForCodewordLengths();
    addSymbolsAndCodewordLengths();
    deduceCanonicalEncoding(codes);
    createCodewordPrefixTree(codes);
    QList<QChar> message = decodeBinaryEncoding(root);

    QString filePathTxt = filePath;
   filePathTxt.chop(3); //change *.bin to *.txt
    filePathTxt += "txt"; //similar to compress

    writeOriginalFile(filePathTxt, message);
    //hexString[0] and [1] represent amount of symbols with codeword length 1
    //[2] and [3] with codeword length 2
    //[4] and [5] with codeword length 3
    //... [28] and [30] with codeword length 15
    //[2k-2] and [2k-1] with codeword length k



}

//read file and assign hexString containing the bytes
QString HuffmanDecode::readFile(const QString &filePath)
{
    QFile file(filePath);
    //    QDataStream dataStreamReader(&file);
    if (file.open(QIODevice::ReadOnly))
    {
        //        dataStreamReader << bytes;

        bytes = file.readAll();
        return QString(bytes.toHex());
        //        QString miniHexString = hexString.left(8); //first four character of hex string
        //        QString binaryString = QString::number(miniHexString.toLongLong(0, 16), 2);
        //        QByteArray::number()

        //        foreach (auto b, bytes)
        //        {
        //            qDebug() << bytes;
        //        }
        //            bytes.toInt()
        //            foreach (auto b, bytes)
        //            {
        //                qDebug() << bytes;
        //            }

        //        QTextStream textStream(&file); while (!textStream.atEnd())
        //        {
        //            QString line = textStream.readLine();
        //            text += line;	//store the text so it can be encoded after finding the canonical Huffman code associated with each character.
        //            qDebug() << line;
        //        }
        file.close();
    }
    else {
        qDebug() << "The specified file can't be opened";
    }
}

void HuffmanDecode::getSymbolCountForCodewordLengths()
{
    //hexString[0] and [1] represent amount of symbols with codeword length 1
    //[2] and [3] with codeword length 2
    //[4] and [5] with codeword length 3
    //... [28] and [30] with codeword length 15
    //[2k-2] and [2k-1] with codeword length k
    symbolCountForCodewordLengths[0] = 0;
    for (int i = 1; i < 16; ++i)
    {
        QString byte = hexString.left(2);
        hexString = hexString.remove(0, 2);
        symbolCount += byte.toInt(0, 16);
        symbolCountForCodewordLengths[i] = byte.toInt(0, 16);
        //        symbolCountForCodewordLengths[i] = getSymbolCountForCodewordLengths();
    }
    //    return byte.toInt(0, 16);
}


/*Each symbol takes up one byte and they are sorted with ascending codeword length order
 * This method gets all symbols and their codeword lengths. THis information is useful for determining
 * encoding of symbols (reverse construction of canonical Huffman)
 * */
void HuffmanDecode::addSymbolsAndCodewordLengths()
{
    //number of symbols is equal to sum of all symbols with lengths from 1 to 15
    int symbolsProcessed = 0;
    //keep finding symbol lengths if there are symbols remaining
    while (symbolsProcessed < this->symbolCount)
    {
        QString byte = hexString.left(2);
        hexString = hexString.remove(0, 2);
        QChar symbol = QChar::fromLatin1(byte.toInt(0, 16));
        int codewordLength = getCodewordLength(symbolsProcessed);
        HuffmanCode code(symbol, codewordLength);
        codes.append(code);
        ++symbolsProcessed;
    }
}

int HuffmanDecode::getCodewordLength(const int &symbolIndex) const
{
    //iterate through symbolCountForCodeLength and find the index in that array for which
    //the sum of element up to and including that index equals symbolIndex...consider using
    //a different data structure
    int indicesRemaining = symbolIndex + 1; //yes, this part is kind of confusing...will come back later to fix the increments
    for (int i = 1; i < 16; ++i)
    {
        if (indicesRemaining <= symbolCountForCodewordLengths[i])
        {
            //we have found the length associated witht this symbolIndex
            return i;
        }

        indicesRemaining -= symbolCountForCodewordLengths[i];
    }

    Q_ASSERT(false); //this shouldn't happen because all symbolIndex must associated with a length
}

void HuffmanDecode::deduceCanonicalEncoding(QList<HuffmanCode> & codes)
{
    //this is essentially identical to finding the canonical codeword when encoding symbols
    //consider merging this redundant code

    //the codes are sorted in ascending order. 0th element is the smallest
    //    int leadingZeroPadCount = codes[0].codewordLength - 1;

    int previousCodeword = -1; //used to determine next codeword. Added to and bitshifted
    int previousCodewordLength = 0; //determines number of bitshifts to perform on current code

    for(HuffmanCode& code: codes)
    {
        previousCodeword = (previousCodeword + 1) << ((code.codewordLength) - previousCodewordLength);
        previousCodewordLength = code.codewordLength;
        int currentCodeword = previousCodeword;

        QString paddedCodeword = padLeftZeros(currentCodeword, code.codewordLength);
        qDebug() << code.symbol << " : " << paddedCodeword;
        code.codeword = paddedCodeword;
    }
}


//adds additional zeros to front of codeword, if necessary, so that the codeword is long enough
QString HuffmanDecode::padLeftZeros(const int& codeword, const int& requiredCodewordLength)
{
    int currentLength = QString::number(codeword, 2).length();
    QString zeros(requiredCodewordLength - currentLength, '0');
    return zeros + QString::number(codeword, 2);
}

void HuffmanDecode::createCodewordPrefixTree(QList<HuffmanCode> &codes)
{
    PrefixTreeCodeNode* current = &root;

    foreach(HuffmanCode code, codes)
    {
        qDebug() << "Symbol: " << code.symbol << ". Codeword: " << code.codeword;

        for(int i = 0; i < code.codewordLength; ++i)//insert each bit into the prefix tree
        {
            if (code.codeword[i] == '1') //1 goes to the right and make new node if it doesn't already exist, if it does, simply reset current
            {
                if (current->right == nullptr)
                {
                    PrefixTreeCodeNode* newNode = new PrefixTreeCodeNode();
                    newNode->digit= code.codeword[i];
                    current->right = newNode;
                }
                current = current->right;
            }
            else //0 goes to the left
            {
                if (current->left == nullptr)
                {
                    PrefixTreeCodeNode* newNode = new PrefixTreeCodeNode();
                    newNode->digit= code.codeword[i];
                    current->left = newNode;
                }
                current = current->left;
            }
        }

        current->isLastDigit = true;
        current->symbol = code.symbol;

        current = &root;
    }
}

QList<QChar> HuffmanDecode::decodeBinaryEncoding(PrefixTreeCodeNode& root)
{
    QList<QChar> message;

    PrefixTreeCodeNode* current = &root;

    while (!hexString.isEmpty()) //loop through every hex value
    {
        QString hex = hexString.left(1);
        hexString = hexString.remove(0, 1);
        //convert this hex into binary and then loop throught the bits
        QString binaryString = QString::number(hex.toLongLong(0, 16), 2);
        binaryString = padLeftZeros(binaryString, 4 - binaryString.length());

        for (int i = 0; i < binaryString.length(); ++i)
        {
            QChar bit = binaryString[i];

            if (bit == '0') //current goes to the left
            {
                current = current->left;
            }
            else //else, current goes to the right
            {
                Q_ASSERT(bit == '1'); //the binary bit is either 0 or 1
                current = current->right;
            }

            if (current->isLastDigit)
            {
                //add symbol to message and start current at the root again
                message.append(current->symbol);
                qDebug() << "Added symbol: " << current->symbol;
                current = &root;
            }
        }


    }
    qDebug() << message;
    return message;

}

//adds additional zeros to front of codeword, if necessary, so that the codeword is long enough
QString HuffmanDecode::padLeftZeros(const QString& binaryString, const int& zerosNeededCount)
{
    QString zeros(zerosNeededCount, '0');
    return zeros + binaryString;
}

void HuffmanDecode::writeOriginalFile(const QString& filePath, const QList<QChar>& message) //creates original text in a new file
{
    QFile file(filePath); //overwrites existing
    if (file.open(QIODevice::WriteOnly))
    {
    QTextStream textStream(&file);

    foreach(QChar c, message)
    {
    textStream << QString(c);
    }


    file.close();
}
    else {
        qDebug() << "The file WriteOriginal.txt couldn't be opened to write to.";
    }
}
