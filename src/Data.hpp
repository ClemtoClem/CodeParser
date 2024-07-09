#ifndef __DATA_HPP
#define __DATA_HPP

#include <string>
#include <vector>

class Data {
public:
    Data(const std::string type) : _type(type) {}
    virtual std::string getType() const { return _type; };
    virtual std::string toString() const = 0;
    virtual ~Data() {}
protected:
    std::string _type;
};

class CommentData : public Data {
public:
    CommentData(const std::string &comment) : Data("COMMENT"), _comment(comment) {}
    std::string toString() const override { return _comment; }
protected:
    std::string _comment;
};

class ArrayData : public Data {
public:
    ArrayData() : Data("ARRAY") {}

    void pushData(Data *newData);
    void deleteData(size_t i);
    Data *popData(size_t i) const;
    Data *getData(size_t i) const;
    size_t getSize() const;

    std::string toString() const override;

protected:
    std::vector<Data *> _array;
};

template<typename T>
class ValueData : public Data {
public:
    ValueData(const std::string &type, T value) : Data(type), value(value) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    T &getValue() { return value; }
    const T &getValue() const { return value; }
    void setValue(const T &newValue) { value = newValue; }

protected:
    T value;
};

class StringData : public ValueData<std::string> {
public:
    StringData(const std::string &value) : ValueData("STRING", value) {}
};

class S32Data : public ValueData<int32_t> {
public:
    S32Data(int32_t value) : ValueData("S32", value) {}
};

class U32Data : public ValueData<uint32_t> {
public:
    U32Data(uint32_t value) : ValueData("U32", value) {}
};

class F32Data : public ValueData<float> {
public:
    F32Data(float value) : ValueData("F32", value) {}
};

class F64Data : public ValueData<double> {
public:
    F64Data(double value) : ValueData("F64", value) {}
};

#endif // __DATA_HPP
