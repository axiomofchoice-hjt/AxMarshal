#include <inja/inja.hpp>

#include "BackEnd.h"
#include "BuiltinTypes.h"
#include "SrcGen.h"

namespace BackEnd {
std::string CodeGenerator::source(const std::string &baseName) {
    std::string res;
    res += "#include \"" + baseName + ".h\"\n\n";

    for (const FrontEnd::Block &block : blocks) {
        res += inja::render(SrcGen::__template_string(), block.json());
    }
    return res;
}
}  // namespace BackEnd