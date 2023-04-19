#pragma once

#include <map>
#include <string>

namespace BasicType {
class Info {
   public:
    const char *name;
    const char *output;
};

std::string translate(const std::string &name);
}  // namespace BasicType