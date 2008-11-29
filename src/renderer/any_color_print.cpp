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


#include <sge/renderer/any_color_print.hpp>
#include <sge/renderer/color_print.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>

namespace
{

struct visitor : boost::static_visitor<sge::ostream &> {
	explicit visitor(
		sge::ostream &s);
	template<typename T>
	sge::ostream &
	operator()(
		T const &) const;
private:
	sge::ostream &s;
};

}

sge::ostream &
sge::renderer::operator<<(
	ostream &s,
	any_color const &c)
{
	return boost::apply_visitor(
		visitor(s),
		c);
}

namespace
{

visitor::visitor(
	sge::ostream &s)
:
	s(s)
{}

template<typename T>
sge::ostream &
visitor::operator()(
	T const &t) const
{
	return sge::renderer::operator<<(s, t);
}

}
