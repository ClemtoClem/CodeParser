#include "XMLDocument.hpp"

XMLDocument::XMLDocument() : _root(nullptr) {}

XMLDocument::~XMLDocument() {
    deleteAllNodes();
}

bool XMLDocument::load(const std::string& filename) {
    if (!checkExtensions(filename, {"xml"})) {
        _error = "File extension not allowed";
        return false;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        _error = "Unable to open file";
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    if (!content.empty()) {
        removeEmptyLines(content);

        if (content[0] == '<') {
            _root = SharedPtr<XMLNode>(new XMLNode("root"));
            parse(content, _root);
        } else {
            _error = "File is not an XML file";
            return false;
        }
    } else {
        _error = "File is empty";
        return false;
    }

    return _error.empty();
}

bool XMLDocument::save(const std::string& filename) {
    if (!_root) {
        _error = "No root node";
        return false;
    }

    if (!checkExtensions(filename, {"xml"})) {
        _error = "File extension not allowed";
        return false;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        _error = "Unable to open file";
        return false;
    }

    file << _root->toString();
    file.close();

    return true;
}

const std::string& XMLDocument::getError() const {
    return _error;
}

SharedPtr<Node> XMLDocument::getRoot() const {
    return _root;
}

void XMLDocument::deleteAllNodes() {
    _root = nullptr;
}

void XMLDocument::parseAttributes(const std::string& tag, const SharedPtr<XMLNode>& node) {
    size_t pos = tag.find(' ');
    while (pos != std::string::npos) {
        size_t eqPos = tag.find('=', pos);
        if (eqPos == std::string::npos) break;

        std::string name = tag.substr(pos + 1, eqPos - pos - 1);
        size_t valStart = tag.find('"', eqPos);
        size_t valEnd = tag.find('"', valStart + 1);
        if (valStart == std::string::npos || valEnd == std::string::npos) break;

        std::string value = tag.substr(valStart + 1, valEnd - valStart - 1);
        node->addAttribute(name, value);

        pos = tag.find(' ', valEnd);
    }
}

void XMLDocument::parse(const std::string& content, const SharedPtr<XMLNode>& parent) {
    size_t pos = 0;
    while (pos < content.size()) {
        size_t start = content.find('<', pos);
        size_t end = content.find('>', start);
        if (start == std::string::npos || end == std::string::npos) break;

        std::string tag = content.substr(start + 1, end - start - 1);
        if (tag[0] != '/') {
            std::string nodeName = tag.substr(0, tag.find(' '));
            SharedPtr<XMLNode> node(new XMLNode(nodeName, nullptr, parent));
            parent->addChild(node);

            parseAttributes(tag, node);

            size_t closeTagStart = content.find("</" + nodeName + ">", end);
            size_t closeTagEnd = content.find('>', closeTagStart);
            std::string innerXML = content.substr(end + 1, closeTagStart - end - 1);
            parse(innerXML, node);

            pos = closeTagEnd + 1;
        } else {
            pos = end + 1;
        }
    }
}
