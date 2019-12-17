#pragma once

#include <string>
#include "Utils.h"

class FirstAcceptor;
class SecondAcceptor;
class ThirdAcceptor;

class Visitor {
public:
    virtual void visit(FirstAcceptor*, const std::string&, const std::string&) = 0;
    virtual void visit(SecondAcceptor*, const std::string&, const std::string&) = 0;
    virtual void visit(ThirdAcceptor*, const std::string&, const std::string&) = 0;
};

template <template <typename, typename> class Functor>
class ConcreteVisitor : public Visitor {
public:
    void visit(FirstAcceptor*, const std::string& first, const std::string& second) override
    {
        Functor<FirstAcceptor, ConcreteVisitor<Functor>> func;
        func(first, second, "###");
    }

    void visit(SecondAcceptor*, const std::string& first, const std::string& second) override
    {
        Functor<SecondAcceptor, ConcreteVisitor<Functor>> func;
        func(first, second, "***");
    }

    void visit(ThirdAcceptor*, const std::string& first, const std::string& second) override
    {
        Functor<ThirdAcceptor, ConcreteVisitor<Functor>> func;
        func(first, second, "@@@");
    }
};


template <typename TL>
class VisitFactory {
private:
    typedef Split<TL, is_acceptor> splitted_;
    typedef typename splitted_::accept all_acceptors_;
    typedef Split<typename splitted_::reject, is_visitor> second_splitted_;
    typedef typename second_splitted_::accept all_visitors_;
    typedef typename second_splitted_::reject functors_;
    typedef typename Split<all_acceptors_, is_abstract>::accept::Head acceptor_;
    typedef typename Split<all_visitors_, is_abstract>::accept::Head visitor_;


    template <typename Functors>
    struct FindFunctor_ {
        template <typename... Args>
        static void go(acceptor_*, visitor_*, Args&&...)
        {
            std::cout << "NO FUNCTOR" << std::endl;
        }
    };

    template <typename Head, typename... Tail>
    struct FindFunctor_<typelist::TypeList<Head, Tail...>> {
        template <typename... Args>
        static void go(acceptor_* acceptor, visitor_* visitor, Args&&... args)
        {
            if (!dynamic_cast<typename Head::Acceptor*>(acceptor) && dynamic_cast<typename Head::Visitor*>(visitor))
            {
                FindFunctor_<typelist::TypeList<Tail...>>::go(acceptor, visitor, std::forward<Args>(args)...);
                return;
            }

            Head functor;
            if (!functor.check(std::forward<Args>(args)...))
                std::cout << "WRONG ARGUMENTS" << std::endl;
            else
                acceptor->accept(visitor, std::forward<Args>(args)...);
        }
    };

public:
    template <typename... Args>
    void go(acceptor_* acceptor, visitor_* visitor, Args&&... args) const
    {
        FindFunctor_<functors_>::go(acceptor, visitor, std::forward<Args>(args)...);
    }
};