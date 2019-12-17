#pragma once
#include <stdexcept>
#include "Visitor.h"

class Acceptor {
public:
    virtual void accept(Visitor*, const std::string&) = 0;
    void accept(...) { throw std::runtime_error("Calling accept method of base class"); }
};

class FirstAcceptor : public Acceptor {
public:
    void accept(Visitor* visitor, const std::string& str) override
    {
        visitor->visit(this, str, "First Acceptor");
    }
};


class SecondAcceptor : public Acceptor {
public:
    void accept(Visitor* visitor, const std::string& str) override
    {
        visitor->visit(this, str, "Second Acceptor");
    }
};


class ThirdAcceptor : public Acceptor {
public:
    void accept(Visitor* visitor, const std::string& str) override
    {
        visitor->visit(this, str, "Third Acceptor");
    }
};