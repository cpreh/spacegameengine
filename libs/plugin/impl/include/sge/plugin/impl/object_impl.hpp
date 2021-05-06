//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_OBJECT_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_OBJECT_IMPL_HPP_INCLUDED

#include <sge/plugin/object.hpp>
#include <sge/plugin/detail/traits.hpp>
#include <sge/plugin/impl/library/load_function.hpp>
#include <sge/plugin/impl/library/object.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Type
>
sge::plugin::object<
	Type
>::object(
	library_shared_ptr _lib
)
:
	lib_(
		std::move(
			_lib
		)
	),
	loader_(
		sge::plugin::impl::library::load_function<
			loader_function
		>(
			fcppt::make_ref(
				*lib_
			),
			sge::plugin::detail::traits<
				Type
			>::plugin_loader_name()
		)
	)
{
}

template<
	typename Type
>
sge::plugin::object<
	Type
>::object(
	object &&
)
noexcept
= default;

template<
	typename Type
>
sge::plugin::object<
	Type
> &
sge::plugin::object<
	Type
>::operator=(
	object &&
)
noexcept
= default;

namespace sge::plugin
{
template<
	typename Type
>
object<
	Type
>::~object()
= default;
}

template<
	typename Type
>
typename sge::plugin::object<
	Type
>::loader_function
sge::plugin::object<
	Type
>::get() const
{
	return
		loader_;
}

#endif
