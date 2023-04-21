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
    bool is_list;
    Element();
    explicit Element(const std::string &key);
    Element(const std::string &key, const std::string &value);
    nlohmann::json json() const;
};

class Block {
   public:
    std::string type;  // "enum" or "class"
    std::string name;
    std::vector<Element> elements;

    void parseEnumContent(Lexer::iter &it);
    void parseClassContent(Lexer::iter &it);
    nlohmann::json json() const;
};

std::vector<Block> Parser(const std::vector<Token> &tokens);
}  // namespace FrontEnd