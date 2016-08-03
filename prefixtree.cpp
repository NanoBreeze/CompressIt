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

        current->isLastLetter = true;
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

    return current->isLastLetter;
}


void PrefixTree::populateModel(QStandardItemModel* model)
{

    //level-order traversal to display the next hierachy of the prefix tree
    QQueue<PrefixTreeNode*> queue;
    queue.enqueue(&root);

    //used to build hierachy of QStandardItem. Children are added in while loop
    //The QStandardItem are either added to another one or to model.
    QQueue<QStandardItem*> itemQueue;

    QStandardItem* rootItem = model->invisibleRootItem(); //NOTE: root doesn't have a letter

    //visually display letters that are the last letters for the word
    rootItem->setBackground(getStandardItemBackgroundBrush(root.isLastLetter));

    itemQueue.enqueue(rootItem);


    while(!queue.isEmpty())
    {
        PrefixTreeNode* temp = queue.dequeue();

        QStandardItem* item = itemQueue.dequeue();

        //visually display letters that are the last letters for the word
        item->setBackground(getStandardItemBackgroundBrush(temp->isLastLetter));

        //add all immediate children to the treeviewmodel
        for (PrefixTreeNode* child: temp->children)
        {
            Q_ASSERT(child->letter.isLetter()); //each child's letter must, well, be a letter! Right now, no numbers

            //no need to do if statement to check for nullness because if a prefixTreeNode contains a
            //PrefixTreeNode in its children, that node MUST have been given a letter (we check above just to have sanity)

            QStandardItem* childItem = new QStandardItem(child->letter);
            childItem->setBackground(getStandardItemBackgroundBrush(child->isLastLetter));

            item->appendRow(childItem);
            itemQueue.enqueue(childItem);
            queue.enqueue(child);
        }
    }
}

QBrush PrefixTree::getStandardItemBackgroundBrush(const bool& isSetColour)
{
    if (isSetColour)
    {
        QBrush brush(Qt::yellow);
        return brush;
    }
    else
    {
        QBrush brush(Qt::white);
        return brush;
    }
}
