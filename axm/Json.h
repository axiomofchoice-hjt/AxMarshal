#pragma once

#include <string>

namespace axm {
namespace detail {
void __to_json(std::string &res, const char &data);
void __to_json(std::string &res, const uint8_t &data);
void __to_json(std::string &res, const uint32_t &data);
void __to_json(std::string &res, const uint64_t &data);
void __to_json(std::string &res, const int8_t &data);
void __to_json(std::string &res, const int32_t &data);
void __to_json(std::string &res, const int64_t &data);
void __to_json(std::string &res, const std::string &data);
template <typename T>
std::string to_json(const T &__data) {
    std::string __res;
    void __to_json(std::string &, const T &);
    __to_json(__res, __data);
    return __res;
}
}  // namespace detail

template <typename T>
std::string to_json(const T &__data) {
    return detail::to_json(__data);
}
}  // namespace axm