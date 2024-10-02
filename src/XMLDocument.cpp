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
                ss << "incorrect tag: " << tag;
                _error = ss.str();
                return false;
            }
            // La balise correspond, on la retire de la pile
            //std::cout << "Closing tag: " << tag << std::endl;
            tagStack.pop();
        } else {
            // C'est une balise ourvrante
            for (const std::string& invalidTag : invalidTagsNames) {
                if (tagName == invalidTag) {
                    std::stringstream ss;
                    ss << "invalid tag: " << tag;
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
        ss << "unclosed tag: " << tagStack.top();
        _error = ss.str();
        return false;
    }

    return true;
}

void XMLDocument::parse(const std::string& content, const std::shared_ptr<XMLNode> parent) {
    // Regex to capture XML tags (open and close with attributes)
    std::regex tagPattern(R"(<\/?([a-z]+)([^>]*)>)");
    std::smatch match;
    std::string::const_iterator searchStart(content.cbegin());

    // Traverse the XML content
    while (std::regex_search(searchStart, content.cend(), match, tagPattern)) {
        std::string tag = match[0];
        std::string tagName = match[1];
        std::string attributes = match[2];

        if (tag[1] != '/') {
            // It's an opening tag
            std::shared_ptr<XMLNode> node(new XMLNode(tagName, nullptr, parent));
            parent->addChild(node);

            // Parse attributes using regex
            std::regex attrPattern(R"(([a-z]+)="([^"]*)\")");
            std::smatch attrMatch;
            std::string::const_iterator attrSearchStart(attributes.cbegin());

            while (std::regex_search(attrSearchStart, attributes.cend(), attrMatch, attrPattern)) {
                std::string name = attrMatch[1];
                std::string value = attrMatch[2];
                node->addAttribute(name, value);
                attrSearchStart = attrMatch.suffix().first;
            }

            // Find the closing tag
            std::string closeTag = "</" + tagName + ">";
            size_t closeTagStart = content.find(closeTag, match.suffix().first - content.cbegin());
            size_t closeTagEnd = closeTagStart + closeTag.size();
            std::string innerXML = content.substr(match.suffix().first - content.cbegin(), closeTagStart - (match.suffix().first - content.cbegin()));
            parse(innerXML, node);

            searchStart = content.cbegin() + closeTagEnd;
        } else {
            // It's a closing tag, move the search forward
            searchStart = match.suffix().first;
        }
    }
}