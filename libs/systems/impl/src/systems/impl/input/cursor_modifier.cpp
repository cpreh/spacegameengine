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


#include <sge/input/processor.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/discover.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/impl/input/cursor_modifier.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::systems::impl::input::cursor_modifier::cursor_modifier(
	sge::input::processor const &_processor,
	sge::window::object &_window,
	sge::systems::cursor_option_field const &_options
)
:
	options_{
		_options
	},
	connection_{
		_window.event_handler(
			sge::window::event_function{
				std::bind(
					&sge::systems::impl::input::cursor_modifier::on_event,
					this,
					std::placeholders::_1
				)
			}
		)
	}
{
	if(
		this->options_
		&
		sge::systems::cursor_option::exclusive
	)
		for(
			sge::input::cursor::shared_ptr const &cursor
			:
			_processor.cursors()
		)
			cursor->mode(
				sge::input::cursor::mode::exclusive
			);

}
FCPPT_PP_POP_WARNING

sge::systems::impl::input::cursor_modifier::~cursor_modifier()
{
}

awl::event::container
sge::systems::impl::input::cursor_modifier::on_event(
	awl::window::event::base const &_event
) const
{
	if(
		this->options_
		&
		sge::systems::cursor_option::exclusive
	)
		fcppt::optional::maybe_void(
			fcppt::cast::dynamic<
				sge::input::cursor::event::discover const
			>(
				_event
			),
			[](
				fcppt::reference<
	 				sge::input::cursor::event::discover const
				> const _discover
			)
			{
				_discover.get().cursor()->mode(
					sge::input::cursor::mode::exclusive
				);
			}
		);

	return
		awl::event::container();
}
