#pragma once
#include <inja/inja.hpp>
#include <nlohmann/json.hpp>
#include <string>

namespace BackEnd {
class HdrGen {
   public:
    static std::string __template_string();
};
}  // namespace BackEnd