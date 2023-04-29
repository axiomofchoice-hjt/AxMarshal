
#pragma once

#include <memory>
#include <rapidjson/document.h>
#include <string>
#include <variant>
#include <vector>

#include "axm/axm.h"

class Calc;
class Result;
class User;
class Array;
class Linked;
class A;
class B;
class E;

namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const Calc &);
void __from_binary(std::vector<uint8_t>::const_iterator &, Calc &);
Value __to_rapidjson(const Calc &, Document::AllocatorType &);
}
}

class Calc {
   private:
    enum class __Tag {
        __UNDEF,
        Add ,
        Sub ,
        Mul ,
        Div 
    };
    using __Data = std::variant<
        std::monostate,
        std::monostate
        ,
        std::monostate
        ,
        std::monostate
        ,
        std::monostate
        
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
    Calc(const __Data &data);
    Calc(__Data &&data);
   public:
    Calc();
    Calc(const Calc &);
    Calc(Calc &&);
    Calc &operator=(const Calc &other);
    Calc &operator=(Calc &&other);
    Calc &operator=(std::nullptr_t);
    static Calc Add();
    bool is_Add() const;
    
    static Calc Sub();
    bool is_Sub() const;
    
    static Calc Mul();
    bool is_Mul() const;
    
    static Calc Div();
    bool is_Div() const;
    
    const char *type_name() const;
    bool operator==(const Calc &) const;
    bool operator!=(const Calc &) const;
    bool operator==(std::nullptr_t) const;
    bool operator!=(std::nullptr_t) const;
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const Calc &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, Calc &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const Calc &, rapidjson::Document::AllocatorType &);
};


namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const Result &);
void __from_binary(std::vector<uint8_t>::const_iterator &, Result &);
Value __to_rapidjson(const Result &, Document::AllocatorType &);
}
}

class Result {
   private:
    enum class __Tag {
        __UNDEF,
        Ok ,
        Err 
    };
    using __Data = std::variant<
        std::monostate,
        std::monostate
        ,
        int
        
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
    Result(const __Data &data);
    Result(__Data &&data);
   public:
    Result();
    Result(const Result &);
    Result(Result &&);
    Result &operator=(const Result &other);
    Result &operator=(Result &&other);
    Result &operator=(std::nullptr_t);
    static Result Ok();
    bool is_Ok() const;
    
    static Result Err(int);
    bool is_Err() const;
    
        const int &get_Err() const;
        int &get_Err();
    
    const char *type_name() const;
    bool operator==(const Result &) const;
    bool operator!=(const Result &) const;
    bool operator==(std::nullptr_t) const;
    bool operator!=(std::nullptr_t) const;
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const Result &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, Result &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const Result &, rapidjson::Document::AllocatorType &);
};


namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const User &);
void __from_binary(std::vector<uint8_t>::const_iterator &, User &);
Value __to_rapidjson(const User &, Document::AllocatorType &);
}
}

class User {
   private:
    User __copy() const;
   public:
    User();
    User(const User &);
    
        int id;
    
    
        std::string name;
    
    
        char gender;
    
    
        bool online;
    
    
        float score;
    
    
        std::vector<int> follows;
    
    
        Result state;
    
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const User &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, User &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const User &, rapidjson::Document::AllocatorType &);
};


namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const Array &);
void __from_binary(std::vector<uint8_t>::const_iterator &, Array &);
Value __to_rapidjson(const Array &, Document::AllocatorType &);
}
}

class Array {
   private:
    Array __copy() const;
   public:
    Array();
    Array(const Array &);
    
        std::array<int, 4> el;
    
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const Array &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, Array &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const Array &, rapidjson::Document::AllocatorType &);
};


namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const Linked &);
void __from_binary(std::vector<uint8_t>::const_iterator &, Linked &);
Value __to_rapidjson(const Linked &, Document::AllocatorType &);
}
}

class Linked {
   private:
    Linked __copy() const;
   public:
    Linked();
    Linked(const Linked &);
    
        int data;
    
    
        std::unique_ptr<Linked> next;
    
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const Linked &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, Linked &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const Linked &, rapidjson::Document::AllocatorType &);
};


namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const A &);
void __from_binary(std::vector<uint8_t>::const_iterator &, A &);
Value __to_rapidjson(const A &, Document::AllocatorType &);
}
}

class A {
   private:
    A __copy() const;
   public:
    A();
    A(const A &);
    
        int data;
    
    
        std::unique_ptr<B> next;
    
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const A &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, A &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const A &, rapidjson::Document::AllocatorType &);
};


namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const B &);
void __from_binary(std::vector<uint8_t>::const_iterator &, B &);
Value __to_rapidjson(const B &, Document::AllocatorType &);
}
}

class B {
   private:
    B __copy() const;
   public:
    B();
    B(const B &);
    
        int data;
    
    
        std::unique_ptr<A> next;
    
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const B &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, B &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const B &, rapidjson::Document::AllocatorType &);
};


namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const E &);
void __from_binary(std::vector<uint8_t>::const_iterator &, E &);
Value __to_rapidjson(const E &, Document::AllocatorType &);
}
}

class E {
   private:
    enum class __Tag {
        __UNDEF,
        AA ,
        BB 
    };
    using __Data = std::variant<
        std::monostate,
        A
        ,
        B
        
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
    E(const __Data &data);
    E(__Data &&data);
   public:
    E();
    E(const E &);
    E(E &&);
    E &operator=(const E &other);
    E &operator=(E &&other);
    E &operator=(std::nullptr_t);
    static E AA(A);
    bool is_AA() const;
    
        const A &get_AA() const;
        A &get_AA();
    
    static E BB(B);
    bool is_BB() const;
    
        const B &get_BB() const;
        B &get_BB();
    
    const char *type_name() const;
    bool operator==(const E &) const;
    bool operator!=(const E &) const;
    bool operator==(std::nullptr_t) const;
    bool operator!=(std::nullptr_t) const;
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const E &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, E &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const E &, rapidjson::Document::AllocatorType &);
};

