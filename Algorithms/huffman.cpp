#include "huffman.h"

Huffman::Huffman()
{

}

/*
 * 1. [Optional] Sort nodes in numerical order. This facilitates thinking about and debugging Huffman algorithms
 * 2. Find the two nodes without parents and have lowest frequency (likely store all these nodes in a sorted list to facilitate finding them) and then create a new node,
 * 		a) whose frequency is the sum of the previously found two node's frequency
 * 		b) has left and right pointers are to the left and right previously found nodes
 * 		c) has no parent (set hasParent to false)
 * 3. Continue executing step 2 until there exists only one node without parent (this is the top-most node). There are several sanity checks:
 * 		a) the frequency of this one node is the sum of all original node's frequencies
 * 		b) this is the only node without parent (redundant)
 * 		c) all nodes have non-null left and right pointers (because they have children) except for the original nodes
 * 4. Assign all left and right branches  0 or 1, consistently and recursively
 * 5. Traverse top to bottom to accumulate 0s and 1s. When traversal reaches an original node, the conglomerate of 0s and 1s represents its encoding
 */

void Huffman::compress(const QString &filePath)
{
    readFile(filePath);
    createNodesFromFrequency(charCounts);
    root = constructHuffmanTree(nodesWithoutParent);
    createCodewordLengths(root, 0);
    sortCanonically(codes);
    assignCanonicalCodewords(codes);
    encodeText(text);
    QList<int> byteInts = byteAlignEncodedText(encodedText);
    writeBinaryFile(byteInts);

}

void Huffman::readFile(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&file);
        while (!textStream.atEnd())
        {
            QString line = textStream.readLine();
            text += line;	//store the text so it can be encoded after finding the canonical Huffman code associated with each character.
            countCharsInString(line);
            qDebug() << line;
        }
        file.close();
    }
    else {
        qDebug() << "The specified file can't be opened";
    }
}

void Huffman::createNodesFromFrequency(const QHash<QChar, int> &charCounts)
{
    QHash<QChar, int>::const_iterator i = charCounts.constBegin();
    while (i != charCounts.constEnd())
    {
       //create a HuffmanNode and add it to the the QMap
        HuffmanNode* node = createNode(QString(i.key()), i.value());
//        qDebug() << "Creating node with key: " << i.key() << " and value: " << i.value();
        nodesWithoutParent.insertMulti(node->frequency, node);
        ++i;
    }
}

//uses the QMultiMap and builds Huffman tree from it. The tree is consider built when there is only
//one node in it.

 //* 2. Find the two nodes without parents and have lowest frequency (likely store all these nodes in a sorted list to facilitate finding them) and then create a new node,
 //* 		a) whose frequency is the sum of the previously found two node's frequency
 //* 		b) has left and right pointers are to the left and right previously found nodes
 //* 		c) has no parent (set hasParent to false)
 //* 3. Continue executing step 2 until there exists only one node without parent (this is the top-most node). There are several sanity checks:
