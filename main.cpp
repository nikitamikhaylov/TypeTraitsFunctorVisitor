#include "Functor.h"
#include "Visitor.h"
#include "Acceptor.h"

int main()
{
    VisitFactory<typelist::TypeList<Acceptor, ThirdAcceptor, ConcreteVisitor<PrinterFunctor>, SecondAcceptor, Visitor,
                PrinterFunctor<FirstAcceptor, ConcreteVisitor<PrinterFunctor>>,
                PrinterFunctor<SecondAcceptor, ConcreteVisitor<PrinterFunctor>>>> f;

    FirstAcceptor firstAcceptor;
    SecondAcceptor secondAcceptor;
    ThirdAcceptor thirdAcceptor;

    ConcreteVisitor<PrinterFunctor> v;

    f.go(&firstAcceptor, &v, "a"); /// a--###--First Acceptor
    f.go(&secondAcceptor, &v, "b"); /// b--***--Second Acceptor
    f.go(&secondAcceptor, &v, 123); /// Wrong arguments
    f.go(&thirdAcceptor, &v, "a"); /// No functors
}