#include "Node.hpp"

Node::Node(const std::string &type, const std::string &name, Data *data, Node *parent)
    : _tyoe(type), _name(name), data(data), _parent(parent), _firstChild(nullptr), _lastChild(nullptr), _nextChild(nullptr), _nbChildren(0)
{
}

Node::~Node() {
    deleteAllNodes();
    delete data;
}

const std::string &Node::getType() const {
    return _type;
}

const std::string &Node::getName() const {
    return _name;
}

Node *Node::getParent() const {
    return _parent;
}

Node *Node::getChild(const std::string &name) const {
    Node *node = _firstChild;
    while (node != nullptr) {
        if (node->_name == name) {
            break;
        } else {
            node = node->_nextChild;
        }
    }
    return node;
}

size_t Node::getNbChildren() const {
    return _nbChildren;
}

void Node::addChild(Node *newChild) {
    if (newChild) {
        if (_lastChild) {
            _lastChild->_nextChild = newChild;
            _lastChild = newChild;
        } else {
            _firstChild = _lastChild = newChild;
        }
        _nbChildren++;
    }
}

Node *Node::getNode(const std::string &name) const {
    Node *node = _firstChild;
    while (node != nullptr) {
        if (node->_name == name) {
            break;
        } else {
            Node *node2 = node->getNode(name);
            if (node2) {
                node = node2;
                break;
            } else {
                node = node->_nextChild;
            }
        }
    }
    return node;
}

void Node::deleteAllNodes() {
    Node *node, *current;
    node = current = _firstChild;
    while (node != nullptr) {
        current = current->_nextChild;
        delete node;
        node = current;
    }
    _nbChildren = 0;
    _firstChild = _lastChild = nullptr;
}