#include "Lexer.h"

#include <cctype>
#include <functional>
#include <limits>

using str_iter = std::string::const_iterator;

static inline str_iter skip_if(str_iter s, const std::function<bool(char)> &f) {
    while (f(*s)) {
        s += 1;
    }
    return s;
}

static inline bool is_name_char(char c) {
    return isalnum(c) || c == '_' || c == '$';
}

static inline bool is_name_char_start(char c) {
    return isalpha(c) || c == '_' || c == '$';
}

namespace FrontEnd {
Token::Token(const std::string &value) : value(value) {}
bool Token::is_name() const {
    return !value.empty() && is_name_char_start(value[0]);
}
bool Token::is_eof() const { return value.empty(); }
bool Token::is_int() const {
    return std::all_of(value.begin(), value.end(), isdigit);
}
uint64_t Token::get_int() const {
    uint64_t res = 0;
    for (auto it = value.rbegin(); it != value.rend(); ++it) {
        res = std::min(Token::UintInvalid, res * 10 + (*it - '0'));
    }
    return res;
}
bool Token::operator==(const char *s) const { return value == s; }
bool Token::operator!=(const char *s) const { return value != s; }

Lexer::Lexer(const std::string &text) {
    str_iter it = text.cbegin();
    while (true) {
        Token token = Lexer::next(it);
        result.push_back(token);
        if (token.is_eof()) {
            break;
        }
    }
}

Token Lexer::next(str_iter &it) {
    it = skip_if(it, isspace);
    std::string res;
    while (*it == '/' && it[1] == '/') {
        it = skip_if(it, [](char c) { return !(c == '\n' || c == '\0'); });
        it = skip_if(it, isspace);
    }
    if (*it == '\0') {
        res.clear();
    } else if (is_name_char(*it)) {
        str_iter t = skip_if(it, is_name_char);
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