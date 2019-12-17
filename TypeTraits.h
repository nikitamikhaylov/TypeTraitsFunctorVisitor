#pragma once
#include "TypeList.h"

namespace type_traits {

    /// helpers
    struct false_type
    {
        static constexpr bool value = false;
    };

    struct true_type
    {
        static constexpr bool value = true;
    };

    template <typename T>
    using add_rvalue_reference_t = T&&;

    template <typename T>
    add_rvalue_reference_t<T> declval();

    /// enable_if_t

    template <bool, typename = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    template <bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;

    /// is_class

    namespace detail
    {
        template <typename T, typename = typename enable_if<!std::is_union<T>::value>::type>
        std::true_type test(int T::*);

        template <typename T>
        std::false_type test(...);
    }

    template <class T>
    struct is_class : decltype(detail::test<T>(nullptr))
    {};

    /// is_base_of

    namespace detail {
        template <typename Base>
        true_type is_base_of_test_func(const volatile Base*);

        template <typename Base>
        false_type is_base_of_test_func(const volatile void*);

        template <typename Base, typename Derived>
        using pre_is_base_of = decltype(is_base_of_test_func<Base>(declval<Derived*>()));

        template <typename Base, typename Derived, typename = void>
        struct pre_is_base_of2 : public true_type { };

        template <typename Base, typename Derived>
        struct pre_is_base_of2<Base, Derived, std::void_t<pre_is_base_of<Base, Derived>>> :
                public pre_is_base_of<Base, Derived> { };
    }


    template<bool B, class T, class F>
    struct conditional { typedef T type; };

    template<class T, class F>
    struct conditional<false, T, F> { typedef F type; };

    template< bool B, class T, class F >
    using conditional_t = typename conditional<B,T,F>::type;

    template <typename Base, typename Derived>
    struct is_base_of : public conditional_t<
                    is_class<Base>::value && is_class<Derived>::value,
                    detail::pre_is_base_of2<Base, Derived>, false_type> { };

    /// is_abstract
    namespace detail
    {
        template <typename T, typename = decltype(new T[1])>
        false_type is_abstract_(int);

        template <typename>
        true_type is_abstract_(...);
    }

    template <typename T>
    struct is_abstract : decltype(detail::is_abstract_<T>(0)) {};


    template <typename TL, template <typename> class Condition>
    struct Split {
        typedef typelist::EmptyList accept;
        typedef typelist::EmptyList reject;
    };

    template <typename H, typename... T, template <typename> class Condition>
    class Split<typelist::TypeList<H, T...>, Condition> {
    private:
        typedef typename Split<typelist::TypeList<T...>, Condition>::accept accepted_prev;
        typedef typename Split<typelist::TypeList<T...>, Condition>::reject rejected_prev;

    public:
        typedef conditional_t<Condition<H>::value, typelist::Append<accepted_prev, H>, accepted_prev> accept;
        typedef conditional_t<Condition<H>::value, rejected_prev, typelist::Append<rejected_prev, H>> reject;
    };
}

