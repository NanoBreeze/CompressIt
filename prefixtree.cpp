#include "prefixtree.h"

PrefixTree::PrefixTree()
{

}


void PrefixTree::insertWords(const QStringList &words)
{

    PrefixTreeNode* current = &root;

    for (const QString word : words)
    {
        qDebug() << "Word: " << word;

        for(int i = 0; i < word.length(); ++i)
        {
            if (current->isChildExists(word[i]) == false)
            {
//                qDebug() << "Child doesn't exist";
                PrefixTreeNode* newNode = new PrefixTreeNode();
                newNode->letter = word[i];
                current->children.append(newNode);
            }
            current = current->getChild(word[i]);
        }

        current->isLastCharacter = true;
        current = &root;

    }
}

bool PrefixTree::searchWord(const QString &word)
{
     PrefixTreeNode* current = &root;

    for (int i = 0; i < word.length(); ++i)
    {
        if (current->isChildExists(word[i]) == false)
        {
            qDebug() << "The word:" << word << " is not found. The current i is: " << i ;
            return false;
        }

        current = current->getChild(word[i]);
    }

    return current->isLastCharacter;
}
