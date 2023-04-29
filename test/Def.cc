
#include "Def.h"


Calc::__Tag Calc::__get_tag() const {
    return static_cast<__Tag>(__data.index());
}
Calc::Calc(const __Data &data): __data(data) {}
Calc::Calc(__Data &&data): __data(std::move(data)) {}
Calc::Calc(): __data() {}
Calc::Calc(const Calc &other): __data(other.__data) {}
Calc::Calc(Calc &&other): __data(std::move(other.__data)) {}
Calc &Calc::operator=(const Calc &other) {
    switch (other.__get_tag()) {
        case __Tag::Add:
            __data.emplace<static_cast<std::size_t>(__Tag::Add)>(other.__get_value<__Tag::Add>());
            break;
        case __Tag::Sub:
            __data.emplace<static_cast<std::size_t>(__Tag::Sub)>(other.__get_value<__Tag::Sub>());
            break;
        case __Tag::Mul:
            __data.emplace<static_cast<std::size_t>(__Tag::Mul)>(other.__get_value<__Tag::Mul>());
            break;
        case __Tag::Div:
            __data.emplace<static_cast<std::size_t>(__Tag::Div)>(other.__get_value<__Tag::Div>());
            break;
        default:
            __data.emplace<0>();
    }
    return *this;
}
Calc &Calc::operator=(Calc &&other) {
    switch (other.__get_tag()) {
        case __Tag::Add:
            __data.emplace<static_cast<std::size_t>(__Tag::Add)>(std::move(other.__get_value<__Tag::Add>()));
            break;
        case __Tag::Sub:
            __data.emplace<static_cast<std::size_t>(__Tag::Sub)>(std::move(other.__get_value<__Tag::Sub>()));
            break;
        case __Tag::Mul:
            __data.emplace<static_cast<std::size_t>(__Tag::Mul)>(std::move(other.__get_value<__Tag::Mul>()));
            break;
        case __Tag::Div:
            __data.emplace<static_cast<std::size_t>(__Tag::Div)>(std::move(other.__get_value<__Tag::Div>()));
            break;
        default:
            __data.emplace<0>();
    }
    return *this;
}
Calc &Calc::operator=(std::nullptr_t) {
    __data.emplace<0>();
    return *this;
}
Calc Calc::Add() {
    return Calc(__Data{std::in_place_index<static_cast<size_t>(__Tag::Add)>});
}

bool Calc::is_Add() const {
    return __get_tag() == __Tag::Add;
}

Calc Calc::Sub() {
    return Calc(__Data{std::in_place_index<static_cast<size_t>(__Tag::Sub)>});
}

bool Calc::is_Sub() const {
    return __get_tag() == __Tag::Sub;
}

Calc Calc::Mul() {
    return Calc(__Data{std::in_place_index<static_cast<size_t>(__Tag::Mul)>});
}

bool Calc::is_Mul() const {
    return __get_tag() == __Tag::Mul;
}

