#ifndef __JSONDOCUMENT_HPP
#define __JSONDOCUMENT_HPP

#include "Document.hpp"
#include "JSONNode.hpp"
#include "SharedPtr.hpp"

class JSONDocument : public Document {
public:
    JSONDocument();
    ~JSONDocument();

    bool load(const std::string &filename) override;
    bool save(const std::string &filename) override;

    const std::string &getError() const override;

    SharedPtr<Node> getRoot() const override;

    void deleteAllNodes() override;

    std::string toString() const;

private:
    SharedPtr<JSONNode> _root;

    void parse(const std::string &content, SharedPtr<JSONNode> parent);
};

#endif // __JSONDOCUMENT_HPP
