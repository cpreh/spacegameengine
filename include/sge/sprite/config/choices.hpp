/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/sprite/config/is_size_choice.hpp>
#include <sge/sprite/config/is_type_choices.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/static_assert.hpp>
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
	typename SizeChoice,
	typename OptionalElements
>
struct choices
{
	typedef TypeChoices type_choices;

	typedef SizeChoice size_choice;

	typedef OptionalElements optional_elements;

	BOOST_STATIC_ASSERT(
		sge::sprite::config::is_type_choices<
			TypeChoices
		>::value
	);

	BOOST_STATIC_ASSERT(
		sge::sprite::config::is_size_choice<
			SizeChoice
		>::value
	);

	BOOST_STATIC_ASSERT(
		boost::mpl::is_sequence<
			OptionalElements
		>::value
	);
};

}
}
}

#endif
