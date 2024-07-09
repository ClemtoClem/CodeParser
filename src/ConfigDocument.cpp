#include "ConfigDocument.hpp"

ConfigDocument::ConfigDocument() : _root(nullptr) {}

ConfigDocument::~ConfigDocument() {
    deleteAllNodes();
}

bool ConfigDocument::loadFile(const std::string &filename) {
    // Vérifier l'extension du fichier
    if (!checkExtensions(filename, {"cfg"})) {
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

        if(_root) delete _root;
        _root = new ConfigNode("root");
        parse(content, _root);
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

bool ConfigDocument::saveInFile(const std::string &filename) {
    if (!_root) {
        _error = "No root node";
        return false;
    }

    // Vérifier l'extension du fichier
    if (!checkExtensions(filename, {"cfg"})) {
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
