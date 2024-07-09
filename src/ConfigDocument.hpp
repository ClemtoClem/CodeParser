#ifndef __CONFIG_DOCUMENT_HPP
#define __CONFIG_DOCUMENT_HPP

#include "Document.hpp"
#include "ConfigNode.hpp"

class ConfigDocument : public Document {
public:
    ConfigDocument();
    ~ConfigDocument();

    bool loadFile(const std::string &filename) override;
    bool saveInFile(const std::string &filename) override;

    const std::string getError() const override;

    Node *getRoot() const override;

    void deleteAllNodes() override;

    std::string toString() const;

private:
    ConfigNode *_root;
    std::string _error;

    void parse(const std::string &content, ConfigNode *parent);
};

#endif // __CONFIG_DOCUMENT_HPP