#include "JSONDocument.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

JSONDocument::JSONDocument() : _root(nullptr) {}

JSONDocument::~JSONDocument() {
    deleteAllNodes();
}

bool JSONDocument::loadFile(const std::string &filename) {
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
            if (_root) delete _root;
            _root = new JSONNode("root");
            parseJSON(content, _root);
        } else {
            _error = "File is not a JSON file";
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

bool JSONDocument::saveInFile(const std::string &filename) {
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

const std::string JSONDocument::getError() const {
    return _error;
}

Node *JSONDocument::getRoot() const {
    return _root;
}

void JSONDocument::deleteAllNodes() {
    delete _root;
    _root = nullptr;
}

std::string JSONDocument::toString() const {
    return (_root) ? _root->toString() : "{}";
}

void JSONDocument::parse(const std::string &content, JSONNode *parent) {
}
