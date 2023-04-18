#pragma once

#include <inja/inja.hpp>
#include <nlohmann/json.hpp>
#include <string>

namespace BackEnd {
class BackEnd;
class SrcGen {
   public:
    static std::string __template_string();
    static std::string gen(const BackEnd &);
};
}  // namespace BackEnd