#include "to_json.h"

#include <rapidjson/document.h>

namespace axm {
namespace detail {
Value __to_rapidjson(const bool &data, Document::AllocatorType &allocator) {
    Value v;
    v.SetBool(data);
    return v;
}
Value __to_rapidjson(const char &data, Document::AllocatorType &allocator) {
    Value v;
    char buffer[2] = {data, 0};
    v.SetString(buffer, 1, allocator);
    return v;
}
Value __to_rapidjson(const uint8_t &data, Document::AllocatorType &allocator) {
    return __to_rapidjson((uint32_t)data, allocator);
}
Value __to_rapidjson(const uint32_t &data, Document::AllocatorType &allocator) {
    Value v;
    v.SetUint(data);
    return v;
}
Value __to_rapidjson(const uint64_t &data, Document::AllocatorType &allocator) {
    Value v;
    v.SetUint64(data);
    return v;
}
Value __to_rapidjson(const int8_t &data, Document::AllocatorType &allocator) {
    return __to_rapidjson((int32_t)data, allocator);
}
Value __to_rapidjson(const int32_t &data, Document::AllocatorType &allocator) {
    Value v;
    v.SetInt(data);
    return v;
}
Value __to_rapidjson(const int64_t &data, Document::AllocatorType &allocator) {
    Value v;
    v.SetInt64(data);
    return v;
}
Value __to_rapidjson(const float &data, Document::AllocatorType &allocator) {
    Value v;
    v.SetFloat(data);
    return v;
}
Value __to_rapidjson(const double &data, Document::AllocatorType &allocator) {
    Value v;
    v.SetDouble(data);
    return v;
}
Value __to_rapidjson(const std::string &data,
                     Document::AllocatorType &allocator) {
    Value v;
    v.SetString(data.c_str(), data.size(), allocator);
    return v;
}
}  // namespace detail
}  // namespace axm