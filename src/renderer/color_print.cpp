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


#include <sge/renderer/color_print.hpp>
#include <sge/renderer/color.hpp>
#include <sge/text.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/back.hpp>
#include <ostream>

namespace
{

template<typename Pixel>
struct channel_printer {
	channel_printer(
		sge::ostream &s,
		Pixel const &p);

	template<typename T>
	void operator()(T &) const;
private:
	sge::ostream &s;
	Pixel const &p;
};

}

template<
	typename Channel,
	typename Layout
>
sge::ostream &
sge::renderer::operator<<(
	ostream &s,
	boost::gil::pixel<
		Channel,
		Layout
	> const &p)
{
	typedef boost::gil::pixel<
		Channel,
		Layout
	> pixel_type;

	boost::mpl::for_each<
		typename pixel_type::layout_t::channel_mapping_t>(
			channel_printer<pixel_type>(
				s,
				p));
	return s;
}

namespace
{

template<typename Pixel>
channel_printer<Pixel>::channel_printer(
	sge::ostream &s,
	Pixel const &p)
: s(s),
  p(p)
{}

template<typename Pixel>
template<typename T>
void channel_printer<Pixel>::operator()(
	T &t) const
{
	s << (p[t] + 0);
	typedef typename Pixel::layout_t::channel_mapping_t mapping;
	if(t != boost::mpl::back<mapping>::type::value)
		s << SGE_TEXT(", ");
}

}

#define SGE_INSTANTIATE_COLOR_PRINT(c, l)\
template sge::ostream &\
sge::renderer::operator<<(\
	ostream &,\
	boost::gil::pixel<\
		sge::renderer::c,\
		boost::gil::l\
	> const &);

SGE_INSTANTIATE_COLOR_PRINT(color_channel_8, rgba_layout_t)
SGE_INSTANTIATE_COLOR_PRINT(color_channel_8, bgra_layout_t)
SGE_INSTANTIATE_COLOR_PRINT(color_channel_8, argb_layout_t)
SGE_INSTANTIATE_COLOR_PRINT(color_channel_f32, rgba_layout_t)

#undef SGE_INSTANTIATE_COLOR_PRINT
