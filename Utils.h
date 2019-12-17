#pragma once

#include <iostream>
#include "TypeTraits.h"
#include "TypeList.h"

using namespace type_traits;

class Acceptor;
class Visitor;

template <typename T>
struct is_acceptor : is_base_of<Acceptor, T> {};

template <typename T>
struct is_visitor : is_base_of<Visitor, T> {};

void PrintArgs() {}

template<class Arg1>
void PrintArgs(Arg1 arg1) {
    std::cout << arg1 << std::endl;
}

template<class Arg1, class... Args>
void PrintArgs(Arg1 arg1, Args... args) {
    std::cout << arg1 << " -- ";
    PrintArgs(args...);
}