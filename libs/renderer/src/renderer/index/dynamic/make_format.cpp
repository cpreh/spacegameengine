/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/renderer/index/detail/pp_formats.hpp>
#include <sge/renderer/impl/index/dynamic/format_enum_static.hpp>
#include <sge/renderer/index/format.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Format
>
sge::renderer::index::dynamic::format
sge::renderer::index::dynamic::make_format()
{
	return
		sge::renderer::impl::index::dynamic::format_enum_static<
			Format
		>::value;
}

#define SGE_RENDERER_INDEX_DYNAMIC_INSTANTIATE_MAKE_FORMAT(\
	seq,\
	_,\
	cur_format\
)\
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
sge::renderer::index::dynamic::format \
sge::renderer::index::dynamic::make_format<\
	cur_format \
>();

BOOST_PP_SEQ_FOR_EACH(
	SGE_RENDERER_INDEX_DYNAMIC_INSTANTIATE_MAKE_FORMAT,
	_,
	SGE_RENDERER_INDEX_DETAIL_PP_FORMATS
)
