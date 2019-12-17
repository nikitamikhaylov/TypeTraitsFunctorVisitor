cmake_minimum_required(VERSION 3.15)
project(TypeTraitsFunctorVisitor)

set(CMAKE_CXX_STANDARD 17)

add_executable(TypeTraitsFunctorVisitor main.cpp TypeList.h TypeTraits.h Functor.h Utils.h Visitor.h Acceptor.h)