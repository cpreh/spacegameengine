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


#include <sge/image/algorithm/fill.hpp>
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/object_impl.hpp>
#include <boost/gil/algorithm.hpp>

namespace
{

class color_visitor {
public:
	typedef void result_type;

	explicit color_visitor(
		sge::image::view::object const &);
	
	template<
		typename T
	>
	result_type
	operator()(
		T const &t) const;
private:
	sge::image::view::object const &dest;
};

template<
	typename Color
>
class fill_visitor {
public:
	typedef void result_type;

	explicit fill_visitor(
		Color const &col);
	
	template<
		typename T
	>
	result_type
	operator()(
		T const &) const;
private:
	Color const col;
};

}

void sge::image::algorithm::fill(
	view::object const &dest,
	color::any::object const &c)
{
	variant::apply_unary(
		color_visitor(dest),
		c
	);
}

namespace
{

color_visitor::color_visitor(
	sge::image::view::object const &dest)
:
	dest(dest)
{}

template<
	typename T
>
color_visitor::result_type
color_visitor::operator()(
	T const &t) const
{
	sge::variant::apply_unary(
		fill_visitor<
			T
		>(t),
		dest
	);
}

template<
	typename Color
>
fill_visitor<Color>::fill_visitor(
	Color const &col)
:
	col(col)
{}

template<
	typename Color
>
template<
	typename T
>
typename fill_visitor<Color>::result_type
fill_visitor<Color>::operator()(
	T const &view) const
{
	boost::gil::fill_pixels(
		view,
		col
	);
}

}
