#include "Json.h"

namespace axm {
namespace detail {
void __to_json(std::string &res, const uint32_t &data) {
    res += std::to_string(data);
}
void __to_json(std::string &res, const uint64_t &data) {
    res += std::to_string(data);
}
void __to_json(std::string &res, const int32_t &data) {
    res += std::to_string(data);
}
void __to_json(std::string &res, const int64_t &data) {
    res += std::to_string(data);
}
}  // namespace detail
}  // namespace axm