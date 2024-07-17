#include "JSONNode.hpp"

JSONNode::JSONNode(const std::string &name, SharedPtr<Data> data, SharedPtr<Node> parent)
 : Node('JSON', name, data, parent)
{
}

std::string JSONNode::toString(size_t tabulate) const {
    return std::string();
}
