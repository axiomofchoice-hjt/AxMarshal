#pragma once
#include <inja/inja.hpp>
#include <nlohmann/json.hpp>
#include <string>

#include "../FrontEnd/FrontEnd.h"

namespace BackEnd {
class BackEnd;
class HdrGen {
   public:
    static std::string __template_string();
    static std::string gen(const BackEnd &);
};
}  // namespace BackEnd