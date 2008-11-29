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


#include <sge/renderer/fill_pixels.hpp>
#include <boost/gil/extension/dynamic_image/algorithm.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

namespace
{

struct visitor : boost::static_visitor<> {
	explicit visitor(
		sge::renderer::image_view const &);
	template<typename T>
	void operator()(
		T const &t) const;
private:
	sge::renderer::image_view const &dest;
};

}

void sge::renderer::fill_pixels(
	image_view const &dest,
	any_color const &c)
{
	boost::apply_visitor(
		visitor(dest),
		c);
}

namespace
{

visitor::visitor(
	sge::renderer::image_view const &dest)
:
	dest(dest)
{}

template<typename T>
void visitor::operator()(
	T const &t) const
{
	boost::gil::fill_pixels(
		dest,
		t);
}

}
