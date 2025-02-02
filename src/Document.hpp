#ifndef __DOCUMENT_HPP
#define __DOCUMENT_HPP

#include <string>
#include <fstream>
#include <sstream>
#include "Node.hpp"
#include <memory>

bool checkExtensions(const std::string& filename, const std::vector<std::string>& extensions);

void removeEmptyLines(std::string& content);

class Document {
public:
    Document(const std::string& type) : _type(type) {}
    virtual ~Document() {}

    virtual bool load(const std::string& filename) = 0;
    virtual bool save(const std::string& filename) = 0;
    virtual const std::string& getError() const = 0;
    virtual std::shared_ptr<Node> getRoot() const = 0;
    virtual void deleteAllNodes() = 0;
protected:
    std::string _type;
    std::string _error;
};

#endif // __DOCUMENT_HPP
