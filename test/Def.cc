
#include "Def.h"


Calc::__Tag Calc::__get_tag() const {
    return static_cast<__Tag>(__data.index());
}
Calc::Calc(): __data({}) {}
Calc::Calc(const Calc &other): __data(other.__data) {}
Calc::Calc(Calc &&other): __data(std::move(other.__data)) {}
Calc &Calc::operator=(const Calc &other) {
    __data = other.__data;
    return *this;
}
Calc &Calc::operator=(Calc &&other) {
    __data = std::move(other.__data);
    return *this;
}
Calc &Calc::operator=(std::nullptr_t) {
    __data = __Data{};
    return *this;
}
Calc Calc::Add() {
    Calc res;
    res.__data = __Data{std::in_place_index<static_cast<size_t>(__Tag::Add)>};
    return res;
}
bool Calc::is_Add() const {
    return __get_tag() == __Tag::Add;
}

Calc Calc::Sub() {
    Calc res;
    res.__data = __Data{std::in_place_index<static_cast<size_t>(__Tag::Sub)>};
    return res;
}
bool Calc::is_Sub() const {
    return __get_tag() == __Tag::Sub;
}

Calc Calc::Mul() {
    Calc res;
    res.__data = __Data{std::in_place_index<static_cast<size_t>(__Tag::Mul)>};
    return res;
}
bool Calc::is_Mul() const {
    return __get_tag() == __Tag::Mul;
}

Calc Calc::Div() {
    Calc res;
    res.__data = __Data{std::in_place_index<static_cast<size_t>(__Tag::Div)>};
    return res;
}
bool Calc::is_Div() const {
    return __get_tag() == __Tag::Div;
}

const char *Calc::type_name() const {
    switch (__get_tag()) {
        case __Tag::Add:
            return "Add";
        case __Tag::Sub:
            return "Sub";
        case __Tag::Mul:
            return "Mul";
        case __Tag::Div:
            return "Div";
        default:
            return "<undefined>";
    }
}
bool Calc::operator==(const Calc &other) const {
    return __data.index() == other.__data.index();
}
bool Calc::operator!=(const Calc &other) const {
    return __data.index() != other.__data.index();
}
bool Calc::operator==(std::nullptr_t) const {
    return __data.index() == 0;
}
bool Calc::operator!=(std::nullptr_t) const {
    return __data.index() != 0;
}
namespace axm {
namespace detail {
void __to_binary(bytes &res, const Calc &object) {
    __to_binary(res, (uint32_t)object.__data.index());
    switch (object.__get_tag()) {
        
        
        
        
        default:
            break;
    }
}
void __from_binary(bytes_iter &it, Calc &object) {
    uint32_t tag_id;
    __from_binary(it, tag_id);
    switch (static_cast<Calc::__Tag>(tag_id)) {
        case Calc::__Tag::Add:
            
                object.__data = Calc::__Data{std::in_place_index<static_cast<size_t>(Calc::__Tag::Add)>};
            
                break;
        case Calc::__Tag::Sub:
            
                object.__data = Calc::__Data{std::in_place_index<static_cast<size_t>(Calc::__Tag::Sub)>};
            
                break;
        case Calc::__Tag::Mul:
            
                object.__data = Calc::__Data{std::in_place_index<static_cast<size_t>(Calc::__Tag::Mul)>};
            
                break;
        case Calc::__Tag::Div:
            
                object.__data = Calc::__Data{std::in_place_index<static_cast<size_t>(Calc::__Tag::Div)>};
            
                break;
        default:
            object.__data = Calc::__Data{};
            break;
    }
}
Value __to_rapidjson(const Calc &object, Document::AllocatorType &allocator) {
    Value v;
    v.SetObject();
    switch (object.__get_tag()) {
        case Calc::__Tag::Add:
            v.AddMember("Add",
            
                Value().Move()
            
            , allocator
            );
            break;
        case Calc::__Tag::Sub:
            v.AddMember("Sub",
            
                Value().Move()
            
            , allocator
            );
            break;
        case Calc::__Tag::Mul:
            v.AddMember("Mul",
            
                Value().Move()
            
            , allocator
            );
            break;
        case Calc::__Tag::Div:
            v.AddMember("Div",
            
                Value().Move()
            
            , allocator
            );
            break;
        default:
            break;
    }
    return v;
}
}
}



Result::__Tag Result::__get_tag() const {
    return static_cast<__Tag>(__data.index());
}
Result::Result(): __data({}) {}
Result::Result(const Result &other): __data(other.__data) {}
Result::Result(Result &&other): __data(std::move(other.__data)) {}
Result &Result::operator=(const Result &other) {
    __data = other.__data;
    return *this;
}
Result &Result::operator=(Result &&other) {
    __data = std::move(other.__data);
    return *this;
}
Result &Result::operator=(std::nullptr_t) {
    __data = __Data{};
    return *this;
}
Result Result::Ok() {
    Result res;
    res.__data = __Data{std::in_place_index<static_cast<size_t>(__Tag::Ok)>};
    return res;
}
bool Result::is_Ok() const {
    return __get_tag() == __Tag::Ok;
}

