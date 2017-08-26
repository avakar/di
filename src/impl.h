#include <utility>
#include <type_traits>

namespace avakar {

template <typename... Dn>
struct di;

template <typename D, typename Di>
struct _di_contains
	: std::false_type
{
};

template <typename D, typename... Dn>
struct _di_contains<D, di<D, Dn...>>
	: std::true_type
{
};

template <typename D, typename D0, typename... Dn>
struct _di_contains<D, di<D0, Dn...>>
	: _di_contains<D, di<Dn...>>
{
};

template <typename D, typename A, typename = void>
struct _di_fetch
{
	static constexpr bool allowed = false;
};

template <typename D, typename Di>
struct _di_fetch<D, Di, std::enable_if_t<
	_di_contains<D, std::decay_t<Di>>::value
	>>
{
	static constexpr bool allowed = true;

	static D const & fetch(Di const & a)
	{
		return a.get<D>();
	}
};

template <typename D, typename A>
struct _di_fetch<D, A, std::enable_if_t<
	std::is_convertible<A &&, D>::value
	>>
{
	static constexpr bool allowed = true;

	static D fetch(A && a)
	{
		return { std::forward<A>(a) };
	}
};

template <typename D>
struct _di_pick
{
	template <typename A0, typename... An>
	static std::enable_if_t<_di_fetch<D, A0>::allowed, D> pick(A0 && a0, An &&... an)
	{
		return _di_fetch<D, A0>::fetch(std::forward<A0>(a0));
	}

	template <typename A0, typename... An>
	static std::enable_if_t<!_di_fetch<D, A0>::allowed, D> pick(A0 && a0, An &&... an)
	{
		return pick(std::forward<An>(an)...);
	}
};

} // namespace avakar
