#include "XMLNode.hpp"

XMLNode::XMLNode(const std::string &name, Data *data, Node *parent)
 : Node('XML', name, data, parent)
{
}

void XMLNode::addAttribute(const std::string &name, const std::string &value)
{
    _attributes[name] = value;
}

const std::string &XMLNode::getAttribute(const std::string &name) const {
    static std::string empty;
    auto it = _attributes.find(name);
    if (it != _attributes.end()) {
        return it->second;
    }
    return empty;
}

bool XMLNode::hasAttribute(const std::string &name) const {
    return _attributes.find(name) != _attributes.end();
}

std::string XMLNode::toString(size_t tabulate = 0) const {

    return ;
}