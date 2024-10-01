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
        std::cerr << "Error: root node not found" << std::endl;
        return 1;
    }
    
    std::cout << "Root node name: " << root->getName() << std::endl;

    std::shared_ptr<XMLNode>child1 = std::dynamic_pointer_cast<XMLNode>(root->getChild("child1"));
    if (!child1) {
        std::cerr << "Error: child1 node not found" << std::endl;
        return 1;
    }

    std::cout << "Child node name: " << child1->getName() << std::endl;
    std::cout << "Child attribute attr1: " << child1->getAttribute("attr1") << std::endl;
    std::cout << "Child attribute attr2: " << child1->getAttribute("attr2") << std::endl;

    std::shared_ptr<XMLNode>subchild = std::dynamic_pointer_cast<XMLNode>(child1->getChild("subchild"));
    if (!subchild) {
        std::cerr << "Error: subchild node should not exist" << std::endl;
        return 1;
    }

    std::cout << "Subchild node name: " << subchild->getName() << std::endl;
    std::cout << "Subchild attribute attr3: " << subchild->getAttribute("attr3") << std::endl;
    
    std::shared_ptr<XMLNode>child2 = std::dynamic_pointer_cast<XMLNode>(root->getChild("child2"));
    if (!child2) {
        std::cerr << "Error: child2 node not found" << std::endl;
        return 1;
    }

    std::cout << "Child node name: " << child2->getName() << std::endl;
    std::cout << "Child attribute attr4: " << child2->getAttribute("attr4") << std::endl;


    return 0;
}
