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


#include <sge/src/systems/make_any_key.hpp>
#include <sge/systems/any.hpp>
#include <sge/systems/any_types.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace
{

struct make_key_visitor
{
	typedef sge::systems::any_key::type result_type;

#define SGE_SYSTEMS_MAKE_KEY_CASE(\
	name\
)\
	result_type \
	operator()( \
		sge::systems::name const & \
	) const \
	{ \
		return \
			sge::systems::any_key::name;\
	}

	SGE_SYSTEMS_MAKE_KEY_CASE(
		config
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		window
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		renderer
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		image2d
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		audio_loader
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		audio_player
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		input
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		charconv
	)

	SGE_SYSTEMS_MAKE_KEY_CASE(
		font
	)
};

}

sge::systems::any_key::type
sge::systems::make_any_key(
	sge::systems::any const &_any
)
{
	return
		fcppt::variant::apply_unary(
			::make_key_visitor(),
			_any
		);
}
