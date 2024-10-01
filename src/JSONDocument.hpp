#ifndef __JSONDOCUMENT_HPP
#define __JSONDOCUMENT_HPP

#include "Document.hpp"
#include "JSONNode.hpp"
#include <memory>

class JSONDocument : public Document {
public:
    JSONDocument();
    ~JSONDocument();

    bool load(const std::string &filename) override;
    bool save(const std::string &filename) override;

    const std::string &getError() const override;

    std::shared_ptr<Node> getRoot() const override;

    void deleteAllNodes() override;

    std::string toString() const;

private:
    std::shared_ptr<JSONNode> _root;

    void parse(const std::string &content, std::shared_ptr<JSONNode> parent);
};

#endif // __JSONDOCUMENT_HPP
