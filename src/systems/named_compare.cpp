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
#include <fcppt/container/map.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/type_info.hpp>
#include <boost/assign/list_of.hpp>
#include <typeinfo>
#include <map>

namespace
{

class compare
{
public:
	typedef bool result_type;

	bool operator()(
		sge::systems::parameterless::type const &,
		sge::systems::parameterless::type const &
	) const;

	template<
		typename T,
		typename U
	>
	result_type
	operator()(
		T const &,
		U const &
	) const;
};

typedef unsigned priority_type;

priority_type
priority(
	fcppt::type_info const &
);

}

bool
sge::systems::named_compare(
	named const &a,
	named const &b
)
{
	return fcppt::variant::apply_binary(
		compare(),
		a.value(),
		b.value()
	);
}

namespace
{

compare::result_type
compare::operator()(
	sge::systems::parameterless::type const &a,
	sge::systems::parameterless::type const &b
) const
{
	return a < b;
}

template<
	typename T,
	typename U
>
compare::result_type
compare::operator()(
	T const &,
	U const &
) const
{
	return
		priority(typeid(T))
		< priority(typeid(U));
}

priority_type
priority(
	fcppt::type_info const &t
)
{
	static fcppt::container::map<
		std::map<
			fcppt::type_info,
			priority_type
		>
	> const priorities =
		boost::assign::map_list_of
			(fcppt::type_info(typeid(sge::window::parameters)), 0)
			(fcppt::type_info(typeid(sge::renderer::parameters)), 1)
			(fcppt::type_info(typeid(sge::systems::parameterless::type)), 2);

	return priorities[t];
}

}
