#include "ConfigNode.hpp"

ConfigNode::ConfigNode(const std::string &name, Data *data, Node *parent)
 : Node('CONFIG', name, data, parent) {
}

std::string ConfigNode::toString(size_t tabulate) const {
    std::stringstream ss;
    ss << _name << " = " << _value << std::endl;
    return ss.str();
}
