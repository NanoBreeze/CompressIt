#include "huffmannode.h"

HuffmanNode::HuffmanNode():hasParent(false), frequency(0), characters("")
{

}

HuffmanNode::~HuffmanNode()
{
    if (left) { delete left; }
    if (right) { delete right; }
}
