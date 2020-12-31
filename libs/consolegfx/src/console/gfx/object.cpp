//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/console/error_callback.hpp>
#include <sge/console/exception.hpp>
#include <sge/console/message_callback.hpp>
#include <sge/console/object.hpp>
#include <sge/console/object_ref.hpp>
#include <sge/console/gfx/font_color.hpp>
#include <sge/console/gfx/input_active.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/output_line_limit.hpp>
#include <sge/console/gfx/detail/pointed_history.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/input/focus/char_type.hpp>
#include <sge/input/focus/key.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/focus/event/key_repeat.hpp>
#include <sge/input/focus/event/text.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/modifier.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/iterator/make_range.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <locale>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::console::gfx::object::object(
	sge::console::object_ref const _object,
	sge::renderer::device::ffp_ref const _renderer,
	sge::console::gfx::font_color _font_color,
	sge::font::object_ref const _font_object,
	sge::font::rect const _area,
	sge::console::gfx::output_line_limit const _line_limit
)
:
	object_{
		_object
	},
	renderer_{
		_renderer
	},
	font_color_{
		std::move(
			_font_color
		)
	},
	font_object_{
		_font_object
	},
	mod_state_tracker_{},
	error_connection_(
		object_.get().register_error_callback(
			sge::console::error_callback{
				[
					this
				](
					sge::font::string const &_string
				)
				{
					this->error(
						sge::font::string{
							_string
						}
					);
				}
			}
		)
	),
	message_connection_(
		object_.get().register_message_callback(
			sge::console::message_callback{
				[
					this
				](
					sge::font::string const &_string
				)
				{
					this->print(
						sge::font::string{
							_string
						}
					);
				}
			}
		)
	),
	area_{
		_area
	},
	input_line_(),
	input_history_(),
	current_input_(
		input_history_.begin()
	),
	output_lines_(
		fcppt::cast::size<
			sge::console::gfx::detail::pointed_history::size_type
		>(
			_line_limit.get()
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::console::gfx::object::~object()
= default;

void
sge::console::gfx::object::render(
	sge::renderer::context::ffp &_render_context,
	sge::console::gfx::input_active const _input_active
)
{
	sge::font::unit current_y(
		area_.size().h()
	);

	if(
		_input_active.get()
	)
	{
		current_y =
			this->render_line(
				_render_context,
				input_line_.edited(),
				current_y
			);
	}

	for(
		auto const &element
		:
		fcppt::iterator::make_range(
			output_lines_.point(),
			output_lines_.end()
		)
	)
	{
		current_y =
			this->render_line(
				_render_context,
				element,
				current_y
			);

		if(
			current_y < 0
		)
		{
			break;
		}
	}
}

void
sge::console::gfx::object::focus_event(
	sge::input::focus::event::base const &_event
)
{
	mod_state_tracker_.event(
		_event
	);

	fcppt::optional::maybe_void(
		fcppt::variant::dynamic_cast_<
			metal::list<
				sge::input::focus::event::text const,
				sge::input::focus::event::key const,
				sge::input::focus::event::key_repeat const
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
						sge::input::focus::event::text const
					> const _text_event
				)
				{
					this->on_text(
						_text_event.get()
					);
				},
				[
					this
				](
					fcppt::reference<
						sge::input::focus::event::key const
					> const _key_event
				)
				{
					this->on_key(
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
					this->on_key_repeat(
						_key_repeat_event.get()
					);
				}
			);
		}
	);
}

void
sge::console::gfx::object::area(
	sge::font::rect const &_area
)
{
	area_ =
		_area;
}

sge::console::object &
sge::console::gfx::object::console_object()
{
	return
		object_.get();
}

sge::console::object const &
sge::console::gfx::object::console_object() const
{
	return
		object_.get();
}

void
sge::console::gfx::object::print(
	sge::font::string &&_string
)
{
	output_lines_.push_front(
		std::move(
			_string
		)
	);
}

