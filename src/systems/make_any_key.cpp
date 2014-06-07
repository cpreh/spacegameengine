/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/src/systems/make_any_key.hpp>
#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_key.hpp>
#include <fcppt/variant/apply_unary.hpp>


namespace
{

struct make_key_visitor
{
	typedef sge::systems::detail::any_key result_type;

#define SGE_SYSTEMS_MAKE_KEY_CASE(\
	type,\
	name\
)\
	result_type \
	operator()( \
		sge::systems::type const & \
	) const \
	{ \
		return \
			sge::systems::detail::any_key::name;\
	}

	SGE_SYSTEMS_MAKE_KEY_CASE(
		config,
		config
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		window,
		window
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		detail::renderer,
		renderer
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		image2d,
		image2d
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		audio_loader,
		audio_loader
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		audio_player,
		audio_player
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		detail::input,
		input
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		font,
		font
	)
};

}

sge::systems::detail::any_key
sge::systems::make_any_key(
	sge::systems::detail::any const &_any
)
{
	return
		fcppt::variant::apply_unary(
			::make_key_visitor(),
			_any
		);
}
