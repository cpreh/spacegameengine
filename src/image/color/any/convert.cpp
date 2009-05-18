/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>
#include <boost/gil/color_convert.hpp>

namespace
{

template<
	typename Dest
>
class visitor {
public:
	typedef Dest result_type;

	template<
		typename Source
	>
	result_type
	operator()(
		Source const &) const;
};

}

template<
	typename Dest
>
Dest const
sge::image::color::any::convert(
	object const &col)
{
	return variant::apply_unary(
		visitor<
			Dest
		>(),
		col
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
	Source const &src) const
{
	Dest dest;

	boost::gil::color_convert(
		src,
		dest
	);

	return dest;
}

}

#define SGE_INSTANTIATE_COLOR_CONVERT(x)\
template SGE_EXPORT_SYMBOL x const \
sge::image::color::any::convert<\
	sge::image::color::x\
>(\
	sge::image::color::any::object const &\
);

SGE_INSTANTIATE_COLOR_CONVERT(rgba8)
SGE_INSTANTIATE_COLOR_CONVERT(argb8)
SGE_INSTANTIATE_COLOR_CONVERT(bgra8)
SGE_INSTANTIATE_COLOR_CONVERT(rgba32f)
SGE_INSTANTIATE_COLOR_CONVERT(argb32f)
SGE_INSTANTIATE_COLOR_CONVERT(bgra32f)

#undef SGE_INSTANTIATE_COLOR_CONVERT
