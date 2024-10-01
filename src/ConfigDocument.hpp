#ifndef __CONFIG_DOCUMENT_HPP
#define __CONFIG_DOCUMENT_HPP

#include "Document.hpp"
#include "ConfigNode.hpp"
#include <memory>

class ConfigDocument : public Document {
public:
    ConfigDocument();
    ~ConfigDocument();

    bool load(const std::string &filename) override;
    bool save(const std::string &filename) override;

    const std::string &getError() const override;

    std::shared_ptr<Node> getRoot() const override;

    void deleteAllNodes() override;

    std::string toString() const;

private:
    std::shared_ptr<ConfigNode> _root;

    void parse(const std::string &content, std::shared_ptr<ConfigNode> parent);
};

#endif // __CONFIG_DOCUMENT_HPP