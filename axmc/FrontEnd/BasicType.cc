#include "BasicType.h"

#include <map>
#include <set>

namespace BasicType {
class BasicTypeInfo {
   public:
    std::string output;
    explicit BasicTypeInfo(const std::string &output) : output(output) {}
};

static const std::set<std::string> var_types = {
    "var_int32",
    "var_int64",
    "var_uint32",
    "var_uint64",
};

static const std::map<std::string, BasicTypeInfo> basic_types = {
    {"string", BasicTypeInfo("std::string")},
    {"int32", BasicTypeInfo("int32_t")},
    {"int64", BasicTypeInfo("int64_t")},
    {"uint32", BasicTypeInfo("uint32_t")},
    {"uint64", BasicTypeInfo("uint64_t")},
    {"var_int32", BasicTypeInfo("int32_t")},
    {"var_int64", BasicTypeInfo("int64_t")},
    {"var_uint32", BasicTypeInfo("uint32_t")},
    {"var_uint64", BasicTypeInfo("uint64_t")}};

bool is_var_types(const std::string &name) { return var_types.count(name); }

std::string translate(const std::string &name) {
    if (basic_types.count(name)) {
        return basic_types.at(name).output;
    } else {
        return name;
    }
}
}  // namespace BasicType