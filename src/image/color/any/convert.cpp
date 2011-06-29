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


#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/ag8_format.hpp>
#include <sge/image/color/alpha8_format.hpp>
#include <sge/image/color/argb32f_format.hpp>
#include <sge/image/color/argb8_format.hpp>
#include <sge/image/color/bgra32f_format.hpp>
#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/ga8_format.hpp>
#include <sge/image/color/gray8_format.hpp>
#include <sge/image/color/rgb32f_format.hpp>
#include <sge/image/color/rgb8_format.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/object_impl.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/export_symbol.hpp>

namespace
{

template<
	typename Dest
>
class visitor
{
public:
	typedef typename sge::image::color::object<
		Dest
	>::type result_type;

	template<
		typename Source
	>
	result_type
	operator()(
		Source const &
	) const;
};

}

template<
	typename Dest
>
typename sge::image::color::object<
	Dest
>::type const
sge::image::color::any::convert(
	object const &_color
)
{
	return
		fcppt::variant::apply_unary(
			::visitor<
				Dest
			>(),
			_color.get()
		);
}

namespace
{

template<
	typename Dest
>
template<
	typename Source
>
typename visitor<Dest>::result_type
visitor<Dest>::operator()(
	Source const &_src
) const
{
	return
		sge::image::color::convert<
			Dest
		>(
			_src
		);
}

}

#define SGE_INSTANTIATE_COLOR_CONVERT(\
	format\
)\
template FCPPT_EXPORT_SYMBOL \
sge::image::color::object<\
	sge::image::color::format\
>::type const \
sge::image::color::any::convert<\
	sge::image::color::format\
>(\
	sge::image::color::any::object const &\
);

SGE_INSTANTIATE_COLOR_CONVERT(alpha8_format)
SGE_INSTANTIATE_COLOR_CONVERT(gray8_format)
SGE_INSTANTIATE_COLOR_CONVERT(rgba8_format)
SGE_INSTANTIATE_COLOR_CONVERT(argb8_format)
SGE_INSTANTIATE_COLOR_CONVERT(bgra8_format)
SGE_INSTANTIATE_COLOR_CONVERT(rgb8_format)
SGE_INSTANTIATE_COLOR_CONVERT(rgba32f_format)
SGE_INSTANTIATE_COLOR_CONVERT(argb32f_format)
SGE_INSTANTIATE_COLOR_CONVERT(bgra32f_format)
SGE_INSTANTIATE_COLOR_CONVERT(rgb32f_format)
SGE_INSTANTIATE_COLOR_CONVERT(ag8_format)
SGE_INSTANTIATE_COLOR_CONVERT(ga8_format)

#undef SGE_INSTANTIATE_COLOR_CONVERT
