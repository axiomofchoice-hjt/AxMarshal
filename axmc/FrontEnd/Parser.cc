#include "Parser.h"

#include <iostream>
#include <string>

#include "BasicType.h"
#include "Lexer.h"

static inline void check(bool value, const char *s) {
    if (!value) {
        throw s;
    }
}

namespace FrontEnd {
Element::Element() : key(), value(), is_vector(), is_array(), is_pointer() {}
Element::Element(const std::string &key)
    : key(key), value(), is_vector(), is_array(), is_pointer() {}

Element::Element(const std::string &key, const std::string &value)
    : key(key), value(value), is_vector(), is_array(), is_pointer() {}

nlohmann::json Element::json() const {
    nlohmann::json data;
    data["key"] = key;
    data["has_value"] = !value.empty();
    if (!value.empty()) {
        data["value"] = BasicType::translate(value);
    }
    data["is_vector"] = is_vector;
    data["is_array"] = is_array;
    data["is_pointer"] = is_pointer;
    if (is_array) {
        data["array_size"] = array_size;
    }
    data["is_var"] = BasicType::is_var_types(value);
    return data;
}

void Block::parse_enum_inner(Lexer::iter &it) {
    while (*it != "}") {
        Element element;
        check(it->is_name(), "enum element is not allowed");
        element.key = it->value;
        it += 1;

        if (*it == "(") {
            it += 1;
            if (it->is_name()) {
                element.value = it->value;
                it += 1;
            }
            check(*it == ")", "enum element need `)`");
            it += 1;
        }
        elements.push_back(element);

        if (*it == "}") {
            break;
        }
        check(*it == "," || *it == ";", "enum element need `,` or `;`");
        it += 1;
    }
}

void Block::parse_struct_inner(Lexer::iter &it) {
    while (*it != "}") {
        Element element;

        check(it->is_name(), "struct element name is not allowed");
        element.key = it->value;
        it += 1;

        check(*it == ":", "struct element need `:`");
        it += 1;

        check(it->is_name(), "struct element type is not allowed");
        element.value = it->value;
        it += 1;

        if (*it == "[") {
            it += 1;
            if (it->is_int()) {  // 定长数组
                element.is_array = true;
                element.array_size = it->get_int();
                it += 1;
                check(element.array_size != Token::UintInvalid,
                      "list size is too large");
            } else {  // 不定长数组
                element.is_vector = true;
            }
            check(*it == "]", "list missing `]`");
            it += 1;
        } else if (*it == "*") {
            it += 1;
            element.is_pointer = true;
        }
        elements.push_back(element);

        if (*it == "}") {
            break;
        }
        check(*it == "," || *it == ";", "struct element need `,` or `;`");
        it += 1;
    }
}

std::vector<Block> Parser(const std::vector<Token> &tokens) {
    auto it = tokens.cbegin();
    std::vector<Block> res;
    while (!it->is_eof()) {
        Block block;
        check(*it == "enum" || *it == "struct",
              "block should begin with `enum` or `struct`");
        block.type = it->value;
        it += 1;

        check(it->is_name(), "block need a name");
        block.name = it->value;
        it += 1;

        check(*it == "{", "block need `{`");
        it += 1;

        auto rbrace = it;
        while (!rbrace->is_eof() && *rbrace != "}") {
            rbrace += 1;
        }
        check(*rbrace == "}", "block need `}`");
        if (block.type == "enum") {
            block.parse_enum_inner(it);
        } else if (block.type == "struct") {
            block.parse_struct_inner(it);
        }
        it += 1;

        res.push_back(block);
    }
    return res;
}

nlohmann::json Block::json() const {
    nlohmann::json data;
    data["type"] = type;
    data["name"] = name;
    for (auto &i : elements) {
        data["elements"].push_back(i.json());
    }
    return data;
}
}  // namespace FrontEnd