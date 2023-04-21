#pragma once

#include <string>
#include <vector>

namespace FrontEnd {
class Token {
   public:
    static constexpr uint64_t UintInvalid = 0x1'0000'0000'0000;
    std::string value;

    explicit Token(const std::string &value);
    bool is_name() const;
    bool is_eof() const;
    bool is_int() const;
    uint64_t get_int() const;
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