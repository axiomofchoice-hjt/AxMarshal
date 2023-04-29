#include "HdrGen.h"

#include <inja/inja.hpp>
#include <nlohmann/json.hpp>

#include "BackEnd.h"

static auto header_template_string = R"__template__(
#pragma once

#include <memory>
#include <rapidjson/document.h>
#include <string>
#include <variant>
#include <vector>

#include "axm/axm.h"

## for block in blocks
class {{ block.name }};
## endfor
)__template__";

static auto block_template_string = R"__template__(
namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const {{ name }} &);
void __from_binary(std::vector<uint8_t>::const_iterator &, {{ name }} &);
Value __to_rapidjson(const {{ name }} &, Document::AllocatorType &);
}
}
{% if type == "enum" %}
class {{ name }} {
   private:
    enum class __Tag {
        __UNDEF,
## for i in elements
        {{ i.key }} {% if not loop.is_last %},{% endif %}
## endfor
    };
    using __Data = std::variant<
        std::monostate,
## for i in elements
        {% if i.has_value %}{{ i.value }}{% else %}std::monostate{% endif %}
        {% if not loop.is_last %},{% endif %}
## endfor
    >;
    __Data __data;
    __Tag __get_tag() const;
    template <__Tag key>
    const auto &__get_value() const {
        return std::get<static_cast<size_t>(key)>(__data);
    }
    template <__Tag key>
    auto &__get_value() {
        return std::get<static_cast<size_t>(key)>(__data);
    }
    {{ name }}(const __Data &data);
    {{ name }}(__Data &&data);
   public:
    {{ name }}();
    {{ name }}(const {{ name }} &);
    {{ name }}({{ name }} &&);
    {{ name }} &operator=(const {{ name }} &other);
    {{ name }} &operator=({{ name }} &&other);
    {{ name }} &operator=(std::nullptr_t);
## for i in elements
    static {{ name }} {{ i.key }}({% if i.has_value %}{{ i.value }}{% endif %});
    bool is_{{ i.key }}() const;
    {% if i.has_value %}
        const {{ i.value }} &get_{{ i.key }}() const;
        {{ i.value }} &get_{{ i.key }}();
    {% endif %}
## endfor
    const char *type_name() const;
    bool operator==(const {{ name }} &) const;
    bool operator!=(const {{ name }} &) const;
    bool operator==(std::nullptr_t) const;
    bool operator!=(std::nullptr_t) const;
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const {{ name }} &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, {{ name }} &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const {{ name }} &, rapidjson::Document::AllocatorType &);
};
{% else if type == "struct" %}
class {{ name }} {
   private:
    {{ name }} __copy() const;
   public:
    {{ name }}();
    {{ name }}(const {{ name }} &);
## for i in elements
    {% if i.is_vector %}
        std::vector<{{ i.value }}> {{ i.key }};
    {% else if i.is_array %}
        std::array<{{ i.value }}, {{ i.array_size }}> {{ i.key }};
    {% else if i.is_pointer %}
        std::unique_ptr<{{ i.value }}> {{ i.key }};
    {% else %}
        {{ i.value }} {{ i.key }};
    {% endif %}
## endfor
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const {{ name }} &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, {{ name }} &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const {{ name }} &, rapidjson::Document::AllocatorType &);
};
{% endif %}
)__template__";

namespace BackEnd {
std::string HdrGen::gen(const nlohmann::json &back_end) {
    std::string res;
    res += inja::render(header_template_string, back_end);
    for (const auto &block : back_end["blocks"]) {
        res += inja::render(block_template_string, block);
    }
    return res;
}
}  // namespace BackEnd