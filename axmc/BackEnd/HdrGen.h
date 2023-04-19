#pragma once

#include <nlohmann/json.hpp>

#include "../FrontEnd/FrontEnd.h"

namespace BackEnd {
class BackEnd;
class HdrGen {
   public:
    static std::string gen(const nlohmann::json &);
};
}  // namespace BackEnd