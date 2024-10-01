#include "ConfigDocument.hpp"

ConfigDocument::ConfigDocument() : Document("CONFIG"), _root(nullptr) {
}

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

        _root = std::shared_ptr<ConfigNode>(new ConfigNode("root"));
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

std::shared_ptr<Node> ConfigDocument::getRoot() const {
    return std::shared_ptr<Node>(dynamic_cast<Node*>(_root.get()));
}

void ConfigDocument::deleteAllNodes() {
    _root.reset();
}

std::string ConfigDocument::toString() const {
    return std::string();
}

void ConfigDocument::parse(const std::string &content, std::shared_ptr<ConfigNode> parent) {
}
