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


#include <sge/gui/context.hpp>
#include <sge/gui/draw.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/master.hpp>
#include <sge/gui/impl/renderer/scoped.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/optional_focus.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/char_event.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/key_repeat_event.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/key/code.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::gui::master::master(
	sge::input::focus::object &_focus,
	sge::input::cursor::object &_cursor,
	sge::gui::context &_context,
	sge::gui::main_area::base &_main_area
)
:
	cursor_(
		_cursor
	),
	context_(
		_context
	),
	main_area_(
		_main_area
	),
	key_connection_(
		_focus.key_callback(
			sge::input::focus::key_callback{
				std::bind(
					&sge::gui::master::key_event,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	key_repeat_connection_(
		_focus.key_repeat_callback(
			sge::input::focus::key_repeat_callback{
				std::bind(
					&sge::gui::master::key_repeat_event,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	char_connection_(
		_focus.char_callback(
			sge::input::focus::char_callback{
				std::bind(
					&sge::gui::master::char_event,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	button_connection_(
		_cursor.button_callback(
			sge::input::cursor::button_callback{
				std::bind(
					&sge::gui::master::button_event,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
}

sge::gui::master::~master()
{
}

void
sge::gui::master::draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::gui::background::base &_background
)
{
	sge::gui::draw(
		_renderer,
		_context,
		_background,
		main_area_
	);
}

void
sge::gui::master::draw_with_states(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context,
	sge::gui::background::base &_background
)
{
	sge::gui::impl::renderer::scoped renderer(
		_renderer,
		_context
	);

	sge::gui::draw(
		renderer,
		_context,
		_background,
		main_area_
	);
}

void
sge::gui::master::update(
	sge::gui::duration const _duration
)
{
	this->widget().on_update(
		_duration
	);
}

void
sge::gui::master::key_event(
	sge::input::focus::key_event const &_event
)
{
	if(
		_event.pressed()
	)
		this->handle_key(
			_event.key().code()
		);
}

void
sge::gui::master::key_repeat_event(
	sge::input::focus::key_repeat_event const &_event
)
{
	this->handle_key(
		_event.key().code()
	);
}

void
sge::gui::master::char_event(
	sge::input::focus::char_event const &_event
)
{
	fcppt::optional::maybe_void(
		context_.focus(),
		[
			&_event
		](
			sge::gui::widget::base &_focus
		)
		{
			_focus.on_char(
				_event.character()
			);
		}
	);
}

void
sge::gui::master::button_event(
	sge::input::cursor::button_event const &_event
)
{
	fcppt::optional::maybe_void(
		cursor_.position(),
		[
			this,
			&_event
		](
			sge::input::cursor::position const _pos
		)
		{
			if(
				_event.pressed()
				&&
				_event.button_code()
				==
				sge::input::cursor::button_code::left
			)
				this->widget().on_click(
					fcppt::math::vector::structure_cast<
						sge::rucksack::vector,
						fcppt::cast::size_fun
					>(
						_pos
					)
				);
		}
	);
}

void
sge::gui::master::handle_key(
	sge::input::key::code const _key_code
)
{
	if(
		_key_code
		==
		sge::input::key::code::tab
	)
	{
		// If no focus was found, try one more time using no focus
		// because the search can wrap around.
		if(
			!this->try_focus(
				sge::gui::widget::optional_focus(
					context_.focus()
				)
			).has_value()
		)
			this->try_focus(
				sge::gui::widget::optional_focus(
					sge::gui::widget::optional_ref()
				)
			);

		return;
	}

	fcppt::optional::maybe_void(
		context_.focus(),
		[
			_key_code
		](
			sge::gui::widget::base &_focus
		)
		{
			_focus.on_key(
				_key_code
			);
		}
	);
}

sge::gui::widget::optional_ref
sge::gui::master::try_focus(
	sge::gui::widget::optional_focus _focus
)
{
	sge::gui::widget::optional_ref const result(
		this->widget().on_tab(
			_focus
		)
	);

	fcppt::optional::maybe_void(
		result,
		[
			this
		](
			sge::gui::widget::base &_focus_window
		)
		{
			context_.focus(
				_focus_window
			);
		}
	);

	return
		result;
}

sge::gui::widget::base &
sge::gui::master::widget()
{
	return
		main_area_.widget();
}
