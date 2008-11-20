/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/color_convert.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/gil/color_convert.hpp>
#include <boost/variant/get.hpp>

namespace
{

template<typename Dest>
struct conversion_helper {
	conversion_helper(
		sge::renderer::any_color const &col,
		Dest &dest);

	template<typename Source>
	void operator()(
		Source &) const;
private:
	sge::renderer::any_color const &col;
	Dest                           &dest;
};

}

template<typename Dest>
Dest const sge::renderer::color_convert(
	any_color const &col)
{
	Dest dest;
	boost::mpl::for_each<
		any_color::types>(
			conversion_helper<Dest>(
				col,
				dest));
	return dest;
}

namespace
{

template<typename Dest>
conversion_helper<Dest>::conversion_helper(
	sge::renderer::any_color const &col,
	Dest &dest)
:
	col(col),
	dest(dest)
{}

template<typename Dest>
template<typename Source>
void conversion_helper<Dest>::operator()(
	Source &) const
{
	if(typeid(Source) == col.type())
		boost::gil::color_convert(
			boost::get<Source>(col),
			dest);
}

}

#define SGE_INSTANTIATE_COLOR_CONVERT(x)\
template SGE_EXPORT_SYMBOL x const sge::renderer::color_convert<x>(\
	sge::renderer::any_color const &);

SGE_INSTANTIATE_COLOR_CONVERT(sge::renderer::rgba8_color)
SGE_INSTANTIATE_COLOR_CONVERT(sge::renderer::argb8_color)
SGE_INSTANTIATE_COLOR_CONVERT(sge::renderer::bgra8_color)
SGE_INSTANTIATE_COLOR_CONVERT(sge::renderer::rgba32f_color)
SGE_INSTANTIATE_COLOR_CONVERT(sge::renderer::argb32f_color)
SGE_INSTANTIATE_COLOR_CONVERT(sge::renderer::bgra32f_color)

#undef SGE_INSTANTIATE_COLOR_CONVERT
