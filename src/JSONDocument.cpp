#include "JSONDocument.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

JSONDocument::JSONDocument() : Document("JSON"), _root(nullptr) {}

JSONDocument::~JSONDocument() {
    deleteAllNodes();
}

bool JSONDocument::load(const std::string &filename) {
    // Vérifier l'extension du fichier
    if (!checkExtensions(filename, {"json"})) {
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
        
        if (content[0] == '{') {
            _root = std::shared_ptr<JSONNode>(new JSONNode("root"));
            parse(content, _root);
        } else {
            _error = "File is not a JSON file";
        }
    } else {
        _error = "File is empty";
    }
    
    return _error.empty();
}

bool JSONDocument::save(const std::string &filename) {
    if (!_root) {
        _error = "No root node";
        return false;
    }

    // Vérifier l'extension du fichier
    if (!checkExtensions(filename, {"json"})) {
        _error = "File extension not allowed";
        return false;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        _error = "Unable to open file";
        return false;
    }

    file << toString();
    file.close();

    return true;
}

const std::string &JSONDocument::getError() const {
    return _error;
}

std::shared_ptr<Node> JSONDocument::getRoot() const {
    return std::shared_ptr<Node>(dynamic_cast<Node*>(_root.get()));
}

void JSONDocument::deleteAllNodes() {
    _root.reset();
    _root = nullptr;
}

std::string JSONDocument::toString() const {
    return (_root) ? _root->toString() : "{}";
}

void JSONDocument::parse(const std::string &content, std::shared_ptr<JSONNode> parent) {
}
