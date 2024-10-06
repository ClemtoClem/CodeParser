#include <iostream>
#include "XMLDocument.hpp"

int main() {
    XMLDocument xml_doc;
    if (!xml_doc.load("./data/test.xml")) {
        std::cerr << "Error parsing XML: " << xml_doc.getError() << std::endl;
        return 1;
    }

    std::shared_ptr<XMLNode> root = std::dynamic_pointer_cast<XMLNode>(xml_doc.getRoot());
    if (!root) {
        std::cerr << "Error: 'root' node not found" << std::endl;
        return 1;
    }
    
    std::cout << "Root node name: " << root->getName() << std::endl;

    std::shared_ptr<XMLNode>main_node = std::dynamic_pointer_cast<XMLNode>(root->getChild("main"));
    if (!main_node) {
        std::cerr << "Error: 'main' node not found" << std::endl;
        return 1;
    }

    std::cout << "Child node name: " << main_node->getName() << std::endl;
    std::cout << "Child attribute 'title': " << main_node->getAttribute("title") << std::endl;
    std::cout << "Child attribute 'version': " << main_node->getAttribute("version") << std::endl;

    std::shared_ptr<XMLNode>string_node = std::dynamic_pointer_cast<XMLNode>(main_node->getChild("string"));
    if (!string_node) {
        std::cerr << "Error: 'string' node should not exist" << std::endl;
        return 1;
    }

    std::cout << "'string' node name: " << string_node->getName() << std::endl;
    std::cout << "'string' attribute 'name': " << string_node->getAttribute("name") << std::endl;
    std::cout << "'string' node value type: " << string_node->getDataType() << std::endl;
    return 0;
}
