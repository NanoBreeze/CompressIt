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
    encodeChar(root, "");

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

void Huffman::encodeChar(HuffmanNode *root, QString encoding)
{
    Q_ASSERT(root != nullptr); //if the children of a node are null, call this method again

    qDebug() << "Inside encodeChar. Current encoding is: " << encoding;
    //this is an original node containing only one character. Both of its children are null
    if (root->left == nullptr)
    {
        qDebug() << "Inside if statment. Thus, node with only one char. Current encoding: " << encoding;
        Q_ASSERT(root->right == nullptr);

        charEncodings.insert(QString(root->characters).at(0), encoding);
        return;
    }

    encodeChar(root->left, encoding + "0");
    encodeChar(root->right, encoding + "1");
}


void Huffman::countCharsInString(const QString &s)
{
    for (QChar c: s)
    {
        charCounts[c]++;
    }
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


void Huffman::printCharEncodings()
{
    QHash<QChar, QString>::const_iterator i = charEncodings.constBegin();
    while (i != charEncodings.constEnd())
    {
        qDebug() << i.key() << " : " << i.value();
        ++i;
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
