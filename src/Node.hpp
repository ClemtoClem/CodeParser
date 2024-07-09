#ifndef __NODE_HPP
#define __NODE_HPP

#include <string>
#include <vector>
#include "Data.hpp"

class Node {
protected:
    std::string _type;
    std::string _name;
    Data *data;
    
    Node*  _parent;
    Node*  _firstChild;
    Node*  _lastChild;
    Node*  _nextChild;
    size_t _nbChildren;
    
public:
    Node(const std::string &type, const std::string &name, Data *data, Node *parent);

    ~Node();
    
    /**
     * @brief Retourne le type de ce noeud
     * @return std::string
     */
    const std::string &getType() const;

    /**
     * @brief Retourne le nom de ce noeud
     * @return std::string
     */
    const std::string &getName() const;

    /**
     * @brief Retourne le parent de ce noeud
     * @return Pointeur sur une classe Node
     */
    Node *getParent() const;

    /**
     * @brief Recherche un noeud enfant à partir de son nom
     * @param[in] name nom du noeud à rechercher
     * @return Pointeur sur une classe Node
     */
    Node *getChild(const std::string &name) const;

    /**
     * @brief Retourne le nombre de noeuds enfants
     * @return size_t
     */
    size_t getNbChildren() const;

    /**
     * @brief Ajouter un enfant
     * @param[in] newChild Pointeur sur une classe Node
     */
    void addChild(Node *newChild);

    /**
     * @brief Recherche un noeud à partir de son nom dans toute l'arborescence
     * @param[in] name nom du noeud à rechercher
     * @return Pointeur sur une classe Node
     */
    Node *getNode(const std::string &name) const;

    void deleteAllNodes();

    /**
     * @brief Convertir le noeud en chaine de caactère
     */
    virtual std::string toString(size_t tabulate = 0) const = 0;
};

#endif // __NODE_HPP