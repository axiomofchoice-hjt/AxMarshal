#include "Json.h"

namespace axm {
namespace detail {
void __to_json(std::string &res, const char &data) {
    res.reserve(3);
    res += '"';
    res += data;
    res += '"';
}
void __to_json(std::string &res, const uint8_t &data) {
    __to_json(res, (uint32_t)data);
}
void __to_json(std::string &res, const uint32_t &data) {
    res += std::to_string(data);
}
void __to_json(std::string &res, const uint64_t &data) {
    res += std::to_string(data);
}
void __to_json(std::string &res, const int8_t &data) {
    __to_json(res, (int32_t)data);
}
void __to_json(std::string &res, const int32_t &data) {
    res += std::to_string(data);
}
void __to_json(std::string &res, const int64_t &data) {
    res += std::to_string(data);
}
void __to_json(std::string &res, const std::string &data) {
    res.reserve(2 + data.size());
    res += '"';
    res += data;
    res += '"';
}
}  // namespace detail
}  // namespace axm