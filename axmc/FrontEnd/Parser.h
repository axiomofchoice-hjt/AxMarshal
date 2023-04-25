#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "Lexer.h"

namespace FrontEnd {

class Element {
   public:
    std::string key;
    std::string value;
    bool is_vector;
    bool is_array;
    bool is_pointer;
    uint64_t array_size;
    Element();
    explicit Element(const std::string &key);
    Element(const std::string &key, const std::string &value);
    nlohmann::json json() const;
};

class Block {
   public:
    std::string type;  // "enum" or "struct"
    std::string name;
    std::vector<Element> elements;

    void parse_enum_inner(Lexer::iter &it);
    void parse_struct_inner(Lexer::iter &it);
    nlohmann::json json() const;
};

std::vector<Block> Parser(const std::vector<Token> &tokens);
}  // namespace FrontEnd