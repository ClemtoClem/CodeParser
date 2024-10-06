#ifndef __NODE_HPP
#define __NODE_HPP

#include <string>
#include <vector>
#include "Data.hpp"
#include <memory>

class Node {
protected:
    std::string _type;
    std::string _name;
    std::shared_ptr<Data> _data;
    
    std::shared_ptr<Node> _parent;
    std::shared_ptr<Node> _firstChild;
    std::shared_ptr<Node> _lastChild;
    std::shared_ptr<Node> _nextChild;
    size_t _nbChildren;
    
public:
    Node(const std::string &type, const std::string &name, std::shared_ptr<Data> data = nullptr, std::shared_ptr<Node> parent = nullptr);

    virtual ~Node();
    
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
    std::shared_ptr<Node> getParent() const;

    std::shared_ptr<Node> getFirstChild() const;

    std::shared_ptr<Node> getLastChild() const;

    std::shared_ptr<Node> getNextChild() const;

    bool hasChild(const std::string &name) const;

    /**
     * @brief Recherche un noeud enfant à partir de son nom
     * @param[in] name nom du noeud à rechercher
     * @return Pointeur sur une classe Node
     */
    std::shared_ptr<Node> getChild(const std::string &name) const;

    /**
     * @brief Retourne le nombre de noeuds enfants
     * @return size_t
     */
    size_t getNbChildren() const;

    /**
     * @brief Ajouter un enfant
     * @param[in] newChild Pointeur sur une classe Node
     */
    void addChild(std::shared_ptr<Node> newChild);

    /**
     * @brief Recherche un noeud à partir de son nom dans toute l'arborescence
     * @param[in] name nom du noeud à rechercher
     * @return Pointeur sur une classe Node
     */
    std::shared_ptr<Node> getNode(const std::string &name) const;

    /**
     * @brief Supprime le noeud et tous ses enfants
     */
    void deleteAllNodes();

    /**
     * @brief Convertir le noeud en chaine de caactère
     */
    virtual std::string toString(size_t tabulate = 0) const = 0;

    virtual void setData(std::shared_ptr<Data> data);

    template <typename T>
    void setValue(const T &value) {
        _type = typeid(T).name();
        _data = std::make_shared<ValueData<T>>(value);
    }

    virtual std::shared_ptr<Data> getData() const;

    virtual std::string getDataType() const;

    virtual bool hasData() const;
};

#endif // __NODE_HPP