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


#include "format_enum_static.hpp"
#include "../instantiate_all.hpp"
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Format
>
sge::renderer::index::dynamic::format::type
sge::renderer::index::dynamic::make_format()
{
	return
		index::dynamic::format_enum_static<
			Format
		>::value;
}

#define SGE_RENDERER_INDEX_DYNAMIC_INSTANTIATE_MAKE_FORMAT(\
	cur_format\
)\
template \
FCPPT_EXPORT_SYMBOL \
sge::renderer::index::dynamic::format::type \
sge::renderer::index::dynamic::make_format<\
	cur_format \
>();

SGE_RENDERER_INDEX_INSTANTIATE_ALL(
	SGE_RENDERER_INDEX_DYNAMIC_INSTANTIATE_MAKE_FORMAT
)

#undef SGE_RENDERER_INDEX_DYNAMIC_INSTANTIATE_MAKE_FORMAT
