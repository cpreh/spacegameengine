/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/systems/renderer.hpp>
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

typedef fcppt::container::map<
	std::map<
		fcppt::type_info,
		priority_type
	>
> priority_map;
	
priority_map const priorities(
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
			fcppt::type_info(typeid(sge::systems::renderer)),
			1
		)
	)
	(
		std::make_pair(
			fcppt::type_info(typeid(sge::systems::input)),
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
	(
		std::make_pair(
			fcppt::type_info(typeid(sge::systems::audio_player)),
			5
		)
	)
	(
		std::make_pair(
			fcppt::type_info(typeid(sge::systems::parameterless::type)),
			6
		)
	)
);


}

bool
sge::systems::any_compare(
	any const &_a,
	any const &_b
)
{
	return
		fcppt::variant::apply_binary(
			::compare(),
			_a,
			_b
		);
}

namespace
{

compare::result_type
compare::operator()(
	sge::systems::parameterless::type const &_a,
	sge::systems::parameterless::type const &_b
) const
{
	return _a < _b;
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
		<
		priority(typeid(U));
}

priority_type
priority(
	fcppt::type_info const &_t
)
{
	return priorities[_t];
}

}
