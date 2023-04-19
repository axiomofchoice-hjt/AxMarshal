
#pragma once

#include <rapidjson/document.h>
#include <string>
#include <variant>
#include <vector>

#include "axm/axm.h"

class Calc;
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


class Result;
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


class User;
namespace axm {
namespace detail {
void __to_binary(std::vector<uint8_t> &, const User &);
void __from_binary(std::vector<uint8_t>::const_iterator &, User &);
Value __to_rapidjson(const User &, Document::AllocatorType &);
}
}

class User {
   public:
    
        int id;
    
    
        std::string name;
    
    
        char gender;
    
    
        bool online;
    
    
        float score;
    
    
        std::vector<int> follows;
    
    
        Result state;
    
    User();
    friend void axm::detail::__to_binary(std::vector<uint8_t> &, const User &);
    friend void axm::detail::__from_binary(std::vector<uint8_t>::const_iterator &, User &);
    friend rapidjson::Value axm::detail::__to_rapidjson(const User &, rapidjson::Document::AllocatorType &);
};

