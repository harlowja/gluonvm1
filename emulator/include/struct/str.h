#pragma once

//#include "defs.h"
#include <string>

namespace gluon {

namespace containers {

// TODO: Replace this with C string or something later
class STLString {
   private:
    std::string value_;

   public:
    using ConstIterator = const char*;

    STLString() = default;
    STLString(const char* x) : value_(x) {}
    STLString(const char* x, size_t sz) : value_(x, sz) {}
    // stl_string(const stl_string &x): value_(x.value_) {}

    const char* c_str() const { return value_.c_str(); }

    void reserve(size_t sz) { value_.reserve(sz); }

    template <typename Append>
    STLString& operator+=(Append c) {
        value_ += c;
        return *this;
    }
    STLString& operator+=(const STLString& c) {
        value_ += c.value_;
        return *this;
    }

    bool operator!=(const char* s) const { return value_ != s; }
    bool operator!=(const STLString& s) const { return value_ != s.value_; }
    bool operator==(const char* s) const { return value_ == s; }
    bool operator==(const STLString& s) const { return value_ == s.value_; }
    bool operator<(const char* s) const { return value_ < s; }
    bool operator<(const STLString& s) const { return value_ < s.value_; }

    char operator[](size_t i) const { return value_[i]; }

    ConstIterator begin() const { return value_.data(); }
    ConstIterator end() const { return value_.data() + value_.length(); }
};

}  // ns containers

inline bool is_uppcase_latin(char c) {
    return c >= 'A' && c <= 'Z';
}
inline bool is_lowcase_latin(char c) {
    return c >= 'a' && c <= 'z';
}
inline bool is_latin(char c) {
    return is_uppcase_latin(c) || is_lowcase_latin(c);
}

// A string container
using Str = containers::STLString;

}  // ns gluon
