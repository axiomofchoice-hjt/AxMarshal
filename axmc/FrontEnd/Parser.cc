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
Element::Element() : key(), value(), isList() {}
Element::Element(const std::string &key) : key(key), value(), isList() {}

Element::Element(const std::string &key, const std::string &value)
    : key(key), value(value), isList() {}

nlohmann::json Element::json() const {
    nlohmann::json data;
    data["key"] = key;
    data["hasValue"] = !value.empty();
    if (!value.empty()) {
        data["value"] = BasicType::translate(value);
    }
    data["isList"] = isList;
    data["isVar"] = BasicType::is_var_types(value);
    return data;
}

void Block::parseEnumContent(Lexer::iter &it) {
    while (*it != "}") {
        Element element;
        check(it->isName(), "enum element is not allowed");
        element.key = it->value;
        it += 1;

        if (*it == "(") {
            it += 1;
            if (it->isName()) {
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
        check(*it == ",", "enum element need `,`");
        it += 1;
    }
}

void Block::parseClassContent(Lexer::iter &it) {
    while (*it != "}") {
        Element element;

        check(it->isName(), "class element name is not allowed");
        element.key = it->value;
        it += 1;

        check(*it == ":", "class element need `:`");
        it += 1;

        check(it->isName(), "class element type is not allowed");
        element.value = it->value;
        it += 1;

        if (*it == "[") {
            it += 1;
            check(*it == "]", "list missing `]`");
            it += 1;
            element.isList = true;
        }
        elements.push_back(element);

        if (*it == "}") {
            break;
        }
        check(*it == ",", "class element need `,`");
        it += 1;
    }
}

std::vector<Block> Parser(const std::vector<Token> &tokens) {
    auto it = tokens.cbegin();
    std::vector<Block> res;
    while (!it->isEof()) {
        Block block;
        check(*it == "enum" || *it == "class",
              "block should begin with `enum` or `class`");
        block.type = it->value;
        it += 1;

        check(it->isName(), "block need a name");
        block.name = it->value;
        it += 1;

        check(*it == "{", "block need `{`");
        it += 1;

        auto rbrace = it;
        while (!rbrace->isEof() && *rbrace != "}") {
            rbrace += 1;
        }
        check(*rbrace == "}", "block need `}`");
        if (block.type == "enum") {
            block.parseEnumContent(it);
        } else if (block.type == "class") {
            block.parseClassContent(it);
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