#pragma once

#include <string>
#include <vector>

#include "../FrontEnd/FrontEnd.h"

namespace BackEnd {
class BackEnd {
   public:
    std::string file_name;
    std::vector<FrontEnd::Block> blocks;

    BackEnd(const std::string &file_name,
            const std::vector<FrontEnd::Block> &blocks);
};
}  // namespace BackEnd