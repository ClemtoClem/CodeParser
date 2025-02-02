#ifndef __XML_DOCUMENT_HPP
#define __XML_DOCUMENT_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Document.hpp"
#include "XMLNode.hpp"
#include <memory>
#include "Utils.hpp"

class XMLDocument : public Document {
public:
    XMLDocument();
    ~XMLDocument();

    /**
     * @brief Load a XML file
     * @param filename The filename to load
     * @return True if the file is loaded, false otherwise
     */
    bool load(const std::string& filename) override;
    bool save(const std::string& filename) override;

    const std::string& getError() const override;

    std::shared_ptr<Node> getRoot() const override;

    void deleteAllNodes() override;

    std::shared_ptr<Data> findNode(const std::string& path);

private:
    std::shared_ptr<XMLNode> _root;
    
    void parseAttributes(std::shared_ptr<XMLNode> node, const std::string &content);
    void parse(std::shared_ptr<XMLNode> parent, const std::string& content);
};

#endif // __XML_DOCUMENT_HPP