Calc Calc::Div() {
    return Calc(__Data{std::in_place_index<static_cast<size_t>(__Tag::Div)>});
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
        case Calc::__Tag::Add: {
            
                object = Calc(Calc::__Data{std::in_place_index<static_cast<size_t>(Calc::__Tag::Add)>});
            
                break;
        }
        case Calc::__Tag::Sub: {
            
                object = Calc(Calc::__Data{std::in_place_index<static_cast<size_t>(Calc::__Tag::Sub)>});
            
                break;
        }
        case Calc::__Tag::Mul: {
            
                object = Calc(Calc::__Data{std::in_place_index<static_cast<size_t>(Calc::__Tag::Mul)>});
            
                break;
        }
        case Calc::__Tag::Div: {
            
                object = Calc(Calc::__Data{std::in_place_index<static_cast<size_t>(Calc::__Tag::Div)>});
            
                break;
        }
        default:
            object = Calc();
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
Result::Result(const __Data &data): __data(data) {}
Result::Result(__Data &&data): __data(std::move(data)) {}
Result::Result(): __data() {}
Result::Result(const Result &other): __data(other.__data) {}
Result::Result(Result &&other): __data(std::move(other.__data)) {}
Result &Result::operator=(const Result &other) {
    switch (other.__get_tag()) {
        case __Tag::Ok:
            __data.emplace<static_cast<std::size_t>(__Tag::Ok)>(other.__get_value<__Tag::Ok>());
            break;
        case __Tag::Err:
            __data.emplace<static_cast<std::size_t>(__Tag::Err)>(other.__get_value<__Tag::Err>());
            break;
        default:
            __data.emplace<0>();
    }
    return *this;
}
Result &Result::operator=(Result &&other) {
    switch (other.__get_tag()) {
        case __Tag::Ok:
            __data.emplace<static_cast<std::size_t>(__Tag::Ok)>(std::move(other.__get_value<__Tag::Ok>()));
            break;
        case __Tag::Err:
            __data.emplace<static_cast<std::size_t>(__Tag::Err)>(std::move(other.__get_value<__Tag::Err>()));
            break;
        default:
            __data.emplace<0>();
    }
    return *this;
}
Result &Result::operator=(std::nullptr_t) {
    __data.emplace<0>();
    return *this;
}
Result Result::Ok() {
    return Result(__Data{std::in_place_index<static_cast<size_t>(__Tag::Ok)>});
}

bool Result::is_Ok() const {
    return __get_tag() == __Tag::Ok;
}

Result Result::Err(int value) {
    return Result(__Data{std::in_place_index<static_cast<size_t>(__Tag::Err)>, value});
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
        case Result::__Tag::Ok: {
            
                object = Result(Result::__Data{std::in_place_index<static_cast<size_t>(Result::__Tag::Ok)>});
            
                break;
        }
        case Result::__Tag::Err: {
            
                int value;
                __from_binary(it, value);
                object = Result(Result::__Data{std::in_place_index<static_cast<size_t>(Result::__Tag::Err)>, std::move(value)});
            
                break;
        }
        default:
            object = Result();
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



User User::__copy() const {
    User res;
    
        res.id = id;
    
    
        res.name = name;
    
    
        res.gender = gender;
    
    
        res.online = online;
    
    
        res.score = score;
    
    
        res.follows = follows;
    
    
        res.state = state;
    
    return res;
}
User::User():
    id()
    ,
    name()
    ,
    gender()
    ,
    online()
    ,
    score()
    ,
    follows()
    ,
    state()
    
    {}
User::User(const User &other):
    
    id(other.id)
    
    ,
    
    name(other.name)
    
    ,
    
    gender(other.gender)
    
    ,
    
    online(other.online)
    
    ,
    
    score(other.score)
    
    ,
    
    follows(other.follows)
    
    ,
    
    state(other.state)
    
    
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



Array Array::__copy() const {
    Array res;
    
        res.el = el;
    
    return res;
}
Array::Array():
    el()
    
    {}
Array::Array(const Array &other):
    
    el(other.el)
    
    
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



Linked Linked::__copy() const {
    Linked res;
    
        res.data = data;
    
    
        res.next = std::make_unique<Linked>(*next);
    
    return res;
}
Linked::Linked():
    data()
    ,
    next()
    
    {}
Linked::Linked(const Linked &other):
    
    data(other.data)
    
    ,
    
    next(other.next == nullptr ? nullptr : std::make_unique<Linked>(*other.next))
    
    
    {}
namespace axm {
namespace detail {
void __to_binary(bytes &res, const Linked &object) {
    __to_binary(res, object.data);
    __to_binary(res, object.next);
}
void __from_binary(bytes_iter &it, Linked &object) {
    __from_binary(it, object.data);
    __from_binary(it, object.next);
}
Value __to_rapidjson(const Linked &object, Document::AllocatorType &allocator) {
    Value v;
    v.SetObject();
    v.AddMember("data", __to_rapidjson(object.data, allocator), allocator);
    v.AddMember("next", __to_rapidjson(object.next, allocator), allocator);
    return v;
}
}
}



A A::__copy() const {
    A res;
    
        res.data = data;
    
    
        res.next = std::make_unique<B>(*next);
    
    return res;
}
A::A():
    data()
    ,
    next()
    
    {}
A::A(const A &other):
    
    data(other.data)
    
    ,
    
    next(other.next == nullptr ? nullptr : std::make_unique<B>(*other.next))
    
    
    {}
namespace axm {
namespace detail {
void __to_binary(bytes &res, const A &object) {
    __to_binary(res, object.data);
    __to_binary(res, object.next);
}
void __from_binary(bytes_iter &it, A &object) {
    __from_binary(it, object.data);
    __from_binary(it, object.next);
}
Value __to_rapidjson(const A &object, Document::AllocatorType &allocator) {
    Value v;
    v.SetObject();
    v.AddMember("data", __to_rapidjson(object.data, allocator), allocator);
    v.AddMember("next", __to_rapidjson(object.next, allocator), allocator);
    return v;
}
}
}



B B::__copy() const {
    B res;
    
        res.data = data;
    
    
        res.next = std::make_unique<A>(*next);
    
    return res;
}
B::B():
    data()
    ,
    next()
    
    {}
B::B(const B &other):
    
    data(other.data)
    
    ,
    
    next(other.next == nullptr ? nullptr : std::make_unique<A>(*other.next))
    
    
    {}
namespace axm {
namespace detail {
void __to_binary(bytes &res, const B &object) {
    __to_binary(res, object.data);
    __to_binary(res, object.next);
}
void __from_binary(bytes_iter &it, B &object) {
    __from_binary(it, object.data);
    __from_binary(it, object.next);
}
Value __to_rapidjson(const B &object, Document::AllocatorType &allocator) {
    Value v;
    v.SetObject();
    v.AddMember("data", __to_rapidjson(object.data, allocator), allocator);
    v.AddMember("next", __to_rapidjson(object.next, allocator), allocator);
    return v;
}
}
}



E::__Tag E::__get_tag() const {
    return static_cast<__Tag>(__data.index());
}
E::E(const __Data &data): __data(data) {}
E::E(__Data &&data): __data(std::move(data)) {}
E::E(): __data() {}
E::E(const E &other): __data(other.__data) {}
E::E(E &&other): __data(std::move(other.__data)) {}
E &E::operator=(const E &other) {
    switch (other.__get_tag()) {
        case __Tag::AA:
            __data.emplace<static_cast<std::size_t>(__Tag::AA)>(other.__get_value<__Tag::AA>());
            break;
        case __Tag::BB:
            __data.emplace<static_cast<std::size_t>(__Tag::BB)>(other.__get_value<__Tag::BB>());
            break;
        default:
            __data.emplace<0>();
    }
    return *this;
}
E &E::operator=(E &&other) {
    switch (other.__get_tag()) {
        case __Tag::AA:
            __data.emplace<static_cast<std::size_t>(__Tag::AA)>(std::move(other.__get_value<__Tag::AA>()));
            break;
        case __Tag::BB:
            __data.emplace<static_cast<std::size_t>(__Tag::BB)>(std::move(other.__get_value<__Tag::BB>()));
            break;
        default:
            __data.emplace<0>();
    }
    return *this;
}
E &E::operator=(std::nullptr_t) {
    __data.emplace<0>();
    return *this;
}
E E::AA(A value) {
    return E(__Data{std::in_place_index<static_cast<size_t>(__Tag::AA)>, value});
}

bool E::is_AA() const {
    return __get_tag() == __Tag::AA;
}

const A &E::get_AA() const {
    return __get_value<__Tag::AA>();
}
A &E::get_AA() {
    return __get_value<__Tag::AA>();
}

E E::BB(B value) {
    return E(__Data{std::in_place_index<static_cast<size_t>(__Tag::BB)>, value});
}

bool E::is_BB() const {
    return __get_tag() == __Tag::BB;
}

const B &E::get_BB() const {
    return __get_value<__Tag::BB>();
}
B &E::get_BB() {
    return __get_value<__Tag::BB>();
}

const char *E::type_name() const {
    switch (__get_tag()) {
        case __Tag::AA:
            return "AA";
        case __Tag::BB:
            return "BB";
        default:
            return "<undefined>";
    }
}
bool E::operator==(const E &other) const {
    return __data.index() == other.__data.index();
}
bool E::operator!=(const E &other) const {
    return __data.index() != other.__data.index();
}
bool E::operator==(std::nullptr_t) const {
    return __data.index() == 0;
}
bool E::operator!=(std::nullptr_t) const {
    return __data.index() != 0;
}
namespace axm {
namespace detail {
void __to_binary(bytes &res, const E &object) {
    __to_binary(res, (uint32_t)object.__data.index());
    switch (object.__get_tag()) {
        
            case E::__Tag::AA:
                __to_binary(res, object.__get_value<E::__Tag::AA>());
                break;
        
        
            case E::__Tag::BB:
                __to_binary(res, object.__get_value<E::__Tag::BB>());
                break;
        
        default:
            break;
    }
}
void __from_binary(bytes_iter &it, E &object) {
    uint32_t tag_id;
    __from_binary(it, tag_id);
    switch (static_cast<E::__Tag>(tag_id)) {
        case E::__Tag::AA: {
            
                A value;
                __from_binary(it, value);
                object = E(E::__Data{std::in_place_index<static_cast<size_t>(E::__Tag::AA)>, std::move(value)});
            
                break;
        }
        case E::__Tag::BB: {
            
                B value;
                __from_binary(it, value);
                object = E(E::__Data{std::in_place_index<static_cast<size_t>(E::__Tag::BB)>, std::move(value)});
            
                break;
        }
        default:
            object = E();
            break;
    }
}
Value __to_rapidjson(const E &object, Document::AllocatorType &allocator) {
    Value v;
    v.SetObject();
    switch (object.__get_tag()) {
        case E::__Tag::AA:
            v.AddMember("AA",
            
                __to_rapidjson(object.__get_value<E::__Tag::AA>(), allocator)
            
            , allocator
            );
            break;
        case E::__Tag::BB:
            v.AddMember("BB",
            
                __to_rapidjson(object.__get_value<E::__Tag::BB>(), allocator)
            
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

