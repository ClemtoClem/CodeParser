#include "XMLDocument.hpp"

XMLDocument::XMLDocument() : _root(nullptr) {}

XMLDocument::~XMLDocument() {
    deleteAllNodes();
}

bool XMLDocument::loadFile(const std::string &filename) {
    // Vérifier l'extension du fichier
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
            if (_root) delete _root;
            _root = new XMLNode("root");
            parseXML(content, _root.get());
        } else {
            _error = "File is not an XML file";
            return false;
        }
    } else {
        _error = "File is empty";
        return false;
    }
    
    if (_error.empty()) {
        return true;
    } else {
        return false;
    }
}

bool XMLDocument::saveInFile(const std::string &filename) {
    if (!_root) {
        _error = "No root node";
        return false;
    }

    // Vérifier l'extension du fichier
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

const std::string XMLDocument::getError() const {
    return _error;
}

Shared<Node> XMLDocument::getRoot() const {
    return _root;
}

void XMLDocument::deleteAllNodes() {
    _root = new XMLNode("root");
}

void XMLDocument::parseAttributes(const std::string &tag, XMLNode *node) {
    // Simplified attribute parsing logic for demonstration
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

void XMLDocument::parse(const std::string &content, XMLNode *parent) {
    size_t pos = 0;
    while (pos < content.size()) {
        size_t start = content.find('<', pos);
        size_t end = content.find('>', start);
        if (start == std::string::npos || end == std::string::npos) break;

        std::string tag = content.substr(start + 1, end - start - 1);
        if (tag[0] != '/') {
            std::string nodeName = tag.substr(0, tag.find(' '));
            XMLNode *node = new XMLNode(nodeName, nullptr, parent);
            parent->addChild(node.get());

            parseAttributes(tag, node.get());

            size_t closeTagStart = content.find("</" + nodeName + ">", end);
            size_t closeTagEnd = content.find('>', closeTagStart);
            std::string innerXML = content.substr(end + 1, closeTagStart - end - 1);
            parse(innerXML, node.get());

            pos = closeTagEnd + 1;
        } else {
            pos = end + 1;
        }
    }
}