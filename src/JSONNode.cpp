#include "JSONNode.hpp"

JSONNode::JSONNode(const std::string &name, Data *data, Node *parent)
 : Node('JSON', name, data, parent)
{
}
