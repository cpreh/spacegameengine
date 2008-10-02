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


#include <sge/systems/any_compare.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <typeinfo>

namespace
{

struct compare : boost::static_visitor<bool> {
	bool operator()(
		sge::systems::parameterless::type const &,
		sge::systems::parameterless::type const &) const;

	template<typename T, typename U>
	bool operator()(
		T const &,
		U const &) const;
};

}

bool sge::systems::any_compare::operator()(
	any const &a,
	any const &b) const
{
	return boost::apply_visitor(
		compare(),
		a,
		b);
}

namespace
{

bool compare::operator()(
	sge::systems::parameterless::type const &a,
	sge::systems::parameterless::type const &b) const
{
	return a < b;
}

template<typename T, typename U>
bool compare::operator()(
	T const &,
	U const &) const
{
	return typeid(T).before(typeid(U));
}

}
