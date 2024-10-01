#include "XMLNode.hpp"

XMLNode::XMLNode(const std::string& name, std::shared_ptr<Data> data, std::shared_ptr<Node> parent)
    : Node("XML", name, data, parent) {
}

void XMLNode::addAttribute(const std::string& name, const std::string& value) {
    _attributes[name] = value;
}

const std::string& XMLNode::getAttribute(const std::string& name) const {
    static std::string empty;
    auto it = _attributes.find(name);
    if (it != _attributes.end()) {
        return it->second;
    }
    return empty;
}

bool XMLNode::hasAttribute(const std::string& name) const {
    return _attributes.find(name) != _attributes.end();
}

std::string XMLNode::toString(size_t tabulate) const {
    std::string indent(tabulate, '\t');
    std::string result;
    
    if (_data->getType() == "comment") {
        result = indent + _data->toString("xml");
    } else {
        result = indent + "<" + _name;

        for (const auto& attr : _attributes) {
            result += " " + attr.first + "=\"" + attr.second + "\"";
        }

        if (_firstChild) {
            result += ">\n";

            std::shared_ptr<Node> child = _firstChild;
            while (child) {
                result += child->toString(tabulate + 1) + "\n";
                child = child->getNextChild();
            }

            result += indent + "</" + _name + ">";
        } else {
            result += (_data ? ">" + _data->toString("xml") + "</" + _name + ">" : " />");
        }
    }
    return result;
}
