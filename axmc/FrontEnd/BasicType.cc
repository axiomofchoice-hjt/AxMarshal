#include "BasicType.h"

namespace BasicType {
static const Info types[]{
    {"string", "std::string"}, {"u32", "uint32_t"}, {"u64", "uint64_t"}};

std::string translate(const std::string &name) {
    for (const auto &i : types) {
        if (name == i.name) {
            return i.output;
        }
    }
    return name;
}
}  // namespace BasicType