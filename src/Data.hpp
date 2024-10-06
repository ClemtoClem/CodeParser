#ifndef __DATA_HPP
#define __DATA_HPP

#include <string>
#include <vector>
#include <sstream>
#include <memory>

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
    std::string toString(const std::string &format) const override;
protected:
    std::string _comment;
};

class ArrayData : public Data {
public:
    ArrayData() : Data("array") {}

    void pushData(std::shared_ptr<Data> newData);
    void deleteData(size_t i);
    std::shared_ptr<Data> popData(size_t i);
    std::shared_ptr<Data> getData(size_t i) const;
    size_t getSize() const;

    std::string toString(const std::string &format) const override;

protected:
    std::vector<std::shared_ptr<Data>> _array;
};

template <typename T>
inline std::string getNameTypeid() {
    if (typeid(T) == typeid(uint8_t))   return "uint8_t";
    if (typeid(T) == typeid(uint16_t))  return "uint16_t";
    if (typeid(T) == typeid(uint32_t))  return "uint32_t";
    if (typeid(T) == typeid(uint64_t))  return "uint64_t";
    if (typeid(T) == typeid(int8_t))    return "int8_t";
    if (typeid(T) == typeid(int16_t))   return "int16_t";
    if (typeid(T) == typeid(int32_t))   return "int32_t";
    if (typeid(T) == typeid(int64_t))   return "int64_t";
    if (typeid(T) == typeid(char))      return "char";
    if (typeid(T) == typeid(float))     return "float";
    if (typeid(T) == typeid(double))    return "double";
    if (typeid(T) == typeid(bool))      return "bool";
    if (typeid(T) == typeid(void*))     return "pointer";
    if (typeid(T) == typeid(std::string)) return "string";
    if (typeid(T) == typeid(std::vector<std::shared_ptr<Data>>)) return "array";
    return "unknown";
}

template<typename T>
class ValueData : public Data {
public:
    ValueData(T value) : Data(getNameTypeid<T>()), _value(value) {}

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