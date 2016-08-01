#include "prefixtreenode.h"

PrefixTreeNode::PrefixTreeNode() : isLastCharacter(false)
{

}

bool PrefixTreeNode::isChildExists(const QChar &letter) const
{
    for (PrefixTreeNode* child: children)
    {
        if (child->letter == letter)
        {
            return true;
        }
    }

    return false;
}

PrefixTreeNode* PrefixTreeNode::getChild(const QChar &letter)
{
    for (PrefixTreeNode* child: children)
    {
        if (child->letter == letter)
        {
            return child;
        }
    }
    qDebug() << "Oh oh, debug about to happen!";
    Q_ASSERT(false); //the child should exist! Otherwise, this method shouldn't be called
}

