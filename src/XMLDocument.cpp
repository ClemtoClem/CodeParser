#include "XMLDocument.hpp"
#include <stack>
#include <regex>
#include <sstream>
#include <iostream>

XMLDocument::XMLDocument() : Document("XML"), _root(nullptr) {}

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

    if (!checkTags(content)) {
        return false;
    }

    if (!content.empty()) {
        removeEmptyLines(content);

        if (content[0] == '<') {
            _root = std::shared_ptr<XMLNode>(new XMLNode("root"));
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

std::shared_ptr<Node> XMLDocument::getRoot() const {
    return _root;
}

void XMLDocument::deleteAllNodes() {
    _root = nullptr;
}

std::shared_ptr<Data> XMLDocument::findNode(const std::string &path) {
    // split path into nodes names
    std::vector<std::string> nodes_names = split(path, '/');
    // get the root node
    std::shared_ptr<Node> node = nullptr;
    // iterate over nodes names
    for (const auto& node_name : nodes_names) {
        // check if node exists
        if (node->hasChild(node_name)) {
            // get the node
            node = node->getChild(node_name);
        } else if (node_name == "@") {
            // get the data
            node = _root;
        }
    }
    if (node == nullptr) {
        return nullptr;
    }
    return node->getData();
}

bool XMLDocument::checkTags(const std::string &content, std::vector<std::string> invalidTagsNames) {
    // Pile pour stocker les balises ouvertes
    std::stack<std::string> tagStack;
    // Regex pour capturer les balises HTML (ouvertes et fermées avec des attributs)
    std::regex tagPattern(R"(<\/?([a-z]+)([^>]*)>)");
    std::smatch match;
    std::string::const_iterator searchStart(content.cbegin());

    // Parcours du contenu XML
    while (std::regex_search(searchStart, content.cend(), match, tagPattern)) {
        std::string tag = match[0];
        std::string tagName = match[1];
        // Vérifier si c'est une balise fermante
        if (tag[1] == '/') {
            // C'est une balise fermante, vérifier si elle correspond à la dernière ouverte
            if (tagStack.empty() || tagStack.top() != tagName) {
                std::stringstream ss;
                ss << "Error: incorrect tag: " << tag;
                _error = ss.str();
                return false;
            }
            // La balise correspond, on la retire de la pile
            std::cout << "Closing tag: " << tag << std::endl;
            tagStack.pop();
        } else {
            // C'est une balise ourvrante
            for (const std::string& invalidTag : invalidTagsNames) {
                if (tagName == invalidTag) {
                    std::stringstream ss;
                    ss << "Error: invalid tag: " << tag;
                    _error = ss.str();
                    return false;
                }
            }
            // on l'ajoute à la pile
            tagStack.push(tagName);
        }
        // Avancer la recherche dans la chaîne
        searchStart = match.suffix().first;
    }

    // Vérifier si la pile est vide à la fin
    if (!tagStack.empty()) {
        std::stringstream ss;
        ss << "Error: unclosed tag: " << tagStack.top();
        _error = ss.str();
        return false;
    }

    return true;
}

void XMLDocument::parseAttributes(const std::string &tag, const std::shared_ptr<XMLNode> node)
{
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

void XMLDocument::parse(const std::string& content, const std::shared_ptr<XMLNode> parent) {
    size_t pos = 0;
    while (pos < content.size()) {
        size_t start = content.find('<', pos);
        size_t end = content.find('>', start);
        if (start == std::string::npos || end == std::string::npos) break;

        std::string tag = content.substr(start + 1, end - start - 1);
        if (tag[0] != '/') {
            std::string nodeName = tag.substr(0, tag.find(' '));
            std::shared_ptr<XMLNode> node(new XMLNode(nodeName, nullptr, parent));
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
