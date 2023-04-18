#include "HdrGen.h"

namespace BackEnd {
std::string HdrGen::__template_string() {
    return R"__template__(
class {{ name }};
namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const {{ name }} &);
void __from_binary(std::vector<uint8_t>::const_iterator &, {{ name }} &);
void __to_json(std::string &, const {{ name }} &);
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
        {% if i.hasValue %}{{ i.value }}
        {% else %}std::monostate
        {% endif %}
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
   public:
    {{ name }}();
    {{ name }}(const {{ name }} &);
    {{ name }}({{ name }} &&);
    {{ name }} &operator=(const {{ name }} &other);
    {{ name }} &operator=({{ name }} &&other);
    {{ name }} &operator=(std::nullptr_t);
## for i in elements
    static {{ name }} {{ i.key }}({% if i.hasValue %}{{ i.value }}{% endif %});
    bool is_{{ i.key }}() const;
    {% if i.hasValue %}
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
    friend void axm::detail::__to_json(std::string &, const {{ name }} &);
};
{% else if type == "class" %}
class {{ name }} {
   public:
## for i in elements
    {% if i.isList %}
        std::vector<{{ i.value }}> {{ i.key }};
    {% else %}
        {{ i.value }} {{ i.key }};
    {% endif %}
## endfor
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const {{ name }} &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, {{ name }} &);
    friend void axm::detail::__to_json(std::string &, const {{ name }} &);
};
{% endif %}
)__template__";
}
}  // namespace BackEnd