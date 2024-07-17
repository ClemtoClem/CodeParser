#ifndef __XML_DOCUMENT_HPP
#define __XML_DOCUMENT_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Document.hpp"
#include "XMLNode.hpp"
#include "SharedPtr.hpp"
#include "Utils.hpp"

class XMLDocument : public Document {
public:
    XMLDocument();
    ~XMLDocument();

    bool load(const std::string& filename) override;
    bool save(const std::string& filename) override;

    const std::string& getError() const override;

    SharedPtr<Node> getRoot() const override;

    void deleteAllNodes() override;

    template <typename T>
    SharedPtr<Data> operator[](const std::string& path, const T& value) override {
        // split path into nodes names
        std::vector<std::string> nodes_names = split(path, '/');
        // get the root node
        SharedPtr<Node> node = nullptr;
        // iterate over nodes names
        for (const auto& node_name : nodes_names) {
            // check if node exists
            if (node->hasChild(node_name)) {
                // get the node
                node = node->getChild(node_name);
            } else if (node_name == "@") {
                // get the data
                node = _root->cast<Node>();
            }
        }
    }

private:
    SharedPtr<XMLNode> _root;

    void parseAttributes(const std::string& tag, const SharedPtr<XMLNode>& node);
    void parse(const std::string& content, const SharedPtr<XMLNode>& parent);
};

#endif // __XML_DOCUMENT_HPP
