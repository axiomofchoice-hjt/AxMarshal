#include "BackEnd.h"

namespace BackEnd {
BackEnd::BackEnd(const std::string &file_name,
                 const std::vector<FrontEnd::Block> &blocks)
    : file_name(file_name), blocks(blocks) {}
}  // namespace BackEnd