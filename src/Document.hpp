#ifndef __DOCUMENT_HPP
#define __DOCUMENT_HPP

#include <string>
#include <fstream>
#include <sstream>
#include "Node.hpp"

bool checkExtensions(const std::string &filename, const std::vector<std::string> &extensions);

void removeEmptyLines(std::string &content);

class Document {
public:
    Document(std::string &type) : _type(type) {}
    virtual bool loadFile(const std::string &filename) = 0;
    virtual bool saveInFile(const std::string &filename) = 0;
    virtual const std::string getError() const = 0;
    virtual Node *getRoot() const = 0;
    virtual void deleteAllNodes() = 0;

private:
    std::string _type;
};

#endif // __DOCUMENT_HPP