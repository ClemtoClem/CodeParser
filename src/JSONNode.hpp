#ifndef __JSONNODE_HPP
#define __JSONNODE_HPP

#include "Node.hpp"
#include <map>
#include <vector>

class JSONNode : public Node {
public:
    JSONNode(const std::string &name, SharedPtr<Data> data = nullptr, SharedPtr<Node> parent = nullptr);

    virtual std::string toString(size_t tabulate = 0) const override;

private:
    std::string _value;
};

#endif // __JSONNODE_HPP
