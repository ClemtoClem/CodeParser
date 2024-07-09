#include "Data.hpp"

void ArrayData::pushData(Data *newData) {
    _array.push_back(newData);
}

void ArrayData::deleteData(size_t i) {
    if (i < _array.size()) {
        delete _array[i]; // Supprime l'objet Data pointé par _array[i]
        _array.erase(_array.begin() + i); // Retire l'élément du vector
    }
}

Data *ArrayData::popData(size_t i) const {
    if (i < _array.size()) {
        Data *data = _array[i]; // Retourne le pointeur vers l'objet Data à l'index i
        _array.erase(_array.begin() + i); // Retire l'élément du vector
        return data;
    }
    return nullptr;
}

Data *ArrayData::getData(size_t i) const {
    if (i < _array.size()) {
        return _array[i]; // Retourne le pointeur vers l'objet Data à l'index i
    }
    return nullptr;
}

size_t ArrayData::getSize() const {
    return _array.size();
}

std::string ArrayData::toString() const {
    std::string result = "[ ";
    for (size_t i = 0; i < _array.size(); ++i) {
        if (i > 0) result += ", ";
        result += _array[i]->toString();
    }
    result += " ]";
    return result;
}
