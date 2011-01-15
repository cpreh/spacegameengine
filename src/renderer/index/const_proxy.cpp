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


#include <sge/renderer/index/const_proxy.hpp>
#include <sge/renderer/index/const_format_16.hpp>
#include <sge/renderer/index/const_format_32.hpp>
#include <fcppt/export_symbol.hpp>
#include <cstring>

template<
	typename Format
>
sge::renderer::index::const_proxy<Format>::const_proxy(
	pointer const _data
)
:
	data_(_data)
{
}

template<
	typename Format
>
typename sge::renderer::index::const_proxy<Format>::value_type
sge::renderer::index::const_proxy<Format>::get() const
{
	value_type ret;

	std::memcpy(
		&ret,
		data_,
		sizeof(value_type)
	);

	return ret;
}

#define SGE_RENDERER_INDEX_DEFINE_CONST_PROXY(\
	format\
)\
template FCPPT_EXPORT_SYMBOL \
class sge::renderer::index::const_proxy<\
	format\
>;

SGE_RENDERER_INDEX_DEFINE_CONST_PROXY(
	sge::renderer::index::const_format_16
)

SGE_RENDERER_INDEX_DEFINE_CONST_PROXY(
	sge::renderer::index::const_format_32
)

#undef SGE_RENDERER_INDEX_DEFINE_CONST_PROXY
