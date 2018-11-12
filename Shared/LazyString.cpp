#include "LazyString.h"
#include <stdarg.h>
#include <algorithm>
#include <ostream>

const Lazy<String::ValueT> EmptyLazyString = Lazy<String::ValueT>([]() {return string(); });
const size_t String::npos = (size_t) -1;

String::String()
    : lazy(EmptyLazyString)
{
}

String::String(ValueT &&value)
    : value(value), lazy(EmptyLazyString)
{
}

String::String(const ValueT &value)
    : value(value), lazy(EmptyLazyString)
{
}

String::String(const char *value)
    : value(value), lazy(EmptyLazyString)
{
}

String::String(const ::Lazy<ValueT>& lazy)
    : lazy(lazy), isLazy(true)
{
}

String& String::operator=(const String& other)
{
    isLazy = other.isLazy;
    lazy = other.lazy;
    value = other.value;
    return *this;
}

String& String::operator=(const ValueT& other)
{
    isLazy = false;
    lazy = EmptyLazyString;
    value = other;
    return *this;
}

String& String::operator=(const char* other)
{
    isLazy = false;
    lazy = EmptyLazyString;
    value = other;
    return *this;
}

String& String::operator+=(const String& other)
{
    isLazy = false;
    value += other.evaluate();
    return *this;
}

String& String::operator+=(const ValueT& other)
{
    isLazy = false;
    value += other;
    return *this;
}

String& String::operator+=(const char *other)
{
    isLazy = false;
    value += other;
    return *this;
}

String String::operator+(const String& other) const
{
    return String(evaluate() + other.evaluate());
}

String String::operator+(char c) const
{
    return String(evaluate() + c);
}

String::operator std::basic_string<char>()
{
    return evaluate();
}

String::operator std::basic_string<char>() const
{
    return evaluate();
}

bool String::operator==(const String& other) const
{
    return evaluate() == other.evaluate();
}

bool String::operator!=(const String& other) const
{
    return !this->operator==(other);
}

bool String::operator<(const String& other) const
{
    return evaluate() < other.evaluate();
}

char& String::operator[](size_t index)
{
    return evaluate()[index];
}

const char& String::operator[](size_t index) const
{
    return evaluate()[index];
}

size_t String::Length() const
{
    return evaluate().length();
}

size_t String::Find(const String& sub, size_t offset) const
{
    return evaluate().find(sub, offset);
}

size_t String::Find(char c, size_t offset) const
{
    return evaluate().find(c, offset);
}

const char *String::c_str() const
{
    return evaluate().c_str();
}

String String::Remove(size_t offset, size_t length) const
{
    return evaluate().erase(offset, length);
}

String String::Remove(char c, size_t offset) const
{
    auto copy = evaluate();
    copy.erase(std::remove(copy.begin() + offset, copy.end(), c), copy.end());
    return copy;
}

String String::Remove(const String& sub, size_t offset) const
{
    auto &&index = Find(sub, offset);
    if (index == String::npos)
    {
        return *this;
    }
    auto copy = *this;
    copy.Remove(index, sub.Length());
    return copy;
}

bool String::Empty() const
{
    return evaluate().empty();
}

String String::Lazy(const ::Lazy<String::ValueT>& lazy)
{
    return String(lazy);
}

String String::Lazy(const std::function<ValueT(void)> &lazy)
{
    return String(::Lazy<ValueT>(lazy));
}

String String::Format(const char* fmt, ...)
{
    char line[256];
    va_list args;

    va_start(args, fmt);
    vsprintf_s(line, fmt, args);
    va_end(args);

    return string(line);
}

ArrayList<String> String::Split(char delimeter) const
{
    ArrayList<String> strings;

    size_t start = 0u;
    while (true)
    {
        auto offset = Find(delimeter, start);
        if (offset == String::npos)
        {
            int count = (int) Length() - (int) start;
            if (count > 0)
            {
                auto &&section = Substring(start, count);
                strings.push_back(section);
            }
            break;
        }
        auto &&section = Substring(start, offset - start);
        strings.push_back(section);
        start += offset + 1u;
    }

    return strings;
}

ArrayList<String> String::SplitByFirst(char delimeter) const
{
    ArrayList<String> strings;

    auto offset = Find(delimeter);
    if (offset == String::npos)
    {
        strings.push_back(*this);
        return strings;
    }

    auto &&first = Substring(0, offset);
    auto &&second = Substring(offset + 1, Length());
    strings.push_back(first);
    strings.push_back(second);

    return strings;
}

String String::Substring(size_t offset) const
{
    return String(evaluate().substr(offset));
}

String String::Substring(size_t offset, size_t length) const
{
    return String(evaluate().substr(offset, length));
}

bool String::EndsWith(const String &endsWith) const
{
    auto &&sourceLen = Length();
    auto &&endsWithLen = endsWith.Length();
    auto &&end = Substring(0, sourceLen - endsWithLen);
    return end == endsWith;
}

std::basic_string<char>::const_iterator String::begin() const
{
    return evaluate().begin();
}

std::basic_string<char>::const_iterator String::end() const
{
    return evaluate().end();
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
    auto str = string.evaluate();
    os.write(str.c_str(), str.length());
    return os;
}