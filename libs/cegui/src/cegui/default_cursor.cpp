//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <metal.hpp>
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
			metal::list<
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