Result Result::Err(int value) {
    Result res;
    res.__data = __Data{std::in_place_index<static_cast<size_t>(__Tag::Err)>, value};
    return res;
}
bool Result::is_Err() const {
    return __get_tag() == __Tag::Err;
}

const int &Result::get_Err() const {
    return __get_value<__Tag::Err>();
}
int &Result::get_Err() {
    return __get_value<__Tag::Err>();
}

const char *Result::type_name() const {
    switch (__get_tag()) {
        case __Tag::Ok:
            return "Ok";
        case __Tag::Err:
            return "Err";
        default:
            return "<undefined>";
    }
}
bool Result::operator==(const Result &other) const {
    return __data.index() == other.__data.index();
}
bool Result::operator!=(const Result &other) const {
    return __data.index() != other.__data.index();
}
bool Result::operator==(std::nullptr_t) const {
    return __data.index() == 0;
}
bool Result::operator!=(std::nullptr_t) const {
    return __data.index() != 0;
}
namespace axm {
namespace detail {
void __to_binary(bytes &res, const Result &object) {
    __to_binary(res, (uint32_t)object.__data.index());
    switch (object.__get_tag()) {
        
        
            case Result::__Tag::Err:
                __to_binary(res, object.__get_value<Result::__Tag::Err>());
                break;
        
        default:
            break;
    }
}
void __from_binary(bytes_iter &it, Result &object) {
    uint32_t tag_id;
    __from_binary(it, tag_id);
    switch (static_cast<Result::__Tag>(tag_id)) {
        case Result::__Tag::Ok:
            
                object.__data = Result::__Data{std::in_place_index<static_cast<size_t>(Result::__Tag::Ok)>};
            
                break;
        case Result::__Tag::Err:
            
                int value;
                __from_binary(it, value);
                object.__data = Result::__Data{std::in_place_index<static_cast<size_t>(Result::__Tag::Err)>, std::move(value)};
            
                break;
        default:
            object.__data = Result::__Data{};
            break;
    }
}
Value __to_rapidjson(const Result &object, Document::AllocatorType &allocator) {
    Value v;
    v.SetObject();
    switch (object.__get_tag()) {
        case Result::__Tag::Ok:
            v.AddMember("Ok",
            
                Value().Move()
            
            , allocator
            );
            break;
        case Result::__Tag::Err:
            v.AddMember("Err",
            
                __to_rapidjson(object.__get_value<Result::__Tag::Err>(), allocator)
            
            , allocator
            );
            break;
        default:
            break;
    }
    return v;
}
}
}



User::User():
    id(),
    name(),
    gender(),
    online(),
    score(),
    follows(),
    state()
    {}
namespace axm {
namespace detail {
void __to_binary(bytes &res, const User &object) {
    __to_binary(res, object.id);
    __to_binary(res, object.name);
    __to_binary(res, object.gender);
    __to_binary(res, object.online);
    __to_binary(res, object.score);
    __to_binary(res, object.follows);
    __to_binary(res, object.state);
}
void __from_binary(bytes_iter &it, User &object) {
    __from_binary(it, object.id);
    __from_binary(it, object.name);
    __from_binary(it, object.gender);
    __from_binary(it, object.online);
    __from_binary(it, object.score);
    __from_binary(it, object.follows);
    __from_binary(it, object.state);
}
Value __to_rapidjson(const User &object, Document::AllocatorType &allocator) {
    Value v;
    v.SetObject();
    v.AddMember("id", __to_rapidjson(object.id, allocator), allocator);
    v.AddMember("name", __to_rapidjson(object.name, allocator), allocator);
    v.AddMember("gender", __to_rapidjson(object.gender, allocator), allocator);
    v.AddMember("online", __to_rapidjson(object.online, allocator), allocator);
    v.AddMember("score", __to_rapidjson(object.score, allocator), allocator);
    v.AddMember("follows", __to_rapidjson(object.follows, allocator), allocator);
    v.AddMember("state", __to_rapidjson(object.state, allocator), allocator);
    return v;
}
}
}



Array::Array():
    el()
    {}
namespace axm {
namespace detail {
void __to_binary(bytes &res, const Array &object) {
    __to_binary(res, object.el);
}
void __from_binary(bytes_iter &it, Array &object) {
    __from_binary(it, object.el);
}
Value __to_rapidjson(const Array &object, Document::AllocatorType &allocator) {
    Value v;
    v.SetObject();
    v.AddMember("el", __to_rapidjson(object.el, allocator), allocator);
    return v;
}
}
}

