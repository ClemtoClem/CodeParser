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

    if (!content.empty()) {
        removeEmptyLines(content);

        _root = std::shared_ptr<XMLNode>(new XMLNode("root"));
        parse(_root, content);
    } else {
        _error = "File is empty";
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

void XMLDocument::parseAttributes(std::shared_ptr<XMLNode> node, const std::string &attr_content) {
    std::regex attrRegex(R"(([a-zA-Z_:][a-zA-Z0-9_.:-]*)\s*=\s*\"(.*?)\")");  // Expression régulière pour les attributs
    std::smatch match;

    std::string::const_iterator searchStart(attr_content.cbegin());
    while (std::regex_search(searchStart, attr_content.cend(), match, attrRegex)) {
        std::string name = match[1].str();     // Nom de l'attribut
        std::string value = match[2].str();    // Valeur de l'attribut
        node->addAttribute(name, value);       // Ajouter l'attribut au nœud
        searchStart = match.suffix().first;    // Avancer dans la chaîne
    }
}

void XMLDocument::parse(std::shared_ptr<XMLNode> parent, const std::string& content) {
    // Regex pour une balise ouvrante/fermante
    std::regex nodeRegex(R"(<\s*(/?)\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*([^>/]*)\s*(/?)\s*>)");
    std::smatch match;

    std::string::const_iterator searchStart(content.cbegin());
    std::vector<std::string> openTagsName;
    std::vector<std::shared_ptr<XMLNode>> stackNodes = {parent};

    while (std::regex_search(searchStart, content.cend(), match, nodeRegex)) {
        bool isClosingTag = match[1].matched && match[1].str() == "/";  // '/' au début de la balise
        std::string tagName = match[2].str();                           // Nom de la balise
        std::string attributes = match[3].str();                        // Attributs éventuels
        bool isSelfClosingTag = match[4].matched && match[4].str() == "/"; // '/' à la fin de la balise (balise auto-fermante)

        // Vérification des erreurs
        if (isClosingTag && isSelfClosingTag) {
            _error = "A tag cannot be closing and self-closing at the same time";
            return;
        }
        if (isClosingTag && !attributes.empty()) {
            _error = "A closing tag cannot have attributes";
            return;
        }

        // Si c'est une balise fermante
        if (isClosingTag) {
            //std::cout << "Closing Tag " << openTagsName.size() << ": " << tagName << std::endl;

            std::string openTagName = openTagsName.back();
            openTagsName.pop_back();
            if (tagName != openTagName) {
                _error = "Mismatched closing tag: " + tagName;
                return;
            }

            // Le nœud antécédent redevient parent
            parent = stackNodes.back();
            stackNodes.pop_back();
        }
        
        // Si c'est une balise auto-fermante, on ne faite pas d'appel récursif
        else if (isSelfClosingTag) {
            //std::cout << "Self-Closing Tag " << openTagsName.size() << ": " << tagName << std::endl;

            std::shared_ptr<XMLNode> newNode = std::shared_ptr<XMLNode>(new XMLNode(tagName, nullptr, parent));
            if (!attributes.empty()) {
                parseAttributes(newNode, attributes);
            }
            parent->addChild(newNode);
        }
        
        // Si c'est une balise ouvrante
        else {

            std::shared_ptr<XMLNode> newNode = std::shared_ptr<XMLNode>(new XMLNode(tagName, nullptr, parent));
            if (!attributes.empty()) {
                parseAttributes(newNode, attributes);
            }
            //std::cout << "Parent: " << parent->getName() << std::endl;
            parent->addChild(newNode);

            // Le nouveau nœud devient parent
            stackNodes.push_back(newNode);
            parent = newNode;

            openTagsName.push_back(tagName);
            //std::cout << "Opening Tag " << openTagsName.size() << ": " << tagName << std::endl;
        }

        // Avancer dans la recherche
        searchStart = match.suffix().first;
    }
}
