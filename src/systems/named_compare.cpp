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



#include <sge/systems/named_compare.hpp>
#include <sge/systems/named.hpp>
#include <sge/container/map.hpp>
#include <sge/type_info.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/assign/list_of.hpp>
#include <typeinfo>
#include <map>

namespace
{

class compare : public boost::static_visitor<bool> {
public:
	bool operator()(
		sge::systems::parameterless::type const &,
		sge::systems::parameterless::type const &) const;
	
	template<
		typename T,
		typename U
	>
	bool operator()(
		T const &,
		U const &) const;
};

typedef unsigned priority_type;

priority_type
priority(
	sge::type_info const &);

}

bool sge::systems::named_compare(
	named const &a,
	named const &b)
{
	return boost::apply_visitor(
		compare(),
		a.value(),
		b.value()
	);
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
	return priority(typeid(T))
		< priority(typeid(U));
}

priority_type
priority(
	sge::type_info const &t)
{
	static sge::container::map<
		std::map,
		sge::type_info,
		priority_type
	> const priorities =
		boost::assign::map_list_of
			(sge::type_info(typeid(sge::window::parameters)), 0)
			(sge::type_info(typeid(sge::renderer::parameters)), 1)
			(sge::type_info(typeid(sge::systems::parameterless::type)), 2);
	
	return priorities[t];
}

}