sge::font::unit
sge::console::gfx::object::render_line(
	sge::renderer::context::ffp &_render_context,
	sge::font::string const &_line,
	sge::font::unit const _current_y
)
{
	sge::font::draw::static_text static_text(
		renderer_,
		font_object_,
		_line,
		sge::font::text_parameters(
			sge::font::align_h::variant{
				sge::font::align_h::left(
					sge::font::align_h::max_width(
						area_.size().w()
					)
				)
			}
		),
		fcppt::math::vector::null<
			sge::font::vector
		>(),
		font_color_.get(),
		sge::renderer::texture::emulate_srgb::no
	);

	// TODO(philipp): Make this easier
	sge::font::vector const pos(
		0,
		_current_y
		-
		static_text.rect().bottom()
	);

	static_text.pos(
		pos
		+
		area_.pos()
	);

	static_text.draw(
		_render_context
	);

	return
		pos.y();
}

void
sge::console::gfx::object::on_key(
	sge::input::focus::event::key const &_event
)
{
	if(
		_event.pressed()
	)
	{
		this->key_action(
			_event.focus(),
			_event.get()
		);
	}
}

void
sge::console::gfx::object::on_text(
	sge::input::focus::event::text const &_event
)
{
	for(
		sge::input::focus::char_type const element
		:
		_event.get()
	)
	{
		if(
			std::isprint(
				element,
				std::locale()
			)
		)
		{
			input_line_.insert(
				element
			);
		}
	}
}

void
sge::console::gfx::object::on_key_repeat(
	sge::input::focus::event::key_repeat const &_event
)
{
	this->key_action(
		_event.focus(),
		_event.key()
	);
}

void
sge::console::gfx::object::key_action(
	sge::input::focus::shared_ptr const &_focus,
	sge::input::focus::key const &_key
)
{
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_CLANG_WARNING(-Wswitch-enum)

	switch(
		_key.code()
	)
	{
		case sge::input::key::code::w:
			if(
				mod_state_tracker_.mod_state(
					_focus
				)
				&
				sge::input::key::modifier::control
			)
			{
				input_line_.erase_word();
			}
		break;
		case sge::input::key::code::delete_:
			input_line_.erase_char();
		break;
		case sge::input::key::code::backspace:
			input_line_.left();
			input_line_.erase_char();
		break;
		case sge::input::key::code::tab:
			input_line_.complete_word(
				object_.get().prefix(),
				object_.get().functions()
			);
		break;
		case sge::input::key::code::pageup:
			if(
				mod_state_tracker_.mod_state(
					_focus
				)
				&
				sge::input::key::modifier::shift
			)
			{
				output_lines_.to_end();
			}
			else
			{
				output_lines_.up();
			}
		break;
		case sge::input::key::code::pagedown:
			if(
				mod_state_tracker_.mod_state(
					_focus
				)
				&
				sge::input::key::modifier::shift
			)
			{
				output_lines_.to_begin();
			}
			else
			{
				output_lines_.down();
			}
		break;
		case sge::input::key::code::up:
			if(
				input_history_.empty()
			)
			{
				return;
			}

			input_line_.string(
				*current_input_
			);

			if(current_input_ != --input_history_.end())
			{
				++current_input_;
			}
		break;
		case sge::input::key::code::down:
			if(current_input_ != input_history_.begin())
			{
				--current_input_;

				input_line_.string(
					*current_input_
				);
			}
		break;
		case sge::input::key::code::left:
			input_line_.left();
		break;
		case sge::input::key::code::right:
			input_line_.right();
		break;
		case sge::input::key::code::home:
			input_line_.to_start();
		break;
		case sge::input::key::code::end:
			input_line_.to_end();
		break;
		case sge::input::key::code::return_:
			if (input_line_.empty())
			{
				return;
			}

			try
			{
				object_.get().eval(
					input_line_.string()
				);
			}
			catch(
				sge::console::exception const &_error
			)
			{
				this->print(
					SGE_FONT_LIT("console error: ")
					+
					_error.console_string()
				);
			}

			// add executed command to each history (at the front)...
			input_history_.push_front(
				input_line_.string()
			);

			current_input_ =
				input_history_.begin();

			// clear input line
			input_line_.string(
				SGE_FONT_LIT("")
			);
		break;
		default:
		break;
	}

	FCPPT_PP_POP_WARNING
}

void
sge::console::gfx::object::error(
	sge::font::string &&_string
)
{
	this->print(
		SGE_FONT_LIT("command error: ")
		+
		std::move(
			_string
		)
	);
}
