#ifndef AVAKAR_DI_DI_H
#define AVAKAR_DI_DI_H

#include "../../src/impl.h"
#include <tuple>
#include <utility>

namespace avakar {

template <typename... Dn>
struct di
{
	template <typename... An>
	di(An &&... an)
		: deps_(_di_pick<Dn>::pick(std::forward<An>(an)...)...)
	{
	}

	template <typename D>
	D const & get() const
	{
		return std::get<D>(deps_);
	}

private:
	std::tuple<Dn...> deps_;
};

}

#endif // AVAKAR_DI_DI_H
