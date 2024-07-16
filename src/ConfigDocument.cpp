#include "ConfigDocument.hpp"

ConfigDocument::ConfigDocument() : _root(nullptr) {}

ConfigDocument::~ConfigDocument() {
    deleteAllNodes();
}

bool ConfigDocument::load(const std::string &filename) {
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

        _root = SharedPtr<ConfigNode>(new ConfigNode("root"));
        parse(content, _root);
    } else {
        _error = "File is empty";
    }

    return _error.empty();
}

bool ConfigDocument::save(const std::string &filename) {
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

const std::string &ConfigDocument::getError() const {
    return _error;
}

SharedPtr<Node> ConfigDocument::getRoot() const {
    return SharedPtr<Node>(dynamic_cast<Node*>(_root.get()));
}

void ConfigDocument::deleteAllNodes() {
    _root.remove();
}

std::string ConfigDocument::toString() const {
    return std::string();
}

void ConfigDocument::parse(const std::string &content, SharedPtr<ConfigNode> parent) {
}
