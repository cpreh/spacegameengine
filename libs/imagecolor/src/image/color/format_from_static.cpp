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


#include <sge/image/color/enable_if_has_format.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_from_static.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/color/impl/pp_formats.hpp>
#include <sge/image/color/impl/traits/format_map.hpp>
#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image/impl/format_from_static_impl.hpp>
#include <sge/image/impl/instantiate_format_from_static.hpp>
#include <sge/src/core/export_function_instantiation.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Format
>
sge::image::color::enable_if_has_format<
	Format,
	sge::image::color::format
>
sge::image::color::format_from_static()
{
	return
		sge::image::format_from_static<
			sge::image::color::tag,
			Format
		>();
}

// TODO: Abstract his?

#define SGE_INSTANTIATE_COLOR_FORMAT_FROM_STATIC(\
	seq,\
	_,\
	format_arg\
)\
template \
SGE_CORE_EXPORT_FUNCTION_INSTANTIATION \
sge::image::color::enable_if_has_format< \
	sge::image::color:: BOOST_PP_CAT(format_arg,_format),\
	sge::image::color::format \
> \
sge::image::color::format_from_static<\
	sge::image::color:: BOOST_PP_CAT(format_arg,_format)\
>() \
; \
SGE_IMAGE_IMPL_INSTANTIATE_FORMAT_FROM_STATIC(\
	sge::image::color::tag,\
	sge::image::color:: BOOST_PP_CAT(format_arg,_format)\
) \
;

BOOST_PP_SEQ_FOR_EACH(
	SGE_INSTANTIATE_COLOR_FORMAT_FROM_STATIC,
	_,
	SGE_IMAGE_COLOR_IMPL_PP_FORMATS
)

#undef SGE_INSTANTIATE_COLOR_FORMAT_FROM_STATIC
