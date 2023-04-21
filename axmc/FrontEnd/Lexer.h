#pragma once

#include <string>
#include <vector>

namespace FrontEnd {
class Token {
   public:
    std::string value;

    explicit Token(const std::string &value);
    bool is_name() const;
    bool is_eof() const;
    bool operator==(const char *) const;
    bool operator!=(const char *) const;
};
class Lexer {
   private:
    static Token next(std::string::const_iterator &);

   public:
    using iter = std::vector<Token>::const_iterator;
    std::vector<Token> result;
    Lexer(const std::string &);
};
}  // namespace FrontEnd