HuffmanNode* Huffman::constructHuffmanTree(QMultiMap<int, HuffmanNode *> & nodesWithoutParents)
{
    if (nodesWithoutParents.size() == 1) //the remaining node must be the root
    {
    qDebug() << "================= ROOT NODE ====================";
    qDebug() << "Characters: " << nodesWithoutParents.first()->characters;
    qDebug() << "Frequency: " << nodesWithoutParents.first()->frequency;
        return nodesWithoutParents.first();
    }

    int initialNodesWithoutParentsSize = nodesWithoutParents.size(); //used for sanity check. Later size should be one less than this

    HuffmanNode* smallestNode = nodesWithoutParents.take(nodesWithoutParents.firstKey());
    HuffmanNode* secondSmallestNode = nodesWithoutParents.take(nodesWithoutParents.firstKey());

    HuffmanNode* newNode = new HuffmanNode();
    newNode->frequency = smallestNode->frequency + secondSmallestNode->frequency;

    //smallest on left and second smallest on right
    newNode->left = smallestNode;
    newNode->right = secondSmallestNode;
    newNode->hasParent = false;
    newNode->characters = smallestNode->characters + secondSmallestNode->characters;

   nodesWithoutParents.insertMulti(newNode->frequency, newNode);

   int currentNodesWithoutParentsSize = nodesWithoutParents.size();

   Q_ASSERT(currentNodesWithoutParentsSize == initialNodesWithoutParentsSize - 1); //two nodes are taken out and one is added in. Total: 1 less than start

    qDebug() << "===========================================";
    qDebug() << "Characters: " << smallestNode->characters <<  " Frequency:" << smallestNode->frequency;
    qDebug() << "Characters: " << secondSmallestNode->characters <<  " Frequency:" << secondSmallestNode->frequency;
    qDebug() << "nodesWithoutParents size: " << nodesWithoutParents.size();

    return constructHuffmanTree(nodesWithoutParents);
}

void Huffman::createCodewordLengths(HuffmanNode *root, int length)
{
    Q_ASSERT(root != nullptr); //if the children of a node are null, call this method again

//    qDebug() << "Inside encodeChar. Current length is: " << length ;
    //this is an original node containing only one character. Both of its children are null
    if (root->left == nullptr)
    {
//        qDebug() << "Inside if statment. Thus, node with only one char. Current length: " << length;
        Q_ASSERT(root->right == nullptr);

        Code code(QString(root->characters).at(0), length);
        codes.append(code);
//        qDebug() << QString(root->characters).at(0) << " : " << QString::number(length);
//        codeWordLengths.insert(QString(root->characters).at(0), length);
        return;
    }
    length++;
    createCodewordLengths(root->left, length);
    createCodewordLengths(root->right, length);
}

void Huffman::sortCanonically(QList<Code> &codes)
{
    //sort codes by codeword length and then symbol
    qSort(codes);
}

