#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace BackEnd {
class BackEnd;
class SrcGen {
   public:
    static std::string gen(const nlohmann::json &);
};
}  // namespace BackEnd