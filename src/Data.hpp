#ifndef __DATA_HPP
#define __DATA_HPP

#include <string>
#include <vector>
#include <sstream>

class Data {
public:
    Data(const std::string& type) : _type(type) {}
    virtual std::string getType() const { return _type; }
    virtual std::string toString(const std::string &format) const = 0;
    virtual ~Data() {}
protected:
    std::string _type;
};

class CommentData : public Data {
public:
    CommentData(const std::string& comment) : Data("comment"), _comment(comment) {}
    std::string toString() const override;
protected:
    std::string _comment;
};

class ArrayData : public Data {
public:
    ArrayData() : Data("array") {}

    void pushData(SharedPtr<Data> newData);
    void deleteData(size_t i);
    SharedPtr<Data> popData(size_t i) const;
    SharedPtr<Data> getData(size_t i) const;
    size_t getSize() const;

    std::string toString(const std::string &format) const override;

protected:
    std::vector<SharedPtr<Data>> _array;
};

inline std::string typeidToString(const std::type_info& type) {
    if (type == typeid(uint8_t)) {
        return "uint8_t";
    } else if (type == typeid(uint16_t)) {
        return "uint16_t";
    } else if (type == typeid(uint32_t)) {
        return "uint32_t";
    } else if (type == typeid(uint64_t)) {
        return "uint64_t";
    } else if (type == typeid(int8_t)) {
        return "int8_t";
    } else if (type == typeid(int16_t)) {
        return "int16_t";
    } else if (type == typeid(int32_t)) {
        return "int32_t";
    } else if (type == typeid(int64_t)) {
        return "int64_t";
    } else if (type == typeid(int)) {
        return "int";
    } else if (type == typeid(float)) {
        return "float";
    } else if (type == typeid(double)) {
        return "double";
    } else if (type == typeid(bool)) {
        return "bool";
    } else if (type == typeid(std::string)) {
        return "string";
    } else {
        return "unknown";
    }
}

template<typename T>
class ValueData : public Data {
public:
    ValueData(T value) : Data(typeidToString(typeid(T))), _value(value) {}

    std::string toString(const std::string &format) const override {
        std::stringstream ss;
        if (_type == "string" && (format == "json" || format == "cfg")) {
            ss << "\"" << _value << "\"";
        } else {
            ss << _value;
        }
        return ss.str();
    }

    T& getValue() { return _value; }
    const T& getValue() const { return _value; }
    void setValue(const T& newValue) { _value = newValue; }

protected:
    T _value;
};

#endif // __DATA_HPP