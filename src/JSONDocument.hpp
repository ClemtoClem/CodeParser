#ifndef __JSONDOCUMENT_HPP
#define __JSONDOCUMENT_HPP

#include "Document.hpp"
#include "JSONNode.hpp"

class JSONDocument : public Document {
public:
    JSONDocument();
    ~JSONDocument();

    bool loadFile(const std::string &filename) override;
    bool saveInFile(const std::string &filename) override;

    const std::string getError() const override;

    Node *getRoot() const override;

    void deleteAllNodes() override;

    std::string toString() const;

private:
    JSONNode *_root;
    std::string _error;

    void parse(const std::string &content, JSONNode *parent);
};

#endif // __JSONDOCUMENT_HPP
