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


#include "any_compare.hpp"
#include <sge/systems/any.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/image_loader.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/map.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/type_info.hpp>
#include <typeinfo>
#include <map>
#include <utility>

namespace
{

class compare
{
public:
	typedef bool result_type;

	result_type
	operator()(
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
sge::systems::any_compare(
	any const &a,
	any const &b
)
{
	return
		fcppt::variant::apply_binary(
			compare(),
			a,
			b
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
	typedef fcppt::container::map<
		std::map<
			fcppt::type_info,
			priority_type
		>
	> priority_map;
	
	static priority_map const priorities(
		fcppt::assign::make_container<
			priority_map
		>
		(
			std::make_pair(
				fcppt::type_info(typeid(sge::window::parameters)),
				0
			)
		)
		(
			std::make_pair(
				fcppt::type_info(typeid(sge::renderer::parameters)),
				1
			)
		)
		(
			std::make_pair(
				fcppt::type_info(typeid(sge::systems::parameterless::type)),
				2	
			)
		)
		(
			std::make_pair(
				fcppt::type_info(typeid(sge::systems::image_loader)),
				3	
			)
		)
		(
			std::make_pair(
				fcppt::type_info(typeid(sge::systems::audio_loader)),
				4	
			)
		)

	);

	return priorities[t];
}

}
