#ifndef __CONFIG_DOCUMENT_HPP
#define __CONFIG_DOCUMENT_HPP

#include "Document.hpp"
#include "ConfigNode.hpp"
#include "SharedPtr.hpp"

class ConfigDocument : public Document {
public:
    ConfigDocument();
    ~ConfigDocument();

    bool load(const std::string &filename) override;
    bool save(const std::string &filename) override;

    const std::string &getError() const override;

    SharedPtr<Node> getRoot() const override;

    void deleteAllNodes() override;

    std::string toString() const;

private:
    SharedPtr<ConfigNode> _root;

    void parse(const std::string &content, SharedPtr<ConfigNode> parent);
};

#endif // __CONFIG_DOCUMENT_HPP