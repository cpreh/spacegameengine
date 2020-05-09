//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_CONTEXT_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_CONTEXT_IMPL_HPP_INCLUDED

#include <sge/plugin/context_base_ref.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/info_fwd.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/impl/context_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


template<
	typename Type
>
sge::plugin::context<
	Type
>::context(
	sge::plugin::context_base_ref const _context_base
)
:
	context_base_(
		_context_base
	)
{
}

template<
	typename Type
>
sge::plugin::context<
	Type
>::context(
	context const &
)
= default;

template<
	typename Type
>
sge::plugin::context<
	Type
>::context(
	context &&
)
noexcept
= default;

template<
	typename Type
>
sge::plugin::context<
	Type
> &
sge::plugin::context<
	Type
>::operator=(
	context const &
)
= default;

template<
	typename Type
>
sge::plugin::context<
	Type
> &
sge::plugin::context<
	Type
>::operator=(
	context &&
)
noexcept
= default;

template<
	typename Type
>
sge::plugin::context<
	Type
>::~context()
= default;

template<
	typename Type
>
typename
sge::plugin::context<
	Type
>::object
sge::plugin::context<
	Type
>::load() const
{
	return
		sge::plugin::object<
			Type
		>(
			context_base_.get().load()
		);
}

template<
	typename Type
>
std::filesystem::path const &
sge::plugin::context<
	Type
>::path() const
{
	return
		context_base_.get().path();
}

template<
	typename Type
>
sge::plugin::info const &
sge::plugin::context<
	Type
>::info() const
{
	return
		context_base_.get().info();
}

#endif
