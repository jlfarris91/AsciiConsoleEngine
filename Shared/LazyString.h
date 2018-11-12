#pragma once
#include "Lazy.h"
#include "ArrayList.h"

class String
{
public:
    typedef std::string ValueT;

    String();
    String(ValueT &&value);
    String(const ValueT &value);
    String(const char *value);

    String &operator=(const String &other);
    String &operator=(const ValueT &other);
    String &operator=(const char *other);

    String &operator+=(const String &other);
    String &operator+=(const ValueT &other);
    String &operator+=(const char *other);

    String operator+(const String &other) const;
    String operator+(char c) const;

    operator ValueT();
    operator ValueT() const;

    bool operator==(const String &other) const;
    bool operator!=(const String &other) const;
    bool operator<(const String &other) const;
    
    char &operator[](size_t index);
    const char &operator[](size_t index) const;

    size_t Length() const;
    size_t Find(const String &sub, size_t offset = 0) const;
    size_t Find(char c, size_t offset = 0) const;
    const char *c_str() const;

    String Remove(size_t offset, size_t length) const;
    String Remove(const String &sub, size_t offset = 0) const;
    String Remove(char c, size_t offset = 0) const;

    ArrayList<String> Split(char delimeter) const;
    ArrayList<String> SplitByFirst(char delimeter) const;
    String Substring(size_t offset) const;
    String Substring(size_t offset, size_t length) const;
    bool EndsWith(const String &endsWith) const;

    ValueT::const_iterator begin() const;
    ValueT::const_iterator end() const;

    bool Empty() const;

    static String Lazy(const Lazy<ValueT> &lazy);
    static String Lazy(const std::function<ValueT(void)> &func);
    static String Format(const char *fmt...);

    static const size_t npos;

    friend std::ostream& operator<<(std::ostream& os, const String& dt);

private:

    explicit String(const ::Lazy<ValueT> &lazy);

    ValueT &evaluate() const
    {
        auto &&valueRef = *const_cast<ValueT*>(&value);
        if (isLazy)
        {
            valueRef = lazy.Value();
        }
        return valueRef;
    }

    ValueT value;
    ::Lazy<ValueT> lazy;
    bool isLazy = false;
};

namespace std
{
//namespace tr1
//{
// Specializations for unordered containers

template <>
struct hash<String> : public unary_function<String, size_t>
{
    size_t operator()(const String& value) const
    {
        return hash<String::ValueT>().operator()(value);
    }
};

//} // namespace tr1

template <>
struct equal_to<String> : public unary_function<String, bool>
{
    bool operator()(const String& x, const String& y) const
    {
        return x == y;
    }
};

} // namespace std
