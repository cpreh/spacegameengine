/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_STATE_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/sprite/state/parameters_fwd.hpp>
#include <sge/sprite/state/detail/parameters_class.hpp>
#include <majutsu/role_value_type.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

template<
	typename StateChoices
>
class parameters
{
	typedef
	sge::sprite::state::detail::parameters_class<
		StateChoices
	>
	elements_type;
public:
	typedef StateChoices state_choices;

	parameters();

	parameters &
	blend_write_mask(
		bool
	);

	parameters &
	enable_scissor_test(
		bool
	);

	template<
		typename Role
	>
	parameters &
	set(
		majutsu::role_value_type<
			elements_type,
			Role
		>
	);

	elements_type const &
	elements() const;
private:
	elements_type elements_;
};

}
}
}

#endif
