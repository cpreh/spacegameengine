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


#include <sge/cegui/default_focus.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/focus/event/key_repeat.hpp>
#include <sge/input/focus/event/text.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


sge::cegui::default_focus::default_focus(
	sge::cegui::syringe &_syringe
)
:
	syringe_{
		_syringe
	}
{
}

sge::cegui::default_focus::~default_focus()
{
}

void
sge::cegui::default_focus::process_event(
	sge::input::event_base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::variant::dynamic_cast_<
			brigand::list<
				sge::input::focus::event::key const,
				sge::input::focus::event::key_repeat const,
				sge::input::focus::event::text const
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
						sge::input::focus::event::key const
					> const _key_event
				)
				{
					this->syringe_.inject(
						_key_event.get()
					);
				},
				[
					this
				](
					fcppt::reference<
						sge::input::focus::event::key_repeat const
					> const _key_repeat_event
				)
				{
					this->syringe_.inject(
						_key_repeat_event.get()
					);
				},
				[
					this
				](
					fcppt::reference<
						sge::input::focus::event::text const
					> const _text_event
				)
				{
					this->syringe_.inject(
						_text_event.get()
					);
				}
			);
		}
	);
}
