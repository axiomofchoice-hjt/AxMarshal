#include "Lexer.h"

#include <cctype>
#include <functional>

using str_iter = std::string::const_iterator;

static inline str_iter match(str_iter s, const std::function<bool(char)> &f) {
    while (f(*s)) {
        s++;
    }
    return s;
}

static inline bool isNameChar(char c) {
    return isalnum(c) || c == '_' || c == '$';
}

static inline bool isNameStartChar(char c) {
    return isalpha(c) || c == '_' || c == '$';
}

namespace FrontEnd {
Token::Token(const std::string &value) : value(value) {}
bool Token::isName() const {
    return !value.empty() && isNameStartChar(value[0]);
}
bool Token::isEof() const { return value.empty(); }
bool Token::operator==(const char *s) const { return value == s; }
bool Token::operator!=(const char *s) const { return value != s; }

Lexer::Lexer(const std::string &text) {
    str_iter it = text.cbegin();
    while (true) {
        Token token = Lexer::next(it);
        result.push_back(token);
        if (token.isEof()) {
            break;
        }
    }
}

Token Lexer::next(str_iter &it) {
    it = match(it, isspace);
    std::string res;
    if (*it == '\0') {
        res.clear();
    } else if (isNameChar(*it)) {
        str_iter t = match(it, isNameChar);
        res.assign(it, t);
        it = t;
    } else {
        str_iter t = it + 1;
        res.assign(it, t);
        it = t;
    }
    return Token(res);
}
}  // namespace FrontEnd