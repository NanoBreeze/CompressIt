#include "testing.h"

Testing::Testing() : totalCharacterCount(0)
{

}

//PrefixTreeNode Testing::returnPointer(PrefixTreeNode *node)
//{
//    return node;
//}

void Testing::readFile(const QString &filePath)
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
        createCharFrequency();
    }
    else {
        qDebug() << "The specified file can't be opened";
    }
}

void Testing::countCharsInString(const QString &s)
{
    for (QChar c: s)
    {
        totalCharacterCount++;
        charCounts[c]++;
    }
}

void Testing::createCharFrequency()
{
    QHash<QChar, int>::const_iterator i = charCounts.constBegin();

    while (i != charCounts.constEnd())
    {
        charFrequencies[i.key()] = (double)i.value()/(double)totalCharacterCount;
        ++i;
    }
}


//
void Testing::buildPrefixTree(const QStringList &words)
{
//    PrefixTreeNode* current = &root;

//    for (const QString word : words)
//    {
//        qDebug() << "Word: " << word;
////        int numberOfNotNullChildren = 0;

////        for (int i = 0; i < 26; ++i)
////        {
////            if (root.children[i] != nullptr) { numberOfNotNullChildren++; }
////        }

////        qDebug() << "Number of not null children of root is: " << numberOfNotNullChildren;


//        for(int i = 0; i < word.length(); ++i)
//        {
//            int letterIndex = getLetterIndex(word[i]);
////            qDebug() << "letterIndex for i=" << i << " is: " << letterIndex;

//            if (current->children[letterIndex] == nullptr)
//            {
////                qDebug() << "current->children[letterIndex] is a nullptr";
//                PrefixTreeNode* newNode = new PrefixTreeNode();
//                newNode->letter = word[i];
//                current->children[letterIndex] = newNode;
//            }

//            current = current->children[letterIndex];
//        }

//        current->isLastCharacter = true;
//        current = &root;

//    }
//    test if the letters are correctly placed in the root node
//    PrefixTreeNode* current2 = &root;

////    int counter = 0;
////    while (counter < 5)
////    {
//        for (int i = 0; i < 26; ++i)
//        {
//            if (current2->children[i])
//            {
//                qDebug() << "The root->children[ " << i << "]" << current2->children[i]->letter;
//                current2 = current2->children[i];
//            }
//        }
//        counter++;

//    }

    //    qDebug() << "The type of a QString element is: " << typeid(s[2]).name();


    //    qDebug() << "The size of the children array of pointers at initialization is: " << sizeof(node.children);
}

bool Testing::search(const QString& word)
{
//    PrefixTreeNode* current = &root;

//    for (int i = 0; i < word.length(); ++i)
//    {
//        int letterIndex = getLetterIndex(word[i]);
//        if (current->children[letterIndex] == nullptr)
//        {
//            qDebug() << "The word:" << word << " is not found. The current i is: " << i << " and the letterIndex is: " << letterIndex;
//            return false; }

//        current = current->children[letterIndex];
//    }

//    return current->isLastCharacter;
    return true;
}

int Testing::getLetterIndex(const QChar& letter)
{
    if (letter == 'a')  return 0;
    else if (letter == 'b') return 1;
    else if (letter == 'c') return 2;
    else if (letter == 'd') return 3;
    else if (letter == 'e') return 4;
    else if (letter == 'f') return 5;
    else if (letter == 'g') return 6;
    else if (letter == 'h') return 7;
    else if (letter == 'i')  return 8;
    else if (letter == 'j')  return 9;

    else if (letter == 'k')  return 10;
    else if (letter == 'l')  return 11;
    else if (letter == 'm') return 12;
    else if (letter == 'n') return 13;
    else if (letter == 'o') return 14;
    else if (letter == 'p') return 15;
    else if (letter == 'q') return 16;
    else if (letter == 'r') return 17;
    else if (letter == 's')  return 18;
    else if (letter == 't')  return 19;
    else if (letter == 'u') return 20;

    else if (letter == 'v')  return 21;
    else if (letter == 'w')  return 22;
    else if (letter == 'x') return 23;
    else if (letter == 'y') return 24;
    else if (letter == 'z') return 25;
    else throw std::runtime_error("The specified letter is not an option");
}
