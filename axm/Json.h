#pragma once

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <string>
#include <vector>

namespace axm {
namespace detail {
using rapidjson::Document;
using rapidjson::Value;
Value __to_rapidjson(const bool &, Document::AllocatorType &);
Value __to_rapidjson(const char &, Document::AllocatorType &);
Value __to_rapidjson(const uint8_t &, Document::AllocatorType &);
Value __to_rapidjson(const uint32_t &, Document::AllocatorType &);
Value __to_rapidjson(const uint64_t &, Document::AllocatorType &);
Value __to_rapidjson(const int8_t &, Document::AllocatorType &);
Value __to_rapidjson(const int32_t &, Document::AllocatorType &);
Value __to_rapidjson(const int64_t &, Document::AllocatorType &);
Value __to_rapidjson(const float &, Document::AllocatorType &);
Value __to_rapidjson(const double &, Document::AllocatorType &);
Value __to_rapidjson(const std::string &, Document::AllocatorType &);
template <typename T>
Value __to_rapidjson(const std::vector<T> &data,
                     Document::AllocatorType &allocator) {
    Value v;
    v.SetArray();
    for (auto &i : data) {
        v.PushBack(__to_rapidjson(i, allocator), allocator);
    }
    return v;
}
template <typename T>
std::string to_json(const T &__data) {
    Document doc;
    Value __to_rapidjson(const T &, Document::AllocatorType &);
    Value v = __to_rapidjson(__data, doc.GetAllocator());
    rapidjson::StringBuffer jsonBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(jsonBuffer);
    v.Accept(writer);
    return jsonBuffer.GetString();
}
}  // namespace detail

template <typename T>
std::string to_json(const T &__data) {
    return detail::to_json(__data);
}
}  // namespace axm