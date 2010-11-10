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
#include <sge/systems/parameterless.hpp>
#include <sge/window/parameters.hpp>
#include <fcppt/mpl/index_of.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <boost/mpl/vector/vector10.hpp>

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

typedef boost::mpl::vector7<
	sge::window::parameters,
	sge::systems::renderer,
	sge::systems::input,
	sge::systems::image_loader,
	sge::systems::audio_loader,
	sge::systems::audio_player,
	sge::systems::parameterless::type
> priority_vector;

template<
	typename T
>
struct priority
:
fcppt::mpl::index_of<
	priority_vector,
	T
>
{
};

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
		priority<T>::value
		<
		priority<U>::value;
}

}
