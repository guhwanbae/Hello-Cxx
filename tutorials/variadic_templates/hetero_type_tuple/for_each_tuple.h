//  Author  :   Louis Dionne
//  Summary :   Partial specialization for variadic hetero-type-tuple.

#include <utility>

// for_each implementation for variadic tuple
template <typename Tuple, typename F, std::size_t ...Is>
void for_each_impl(Tuple&& tuple, F&& f, std::index_sequence<Is ...>)
{
    using swallow = int[];
    (void)swallow{1, \
                 (f(std::get<Is>(std::forward<Tuple>(tuple))), \
                 void(), \
                 int{})...};
}

template <typename Tuple, typename F>
void for_each(Tuple&& tuple, F&& f)
{
    constexpr std::size_t N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
    for_each_impl(std::forward<Tuple>(tuple), \
                  std::forward<F>(f), \
                  std::make_index_sequence<N>{});
}
