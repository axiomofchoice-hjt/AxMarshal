#pragma once
#include <concepts>
#include <cstdint>
#include <vector>

namespace axm {
namespace detail {
using bytes = std::vector<uint8_t>;
using bytes_iter = std::vector<uint8_t>::const_iterator;
template <typename T>
concept is_number = std::integral<T> || std::floating_point<T>;
}  // namespace detail
}  // namespace axm