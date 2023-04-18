#include "BackEnd.h"
#include "HdrGen.h"

namespace BackEnd {
std::string CodeGenerator::header() {
    std::string res;
    res += "#pragma once\n\n";
    res += "#include \"axm/axm.h\"\n\n";
    res += "#include <string>\n";
    res += "#include <vector>\n";
    res += "#include <variant>\n";
    for (const FrontEnd::Block &block : blocks) {
        res += inja::render(HdrGen::__template_string(), block.json());
    }
    return res;
}
}  // namespace BackEnd