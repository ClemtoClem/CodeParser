#ifndef __DOCUMENT_HPP
#define __DOCUMENT_HPP

#include <string>
#include <fstream>
#include <sstream>
#include "Node.hpp"
#include "SharedPtr.hpp"

bool checkExtensions(const std::string& filename, const std::vector<std::string>& extensions);

void removeEmptyLines(std::string& content);

class Document {
public:
    Document(const std::string& type) : _type(type) {}
    virtual ~Document() {}

    virtual bool load(const std::string& filename) = 0;
    virtual bool save(const std::string& filename) = 0;
    virtual const std::string& getError() const = 0;
    virtual SharedPtr<Node> getRoot() const = 0;
    virtual void deleteAllNodes() = 0;

    template <typename T>
    virtual SharedPtr<Data> operator[](const std::string& path, const T& value) = 0;
protected:
    std::string _type;
    std::string _error;
};

#endif // __DOCUMENT_HPP
