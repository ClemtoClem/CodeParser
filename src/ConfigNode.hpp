#ifndef __CONFIGNODE_HPP
#define __CONFIGNODE_HPP

#include "Node.hpp"
#include <map>
#include <vector>

class ConfigNode : public Node {
public:
    ConfigNode(const std::string &name, SharedPtr<Data> data = nullptr, SharedPtr<Node> parent = nullptr);

    virtual std::string toString(size_t tabulate = 0) const override;

private:
    std::string _value;
};

#endif // __CONFIGNODE_HPP
