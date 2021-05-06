//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_COLLECTION_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_COLLECTION_IMPL_HPP_INCLUDED

#include <sge/plugin/category_array.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <fcppt/reference_impl.hpp>


template<
	typename Type
>
sge::plugin::collection<
	Type
>::collection(
	sge::plugin::category_array const &_plugins
)
:
	plugins_{
		_plugins
	}
{
}

template<
	typename Type
>
sge::plugin::collection<
	Type
>::collection(
	collection const &
)
=
default;

template<
	typename Type
>
sge::plugin::collection<
	Type
>::collection(
	collection &&
)
noexcept
=
default;

template<
	typename Type
>
sge::plugin::collection<
	Type
> &
sge::plugin::collection<
	Type
>::operator=(
	collection const &
)
=
default;

template<
	typename Type
>
sge::plugin::collection<
	Type
> &
sge::plugin::collection<
	Type
>::operator=(
	collection &&
)
noexcept
=
default;

namespace sge::plugin
{
template<
	typename Type
>
collection<
	Type
>::~collection()
= default;
}

template<
	typename Type
>
typename
sge::plugin::collection<
	Type
>::iterator
sge::plugin::collection<
	Type
>::begin() const
{
	return
		iterator(
			plugins_.get().begin()
		);
}

template<
	typename Type
>
typename
sge::plugin::collection<
	Type
>::iterator
sge::plugin::collection<
	Type
>::end() const
{
	return
		iterator(
			plugins_.get().end()
		);
}

template<
	typename Type
>
typename
sge::plugin::collection<
	Type
>::size_type
sge::plugin::collection<
	Type
>::size() const
{
	return
		plugins_.get().size();
}

#endif
