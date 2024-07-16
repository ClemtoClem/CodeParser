#include "Node.hpp"

Node::Node(const std::string& type, const std::string& name, SharedPtr<Data> data, SharedPtr<Node> parent)
    : _type(type), _name(name), _data(data), _parent(parent), _firstChild(nullptr), _lastChild(nullptr), _nextChild(nullptr), _nbChildren(0) {
}

Node::~Node() {
    deleteAllNodes();
}

const std::string& Node::getType() const {
    return _type;
}

const std::string& Node::getName() const {
    return _name;
}

SharedPtr<Node> Node::getParent() const {
    return _parent;
}

SharedPtr<Node> Node::getChild(const std::string& name) const {
    SharedPtr<Node> node = _firstChild;
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

void Node::addChild(const SharedPtr<Node>& newChild) {
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

SharedPtr<Node> Node::getNode(const std::string& name) const {
    SharedPtr<Node> node = _firstChild;
    while (node != nullptr) {
        if (node->_name == name) {
            break;
        } else {
            SharedPtr<Node> node2 = node->getNode(name);
            if (node2) {
                return node2;
            } else {
                node = node->_nextChild;
            }
        }
    }
    return nullptr;
}

void Node::deleteAllNodes() {
    while (_firstChild != nullptr) {
        _firstChild = _firstChild->_nextChild;
    }
    _lastChild = nullptr;
    _nbChildren = 0;
}

void Node::setData(SharedPtr<Data> data) {
    _data = data;
}

SharedPtr<Data> Node::getData() const {
    return _data;
}

std::string Node::getDataType() const {
    return _data.ok()? _data->getDataType() : "";
}

bool Node::hasData() const {
    return _data.ok();
}
