#pragma once

#include <utility>
#include <string>
#include <iostream>

#include "Utils.h"

template <typename, typename, typename = void>
class PrinterFunctor;

template <typename AcceptorType, typename VisitorType>
class PrinterFunctor<AcceptorType, VisitorType, enable_if_t<is_acceptor<AcceptorType>::value && is_visitor<VisitorType>::value>> {
    public:
        using Acceptor = AcceptorType;
        using Visitor = VisitorType;

        template <typename... Args>
        bool check(Args&&... args) const
        {
            return decltype(check_(std::forward<Args>(args)...))::value;
        }

        template <typename... Args>
        void operator()(Args&&... args)
        {
            PrintArgs(std::forward<Args>(args)...);
        }

    private:
        true_type check_(const std::string&) const;
        false_type check_(...) const;
};