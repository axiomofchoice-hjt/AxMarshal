#include "from_binary.h"

namespace axm {
namespace detail {

void __from_binary(bytes_iter &it, std::string &data) {
    uint32_t size;
    __from_binary(it, size);
    data.resize(size);
    __container_from_binary(it, data.begin(), data.end());
}

template <typename T>
void __var_u_from_binary(bytes_iter &it, T &data) {
    bool flag;
    uint32_t index = 0;
    data = 0;
    do {
        if (index == 8) {
            data |= (T)*it << (index * 7);
            it += 1;
            break;
        }
        flag = (*it & 0x80);
        data |= (T)(*it & 0x7f) << (index * 7);
        it += 1;
        index++;
    } while (flag);
}
void __var_from_binary(bytes_iter &it, uint32_t &data) {
    __var_u_from_binary(it, data);
}
void __var_from_binary(bytes_iter &it, int32_t &data) {
    uint32_t tmp;
    __var_u_from_binary(it, tmp);
    data = (tmp & 1 ? ~(tmp >> 1) : tmp >> 1);
}
void __var_from_binary(bytes_iter &it, uint64_t &data) {
    __var_u_from_binary(it, data);
}
void __var_from_binary(bytes_iter &it, int64_t &data) {
    uint64_t tmp;
    __var_u_from_binary(it, tmp);
    data = (tmp & 1 ? ~(tmp >> 1) : tmp >> 1);
}
}  // namespace detail
}  // namespace axm