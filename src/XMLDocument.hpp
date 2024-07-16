#ifndef __XML_DOCUMENT_HPP
#define __XML_DOCUMENT_HPP

#include <string>
#include <fstream>
#include <sstream>
#include "Document.hpp"
#include "XMLNode.hpp"
#include "SharedPtr.hpp"

class XMLDocument : public Document {
public:
    XMLDocument();
    ~XMLDocument();

    bool load(const std::string& filename) override;
    bool save(const std::string& filename) override;

    const std::string& getError() const override;

    SharedPtr<Node> getRoot() const override;

    void deleteAllNodes() override;

private:
    SharedPtr<XMLNode> _root;

    void parseAttributes(const std::string& tag, const SharedPtr<XMLNode>& node);
    void parse(const std::string& content, const SharedPtr<XMLNode>& parent);
};

#endif // __XML_DOCUMENT_HPP
