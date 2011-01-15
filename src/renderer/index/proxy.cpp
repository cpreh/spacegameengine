/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/renderer/index/proxy.hpp>
#include <sge/renderer/index/const_proxy.hpp>
#include <sge/renderer/index/format_16.hpp>
#include <sge/renderer/index/format_32.hpp>
#include <sge/renderer/index/to_nonconst_format.hpp>
#include <cstring>

template<
	typename Format
>
sge::renderer::index::proxy<Format>::proxy(
	pointer const _data
)
:
	data_(_data)
{
}

template<
	typename Format
>
void
sge::renderer::index::proxy<Format>::set(
	value_type const _value
)
{
	std::memcpy(
		data_,
		sizeof(value_type),
		&_value
	);
}

template<
	typename Format
>
typename sge::renderer::index::proxy<Format>::value_type
sge::renderer::index::proxy<Format>::get() const
{
	return
		index::const_proxy<
			typename index::to_nonconst_format<
				Format
			>::type
		>(
			data_
		).get();
}

#define SGE_RENDERER_INDEX_DEFINE_PROXY(\
	format\
)\
template FCPPT_EXPORT_SYMBOL \
class sge::renderer::index::proxy<\
	format\
>;

SGE_RENDERER_INDEX_DEFINE_PROXY(
	sge::renderer::index::format_16
)

SGE_RENDERER_INDEX_DEFINE_PROXY(
	sge::renderer::index::format_32
)

#undef SGE_RENDERER_INDEX_DEFINE_PROXY
