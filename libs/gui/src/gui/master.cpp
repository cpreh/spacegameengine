//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/context.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/draw.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/master.hpp>
#include <sge/gui/impl/renderer/scoped.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/main_area/reference.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/optional_focus.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/event/button.hpp>
#include <sge/input/focus/char_type.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/focus/event/key_repeat.hpp>
#include <sge/input/focus/event/text.hpp>
#include <sge/input/key/code.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


sge::gui::master::master(
	sge::gui::context_ref const _context,
	sge::gui::main_area::reference const _main_area
)
:
	context_{
		_context
	},
	main_area_{
		_main_area
	}
{
}

sge::gui::master::~master()
= default;

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
		main_area_.get()
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
		fcppt::make_ref(
			_renderer
		),
		fcppt::make_ref(
			_context
		)
	);

	sge::gui::draw(
		renderer,
		_context,
		_background,
		main_area_.get()
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
sge::gui::master::process_event(
	sge::input::event_base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::variant::dynamic_cast_<
			metal::list<
				sge::input::focus::event::key const,
				sge::input::focus::event::key_repeat const,
				sge::input::focus::event::text const,
				sge::input::cursor::event::button const
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
					this->key_event(
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
					this->key_repeat_event(
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
					this->text_event(
						_text_event.get()
					);
				},
				[
					this
				](
					fcppt::reference<
						sge::input::cursor::event::button const
					> const _button_event
				)
				{
					this->button_event(
						_button_event.get()
					);
				}
			);
		}
	);
}

void
sge::gui::master::key_event(
	sge::input::focus::event::key const &_event
)
{
	if(
		_event.pressed()
	)
	{
		this->handle_key(
			_event.get().code()
		);
	}
}

void
sge::gui::master::key_repeat_event(
	sge::input::focus::event::key_repeat const &_event
)
{
	this->handle_key(
		_event.key().code()
	);
}

void
sge::gui::master::text_event(
	sge::input::focus::event::text const &_event
)
{
	fcppt::optional::maybe_void(
		context_.get().focus(),
		[
			&_event
		](
			fcppt::reference<
				sge::gui::widget::base
			> const _focus
		)
		{
			for(
				sge::input::focus::char_type const element
				:
				_event.get()
			)
			{
				_focus.get().on_char(
					element
				);
			}
		}
	);
}

void
sge::gui::master::button_event(
	sge::input::cursor::event::button const &_event
)
{
	fcppt::optional::maybe_void(
		_event.cursor()->position(),
		[
			this,
			&_event
		](
			sge::input::cursor::position const &_pos
		)
		{
			if(
				_event.pressed()
				&&
				_event.button_code()
				==
				sge::input::cursor::button_code::left
			)
			{
				this->widget().on_click(
					fcppt::math::vector::structure_cast<
						sge::rucksack::vector,
						fcppt::cast::size_fun
					>(
						_pos
					)
				);
			}
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
					context_.get().focus()
				)
			).has_value()
		)
		{
			this->try_focus(
				sge::gui::widget::optional_focus(
					sge::gui::widget::optional_ref()
				)
			);
		}

		return;
	}

	fcppt::optional::maybe_void(
		context_.get().focus(),
		[
			_key_code
		](
			fcppt::reference<
				sge::gui::widget::base
			> const _focus
		)
		{
			_focus.get().on_key(
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
			fcppt::make_ref(
				_focus
			)
		)
	);

	fcppt::optional::maybe_void(
		result,
		[
			this
		](
			fcppt::reference<
				sge::gui::widget::base
			> const _focus_window
		)
		{
			context_.get().focus(
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
		main_area_.get().widget();
}
