#include "BackEnd.h"

#include <nlohmann/json_fwd.hpp>

namespace BackEnd {
BackEnd::BackEnd(const std::string &file_name,
                 const std::vector<FrontEnd::Block> &blocks)
    : file_name(file_name), blocks(blocks) {}

nlohmann::json BackEnd::json() const {
    nlohmann::json res;
    res["file_name"] = file_name;
    for (const auto &i : blocks) {
        res["blocks"].push_back(i.json());
    }
    return res;
}
}  // namespace BackEnd