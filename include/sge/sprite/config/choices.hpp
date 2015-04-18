/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_CONFIG_CHOICES_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_CHOICES_HPP_INCLUDED

#include <sge/sprite/config/choices_fwd.hpp>
#include <sge/sprite/config/is_pos_choice.hpp>
#include <sge/sprite/config/is_size_choice.hpp>
#include <sge/sprite/config/is_type_choices.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

template<
	typename TypeChoices,
	typename PosChoice,
	typename SizeChoice,
	typename OptionalElements
>
struct choices
{
	typedef
	TypeChoices
	type_choices;

	typedef
	PosChoice
	pos_choice;

	typedef
	SizeChoice
	size_choice;

	typedef
	OptionalElements
	optional_elements;

	static_assert(
		sge::sprite::config::is_type_choices<
			TypeChoices
		>::value,
		"TypeChoices must be a sprite type_choices struct"
	);

	static_assert(
		sge::sprite::config::is_pos_choice<
			PosChoice
		>::value,
		"PosChoice must be one of sprite's pos choices"
	);

	static_assert(
		sge::sprite::config::is_size_choice<
			SizeChoice
		>::value,
		"SizeChoice must be one of sprite's size choices"
	);

	static_assert(
		boost::mpl::is_sequence<
			OptionalElements
		>::value,
		"OptionalElements must be an mpl sequence"
	);
};

}
}
}

#endif
