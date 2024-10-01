#include "ConfigNode.hpp"

ConfigNode::ConfigNode(const std::string &name, std::shared_ptr<Data> data, std::shared_ptr<Node> parent)
 : Node("CONFIG", name, data, parent) {
}

ConfigNode::~ConfigNode()
{
}

std::string ConfigNode::toString(size_t tabulate) const {
    std::stringstream ss;
    ss << _name << " = " << _value << std::endl;
    return ss.str();
}
