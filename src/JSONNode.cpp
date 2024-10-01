#include "JSONNode.hpp"

JSONNode::JSONNode(const std::string &name, std::shared_ptr<Data> data, std::shared_ptr<Node> parent)
 : Node("JSON", name, data, parent)
{
}

std::string JSONNode::toString(size_t tabulate) const {
    return std::string();
}
