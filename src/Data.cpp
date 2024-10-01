#include "Data.hpp"

void ArrayData::pushData(const std::shared_ptr<Data> newData) {
    _array.push_back(newData);
}

void ArrayData::deleteData(size_t i) {
    if (i < _array.size()) {
        _array.erase(_array.begin() + i); // Retire l'élément du vector
    }
}

std::shared_ptr<Data> ArrayData::popData(size_t i) {
    if (i < _array.size()) {
        std::shared_ptr<Data> data = _array[i]; // Retourne le pointeur vers l'objet Data à l'index i
        _array.erase(_array.begin() + i); // Retire l'élément du vector
        return data;
    }
    return nullptr;
}

std::shared_ptr<Data> ArrayData::getData(size_t i) const {
    if (i < _array.size()) {
        return _array[i]; // Retourne le pointeur vers l'objet Data à l'index i
    }
    return nullptr;
}

size_t ArrayData::getSize() const {
    return _array.size();
}

std::string ArrayData::toString(const std::string &format) const {
    std::string result;
    if (format == "json" || format == "cfg") {
        result = "[ ";
        for (size_t i = 0; i < _array.size(); ++i) {
            if (i > 0) result += ", ";
            result += _array[i]->toString(format);
        }
        result += " ]";
        return result;
    } else if (format == "xml") {
        for (size_t i = 0; i < _array.size(); ++i) {
            if (i > 0) result += " ";
            result += _array[i]->toString(format);
        }
    }
    return result;
}

std::string CommentData::toString(const std::string &format) const { 
    std::string result;
    if (format == "cfg") {
        result = "# ";
        for (size_t i = 0; i < _comment.size(); ++i) {
            if (_comment[i] == '\n') {
                result += "\n";
                if (i + 1 < _comment.size() && _comment[i + 1] != '\n') {
                    result += "# ";
                }
            } else {
                result += _comment[i];
            }
        }
    } else if (format == "json") {
        result = "/* " + _comment + " */";
    } else if (format == "xml") {
        result = "<!-- " + _comment + " -->";
    }
    return result;
}