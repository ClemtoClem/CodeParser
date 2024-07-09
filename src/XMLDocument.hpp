#ifndef __XML_DOCUMENT_HPP
#define __XML_DOCUMENT_HPP

#include <string>
#include <fstream>
#include <sstream>
#include "Document.hpp"
#include "XMLNode.hpp"

class XMLDocument: public Document {
public:
    XMLDocument();
    ~XMLDocument();

    bool loadFile(const std::string &filename) override;
    bool saveInFile(const std::string &filename) override;

    const std::string getError() const override;

    Node *getRoot() const override;

    void deleteAllNodes() override;
    
private:
    XMLNode *_root;
    std::string _error;

    void parseAttributes(const std::string &tag, XMLNode *node);
    void parse(const std::string &content, XMLNode *parent);
};

#endif // __XML_DOCUMENT_HPP