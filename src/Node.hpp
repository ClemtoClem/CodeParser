#ifndef __NODE_HPP
#define __NODE_HPP

#include <string>
#include <vector>
#include "Data.hpp"
#include "SharedPtr.hpp"

class Node {
protected:
    std::string     _type;
    std::string     _name;
    SharedPtr<Data> _data;
    
    SharedPtr<Node> _parent;
    SharedPtr<Node> _firstChild;
    SharedPtr<Node> _lastChild;
    SharedPtr<Node> _nextChild;
    size_t          _nbChildren;
    
public:
    Node(const std::string &type, const std::string &name, SharedPtr<Data> data = nullptr, SharedPtr<Node> parent = nullptr);

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
    SharedPtr<Node> getParent() const;

    /**
     * @brief Recherche un noeud enfant à partir de son nom
     * @param[in] name nom du noeud à rechercher
     * @return Pointeur sur une classe Node
     */
    SharedPtr<Node> getChild(const std::string &name) const;

    /**
     * @brief Retourne le nombre de noeuds enfants
     * @return size_t
     */
    size_t getNbChildren() const;

    /**
     * @brief Ajouter un enfant
     * @param[in] newChild Pointeur sur une classe Node
     */
    void addChild(SharedPtr<Node> newChild);

    /**
     * @brief Recherche un noeud à partir de son nom dans toute l'arborescence
     * @param[in] name nom du noeud à rechercher
     * @return Pointeur sur une classe Node
     */
    SharedPtr<Node> getNode(const std::string &name) const;

    /**
     * @brief Supprime le noeud et tous ses enfants
     */
    void deleteAllNodes();

    /**
     * @brief Convertir le noeud en chaine de caactère
     */
    virtual std::string toString(size_t tabulate = 0) const = 0;

    virtual void setData(SharedPtr<Data> data);

    virtual SharedPtr<Data> getData() const;

    virtual std::string getDataType() const;

    virtual bool hasData() const;
};

#endif // __NODE_HPP