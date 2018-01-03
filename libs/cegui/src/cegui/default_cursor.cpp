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


#include <sge/cegui/default_cursor.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/cursor/event/button.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/input/cursor/event/scroll.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


sge::cegui::default_cursor::default_cursor(
	sge::cegui::syringe &_syringe
)
:
	syringe_{
		_syringe
	}
{
	// FIXME
	/*
	fcppt::optional::maybe_void(
		_cursor.position(),
		[
			this
		](
			sge::input::cursor::position const _pos
		)
		{
			syringe_.inject(
				_pos
			);
		}
	);*/
}

sge::cegui::default_cursor::~default_cursor()
{
}

void
sge::cegui::default_cursor::process_event(
	sge::input::event_base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::variant::dynamic_cast_<
			brigand::list<
				sge::input::cursor::event::button const,
				sge::input::cursor::event::move const,
				sge::input::cursor::event::scroll const
			>,
			fcppt::cast::dynamic_fun
		>(
			_event
		),
		[
			this
		](
			auto const &_variant
		)
		{
			fcppt::variant::match(
				_variant,
				[
					this
				](
					fcppt::reference<
						sge::input::cursor::event::button const
					> const _button_event
				)
				{
					this->syringe_.inject(
						_button_event.get()
					);
				},
				[
					this
				](
					fcppt::reference<
						sge::input::cursor::event::move const
					> const _move_event
				)
				{
					this->syringe_.inject(
						_move_event.get()
					);
				},
				[
					this
				](
					fcppt::reference<
						sge::input::cursor::event::scroll const
					> const _scroll_event
				)
				{
					this->syringe_.inject(
						_scroll_event.get()
					);
				}
			);
		}
	);
}
