#include "Node.hpp"

Node::Node(const std::string& type, const std::string& name, std::shared_ptr<Data> data, std::shared_ptr<Node> parent)
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

std::shared_ptr<Node> Node::getParent() const {
    return _parent;
}

std::shared_ptr<Node> Node::getFirstChild() const {
    return _firstChild;
}

std::shared_ptr<Node> Node::getLastChild() const {
    return _lastChild;
}

std::shared_ptr<Node> Node::getNextChild() const {
    return _nextChild;
}

bool Node::hasChild(const std::string &name) const {
    std::shared_ptr<Node> node = _firstChild;
    while (node != nullptr) {
        if (node->_name == name) {
            return true;
        } else {
            node = node->_nextChild;
        }
    }
    return false;
}

std::shared_ptr<Node> Node::getChild(const std::string& name) const {
    std::shared_ptr<Node> node = _firstChild;
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

void Node::addChild(const std::shared_ptr<Node> newChild) {
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

std::shared_ptr<Node> Node::getNode(const std::string& name) const {
    std::shared_ptr<Node> node = _firstChild;
    while (node != nullptr) {
        if (node->_name == name) {
            break;
        } else {
            std::shared_ptr<Node> node2 = node->getNode(name);
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

void Node::setData(std::shared_ptr<Data> data) {
    if (_data!= nullptr) {
        _data.reset();
    }
    _data = data;
}

std::shared_ptr<Data> Node::getData() const {
    return _data;
}

std::string Node::getDataType() const {
    return (_data != nullptr)? _data->getType() : "unknown";
}

bool Node::hasData() const {
    return (_data != nullptr);
}
