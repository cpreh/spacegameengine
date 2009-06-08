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


#include <sge/image/color/any/compare.hpp>
#include <sge/variant/apply_binary.hpp>
#include <sge/variant/object_impl.hpp>

namespace
{

class compare_visitor {
public:
	typedef bool result_type;

	template<
		typename T,
		typename U
	>
	result_type
	operator()(
		T const &,
		U const &) const;
};

}

bool
sge::image::color::any::compare(
	object const &a,
	object const &b)
{
	return variant::apply_binary(
		compare_visitor(),
		a,
		b
	);
}

namespace
{

template<
	typename T,
	typename U
>
compare_visitor::result_type
compare_visitor::operator()(
	T const &t,
	U const &u) const
{
	return t == u;
}

}
