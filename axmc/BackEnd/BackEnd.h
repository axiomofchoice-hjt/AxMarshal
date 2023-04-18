#pragma once

#include <string>
#include <vector>

#include "../FrontEnd/FrontEnd.h"

namespace BackEnd {
class CodeGenerator {
   public:
    // size_t indent;
    std::vector<FrontEnd::Block> blocks;

    CodeGenerator(const std::vector<FrontEnd::Block> &blocks);
    std::string header();
    std::string source(const std::string &baseName);
};
}  // namespace BackEnd