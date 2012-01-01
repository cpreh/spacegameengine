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


#include <sge/input/forward_discover.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/src/systems/modules/input/cursor_modifier.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::systems::modules::input::cursor_modifier::cursor_modifier(
	sge::input::processor &_processor,
	systems::cursor_option_field const &_options
)
:
	options_(_options),
	connection_(
		_processor.cursor_discover_callback(
			std::tr1::bind(
				&sge::systems::modules::input::cursor_modifier::cursor_discover,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
	sge::input::forward_discover<
		sge::input::cursor::discover_event
	>(
		_processor.cursors(),
		&sge::systems::modules::input::cursor_modifier::cursor_discover,
		*this
	);
}
FCPPT_PP_POP_WARNING

sge::systems::modules::input::cursor_modifier::~cursor_modifier()
{
}

void
sge::systems::modules::input::cursor_modifier::cursor_discover(
	sge::input::cursor::discover_event const &_event
)
{
	if(
		options_ & systems::cursor_option::exclusive
	)
		_event.object()->mode(
			sge::input::cursor::mode::exclusive
		);
}
