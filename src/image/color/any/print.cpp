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


#include <sge/image/color/any/print.hpp>
#include <sge/image/color/print.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace
{

class visitor {
public:
	typedef sge::ostream &result_type;

	explicit visitor(
		sge::ostream &s);

	template<
		typename T
	>
	result_type
	operator()(
		T const &) const;
private:
	sge::ostream &s;
};

}

sge::ostream &
sge::image::color::any::operator<<(
	ostream &s,
	object const &c)
{
	return variant::apply_unary(
		visitor(s),
		c
	);
}

namespace
{

visitor::visitor(
	sge::ostream &s)
:
	s(s)
{}

template<
	typename T
>
visitor::result_type
visitor::operator()(
	T const &t) const
{
	return s << t;
	//return sge::image::color::operator<<(s, t);
}

}
