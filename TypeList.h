#pragma once

namespace typelist {

    template <typename...> class TypeList {};

    template <typename H, typename... T>
    struct TypeList<H, T...> {
        using Head = H;
        using Tail = TypeList<T...>;
    };

    using EmptyList = TypeList<>;

    namespace detail {

        template <typename, typename>
        struct AppendImpl;

        template <typename... Types, typename U>
        struct AppendImpl<TypeList<Types...>, U> {
            using type = TypeList<Types..., U>;
        };
    }

    template <typename TL, typename T>
    using Append = typename detail::AppendImpl<TL, T>::type;

}