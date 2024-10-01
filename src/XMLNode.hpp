#ifndef __XML_NODE_HPP
#define __XML_NODE_HPP

#include <map>
#include "Node.hpp"
#include <memory>

class XMLNode: public Node {
protected:
    std::map<std::string, std::string> _attributes;

public:
    XMLNode(const std::string &name, std::shared_ptr<Data> data = nullptr, std::shared_ptr<Node> parent = nullptr);

    // Méthodes pour manipuler les attributs
    void addAttribute(const std::string &name, const std::string &value);
    
    const std::string &getAttribute(const std::string &name) const;
    
    bool hasAttribute(const std::string &name) const;

    virtual std::string toString(size_t tabulate = 0) const override;
};

#endif // __XML_NODE_HPP