//Algorithm from https://en.wikipedia.org/wiki/Canonical_Huffman_code
void Huffman::assignCanonicalCodewords(QList<Code> &codes)
{
    //the codes are sorted in ascending order. 0th element is the smallest
//    int leadingZeroPadCount = codes[0].codewordLength - 1;

    int previousCodeword = -1; //used to determine next codeword. Added to and bitshifted
    int previousCodewordLength = 0; //determines number of bitshifts to perform on current code

    for(Code& code: codes)
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
QString Huffman::padLeftZeros(const int& codeword, const int& requiredCodewordLength)
{
    int currentLength = QString::number(codeword, 2).length();
    QString zeros(requiredCodewordLength - currentLength, '0');
    return zeros + QString::number(codeword, 2);
}


void Huffman::countCharsInString(const QString &s)
{
    for (QChar c: s)
    {
        charCounts[c]++;
    }
}

void Huffman::encodeText(const QString &text)
{
    //find the codeword associated with each character and append that to the encodedText
    foreach(QChar c, text)
    {
        QString codeword;
        //find codeword. Looping is not optimal strategy. Consider using a hash instead
        foreach(Code code, codes)
        {
            if (c == code.symbol)
            {
                codeword = code.codeword;
            }
        }
        encodedText += codeword;
    }
    qDebug() << "The encodedText is: " << encodedText;
}

QList<int> Huffman::byteAlignEncodedText(const QString &encodedText)
{

    QString remainingEncodedText = encodedText;
    QList<int> byteInts;

    //group every eight bits as a q-int
    while (remainingEncodedText.length() > 8)
    {
        //converts most left 8 bits into a qint8 integer and store in list
         byteInts.append(remainingEncodedText.left(8).toInt(0,2));
        remainingEncodedText.remove(0, 8);
}
    //if there are 8 or less bits in encoded text, pad additional 0s to end

    int extraZerosCount = 8 - remainingEncodedText.length();
    QString zeros(extraZerosCount, '0');
    remainingEncodedText += zeros;
     byteInts.append(remainingEncodedText.left(8).toInt(0,2));

    return  byteInts;

}

void Huffman::writeBinaryFile(const QList<int>& byteInts)
{
    //representing hex
    QFile file("C://Users//Lenny//Desktop//WriteBin.bin");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    //find number of symbols for each bit-length, starting with 1, 2, 3... for value gets a byte. We assume no more than 15 bit-lengths,
    QList<int> numberOfSymbolsForEachBitLength;
    for (int i = 1; i < 16; ++i)
    {
     numberOfSymbolsForEachBitLength.append(getNumberOfCodesOfBitLength(i));
}
    //write the bit-lengths. Here, assume no more than 255 symbols per count ;)
    foreach(int symbolCount, numberOfSymbolsForEachBitLength)
    {
        qDebug() << (qint8) symbolCount;
        out << (qint8) symbolCount;
    }


    //write codebook to file
    foreach(Code code, codes)
    {
        qDebug() << (qint8) code.symbol.toLatin1();
        out << (qint8) code.symbol.toLatin1();
    }

    //write original text with encoded hex format
    foreach (int byteInt, byteInts)
    {
        out << (qint8)byteInt;
    }

    file.close();

}

int Huffman::getNumberOfCodesOfBitLength(const int &length)
{
    int count = 0;
    foreach(Code code, codes)
    {
        if (code.codewordLength == length)
        {
            count++;
        }
    }
    return count;
}

HuffmanNode* Huffman::createNode(const QString &chars, const int &frequency)
{
    HuffmanNode* node = new HuffmanNode();
    node->frequency 	= frequency;
    node->characters 	= chars;
    return node;
}

HuffmanNode* Huffman::createNode(HuffmanNode *leftChild, HuffmanNode *rightChild)
{
    HuffmanNode* node = new HuffmanNode();
    node->left		 = leftChild;
    node->right 	 = rightChild;
    node->frequency	 = leftChild->frequency + rightChild->frequency;
    node->characters = leftChild->characters + rightChild->characters;

    return node;

}

void Huffman::printNodesWithoutChildren()
{
    QMap<int, HuffmanNode*>::const_iterator i = nodesWithoutParent.constBegin();
    while (i != nodesWithoutParent.constEnd())
    {
        qDebug() << i.key() << " : " << i.value()->characters;
        ++i;
    }
}


void Huffman::printCodewordLengths()
{
    foreach(Code code, codes)
    {
        qDebug() << code.symbol << " : " << code.codewordLength;
    }
}


void Huffman::populateItemModel(QStandardItemModel *model)
{
    //level-order traversal to display the next hierachy of the prefix tree
    QQueue<HuffmanNode*> queue;
    queue.enqueue(root);

    //used to build hierachy of QStandardItem. Children are added in while loop
    //The QStandardItem are either added to another one or to model.
    QQueue<QStandardItem*> itemQueue;

    QStandardItem* rootItem = model->invisibleRootItem(); //NOTE: root doesn't have a letter

    itemQueue.enqueue(rootItem);


    while(!queue.isEmpty())
    {
        HuffmanNode* temp = queue.dequeue();

        QStandardItem* item = itemQueue.dequeue();

        //add both children nodes to the model
        if (temp->left)
        {
            QStandardItem* childItem = new QStandardItem("Freq " + QString::number(temp->left->frequency) + "| " + temp->left->characters);

            item->appendRow(childItem);
            itemQueue.enqueue(childItem);
            queue.enqueue(temp->left);
        }

        if (temp->right)
        {
            QStandardItem* childItem = new QStandardItem("Freq " + QString::number(temp->right->frequency) + "| " + temp->right->characters);

            item->appendRow(childItem);
            itemQueue.enqueue(childItem);
            queue.enqueue(temp->right);
        }
    }
}
