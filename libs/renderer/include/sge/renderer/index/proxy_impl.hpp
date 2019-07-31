//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_PROXY_IMPL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_PROXY_IMPL_HPP_INCLUDED

#include <sge/renderer/index/const_proxy_impl.hpp>
#include <sge/renderer/index/proxy_decl.hpp>
#include <sge/renderer/index/to_const_format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>


template<
	typename Format
>
sge::renderer::index::proxy<
	Format
>::proxy(
	pointer const _data
)
:
	data_(
		_data
	)
{
}

template<
	typename Format
>
void
sge::renderer::index::proxy<
	Format
>::set(
	value_type const _value
)
{
	std::memcpy(
		data_,
		&_value,
		sizeof(
			value_type
		)
	);
}

template<
	typename Format
>
typename
sge::renderer::index::proxy<
	Format
>::value_type
sge::renderer::index::proxy<
	Format
>::get() const
{
	return
		sge::renderer::index::const_proxy<
			sge::renderer::index::to_const_format<
				Format
			>
		>(
			data_
		).get();
}

#endif
