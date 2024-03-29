#include "SrcGen.h"

#include <inja/inja.hpp>
#include <nlohmann/json.hpp>

#include "BackEnd.h"

static auto header_template_string = R"__template__(
#include "{{ file_name }}.h"
)__template__";

static auto block_template_string = R"__template__(
{% if type == "enum" %}
{{ name }}::__Tag {{ name }}::__get_tag() const {
    return static_cast<__Tag>(__data.index());
}
{{ name }}::{{ name }}(const __Data &data): __data(data) {}
{{ name }}::{{ name }}(__Data &&data): __data(std::move(data)) {}
{{ name }}::{{ name }}(): __data() {}
{{ name }}::{{ name }}(const {{ name }} &other): __data(other.__data) {}
{{ name }}::{{ name }}({{ name }} &&other): __data(std::move(other.__data)) {}
{{ name }} &{{ name }}::operator=(const {{ name }} &other) {
    switch (other.__get_tag()) {
## for i in elements
        case __Tag::{{ i.key }}:
            __data.emplace<static_cast<std::size_t>(__Tag::{{ i.key }})>(other.__get_value<__Tag::{{ i.key }}>());
            break;
## endfor
        default:
            __data.emplace<0>();
    }
    return *this;
}
{{ name }} &{{ name }}::operator=({{ name }} &&other) {
    switch (other.__get_tag()) {
## for i in elements
        case __Tag::{{ i.key }}:
            __data.emplace<static_cast<std::size_t>(__Tag::{{ i.key }})>(std::move(other.__get_value<__Tag::{{ i.key }}>()));
            break;
## endfor
        default:
            __data.emplace<0>();
    }
    return *this;
}
{{ name }} &{{ name }}::operator=(std::nullptr_t) {
    __data.emplace<0>();
    return *this;
}
## for i in elements
{{ name }} {{ name }}::{{ i.key }}({% if i.has_value %}{{ i.value }} value{% endif %}) {
    return {{ name }}(__Data{std::in_place_index<static_cast<size_t>(__Tag::{{ i.key }})>{% if i.has_value %}, value{% endif %}});
}
{# is_SomeTag #}
bool {{ name }}::is_{{ i.key }}() const {
    return __get_tag() == __Tag::{{ i.key }};
}
{% if i.has_value %}
const {{ i.value }} &{{ name }}::get_{{ i.key }}() const {
    return __get_value<__Tag::{{ i.key }}>();
}
{{ i.value }} &{{ name }}::get_{{ i.key }}() {
    return __get_value<__Tag::{{ i.key }}>();
}
{% endif %}
## endfor
const char *{{ name }}::type_name() const {
    switch (__get_tag()) {
## for i in elements
        case __Tag::{{ i.key }}:
            return "{{ i.key }}";
## endfor
        default:
            return "<undefined>";
    }
}
bool {{ name }}::operator==(const {{ name }} &other) const {
    return __data.index() == other.__data.index();
}
bool {{ name }}::operator!=(const {{ name }} &other) const {
    return __data.index() != other.__data.index();
}
bool {{ name }}::operator==(std::nullptr_t) const {
    return __data.index() == 0;
}
bool {{ name }}::operator!=(std::nullptr_t) const {
    return __data.index() != 0;
}
namespace axm {
namespace detail {
void __to_binary(bytes &res, const {{ name }} &object) {
    __to_binary(res, (uint32_t)object.__data.index());
    switch (object.__get_tag()) {
## for i in elements
        {% if i.has_value %}
            case {{ name }}::__Tag::{{ i.key }}:
                __{% if i.is_var %}var_{% endif %}to_binary(res, object.__get_value<{{ name }}::__Tag::{{ i.key }}>());
                break;
        {% endif %}
## endfor
        default:
            break;
    }
}
void __from_binary(bytes_iter &it, {{ name }} &object) {
    uint32_t tag_id;
    __from_binary(it, tag_id);
    switch (static_cast<{{ name }}::__Tag>(tag_id)) {
## for i in elements
        case {{ name }}::__Tag::{{ i.key }}: {
            {% if i.has_value %}
                {{ i.value }} value;
                __{% if i.is_var %}var_{% endif %}from_binary(it, value);
                object = {{ name }}({{ name }}::__Data{std::in_place_index<static_cast<size_t>({{ name }}::__Tag::{{ i.key }})>, std::move(value)});
            {% else %}
                object = {{ name }}({{ name }}::__Data{std::in_place_index<static_cast<size_t>({{ name }}::__Tag::{{ i.key }})>});
            {% endif %}
                break;
        }
## endfor
        default:
            object = {{ name }}();
            break;
    }
}
Value __to_rapidjson(const {{ name }} &object, Document::AllocatorType &allocator) {
    Value v;
    v.SetObject();
    switch (object.__get_tag()) {
## for i in elements
        case {{ name }}::__Tag::{{ i.key }}:
            v.AddMember("{{ i.key }}",
            {% if i.has_value %}
                __to_rapidjson(object.__get_value<{{ name }}::__Tag::{{ i.key }}>(), allocator)
            {% else %}
                Value().Move()
            {% endif%}
            , allocator
            );
            break;
## endfor
        default:
            break;
    }
    return v;
}
}
}
{% else if type == "struct" %}
{{ name }} {{ name }}::__copy() const {
    {{ name }} res;
## for i in elements
    {% if i.is_pointer %}
        res.{{ i.key }} = std::make_unique<{{ i.value }}>(*{{ i.key }});
    {% else %}
        res.{{ i.key }} = {{ i.key }};
    {% endif %}
## endfor
    return res;
}
{{ name }}::{{ name }}():
## for i in elements
    {{ i.key }}()
    {% if not loop.is_last %},{% endif %}
## endfor
    {}
{{ name }}::{{ name }}(const {{ name }} &other):
## for i in elements
    {% if i.is_pointer %}
    {{ i.key }}(other.{{ i.key }} == nullptr ? nullptr : std::make_unique<{{ i.value }}>(*other.{{ i.key }}))
    {% else %}
    {{ i.key }}(other.{{ i.key }})
    {% endif %}
    {% if not loop.is_last %},{% endif %}
## endfor
    {}
namespace axm {
namespace detail {
void __to_binary(bytes &res, const {{ name }} &object) {
## for i in elements
    __{% if i.is_var %}var_{% endif %}to_binary(res, object.{{ i.key }});
## endfor
}
void __from_binary(bytes_iter &it, {{ name }} &object) {
## for i in elements
    __{% if i.is_var %}var_{% endif %}from_binary(it, object.{{ i.key }});
## endfor
}
Value __to_rapidjson(const {{ name }} &object, Document::AllocatorType &allocator) {
    Value v;
    v.SetObject();
## for i in elements
    v.AddMember("{{ i.key }}", __to_rapidjson(object.{{ i.key }}, allocator), allocator);
## endfor
    return v;
}
}
}
{% endif %}
)__template__";

namespace BackEnd {
std::string SrcGen::gen(const nlohmann::json &back_end) {
    std::string res;
    res += inja::render(header_template_string, back_end);

    for (const nlohmann::json &block : back_end["blocks"]) {
        res += inja::render(block_template_string, block);
    }
    return res;
}
}  // namespace BackEnd