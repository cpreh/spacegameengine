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


#include <sge/renderer/any_color_compare.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>

namespace
{

class compare : public boost::static_visitor<bool> {
public:
	template<
		typename T,
		typename U
	>
	bool operator()(
		T const &,
		U const &) const;
};

}

bool
sge::renderer::any_color_compare(
	any_color const &a,
	any_color const &b)
{
	return boost::apply_visitor(
		compare(),
		a,
		b);
}

namespace
{

template<
	typename T,
	typename U
>
bool
compare::operator()(
	T const &t,
	U const &u) const
{
	return t == u;
}

}
