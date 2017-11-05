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


#include <sge/font/char_type.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/index.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/v_center.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/focus_change.hpp>
#include <sge/gui/get_focus.hpp>
#include <sge/gui/text_callback.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/text_function.hpp>
#include <sge/gui/impl/fill_rect.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/edit.hpp>
#include <sge/gui/widget/optional_focus.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/input/key/code.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/timer/basic_impl.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <sge/timer/clocks/delta_impl.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/string_conv_locale.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <chrono>
#include <locale>
#include <fcppt/config/external_end.hpp>


sge::gui::widget::edit::edit(
	sge::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_text
)
:
	sge::gui::widget::base(),
	style_(
		_style
	),
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	text_(
		_text
	),
	position_{
		0u
	},
	layout_{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::minimum_size{
					_style.edit_spacing().w()
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					font_.metrics().height().get()
					+
					_style.edit_spacing().h()
				}
			}
		}
	},
	static_text_(
		this->make_static_text()
	),
	clock_(),
	cursor_blink_timer_(
		diff_timer::parameters(
			clock_,
			std::chrono::milliseconds(
				500
			)
		)
	),
	has_focus_(
		false
	),
	show_cursor_(
		true
	),
	text_change_()
{
}

sge::gui::widget::edit::~edit()
{
}

sge::font::string const &
sge::gui::widget::edit::text() const
{
	return
		text_;
}

fcppt::signal::auto_connection
sge::gui::widget::edit::text_change(
	sge::gui::text_callback const &_callback
)
{
	return
		text_change_.connect(
			_callback
		);
}

sge::rucksack::widget::base &
sge::gui::widget::edit::layout()
{
	return
		layout_;
}

void
sge::gui::widget::edit::on_update(
	sge::gui::duration const _duration
)
{
	if(
		!has_focus_
	)
		return;

	clock_.update(
		_duration
	);

	if(
		sge::timer::reset_when_expired(
			cursor_blink_timer_
		)
	)
		show_cursor_ =
			!show_cursor_;
}

void
sge::gui::widget::edit::on_draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	// TODO: Add a signal to sge that tells us when a layout changes
	static_text_ =
		this->make_static_text();

	style_.draw_edit(
		_renderer,
		_context,
		this->layout().area()
	);

	_renderer.draw_static_text(
		_context,
		static_text_
	);

	if(
		!has_focus_
		||
		!show_cursor_
	)
		return;

	sge::font::rect const cursor_rect(
		static_text_.text().cursor_rect(
			position_
		)
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			cursor_rect.pos()
			+
			static_text_.pos(),
			sge::font::dim(
				// TODO: How do we specify the width?
				2,
				cursor_rect.size().h()
			)
		),
		style_.text_color().get()
	);
}

sge::gui::get_focus
sge::gui::widget::edit::on_click(
	sge::rucksack::vector const _pos
)
{
	fcppt::optional::maybe(
		static_text_.text().pos_to_index(
			fcppt::math::vector::structure_cast<
				sge::font::vector,
				fcppt::cast::size_fun
			>(
				_pos
			)
			-
			static_text_.pos()
		),
		[
			_pos,
			this
		]{
			if(
				_pos.x()
				>=
				static_text_.rect().size().w()
				+
				static_text_.pos().x()
			)
				position_
					= text_.size();
		},
		[
			this
		](
			sge::font::index const _index
		)
		{
			FCPPT_ASSERT_ERROR(
				_index
				<=
				text_.size()
			);

			position_ =
				_index;
		}
	);

	return
		sge::gui::get_focus(
			true
		);
}

void
sge::gui::widget::edit::on_key(
	sge::input::key::code const _code
)
{
	switch(
		_code
	)
	{
	case sge::input::key::code::left:
		if(
			position_ != 0u
		)
			--position_;

		break;
	case sge::input::key::code::right:
		if(
			position_ < text_.size()
		)
			++position_;

		break;
	case sge::input::key::code::delete_:
		if(
			position_ != text_.size()
		)
		{
			text_.erase(
				position_,
				1u
			);

			this->text_changed();
		}

		break;
	case sge::input::key::code::backspace:
		if(
			position_ - 1u
			<
			text_.size()
		)
		{
			text_.erase(
				position_ - 1u,
				1u
			);

			--position_;

			this->text_changed();
		}

		break;
	default:
		break;
	}
}

void
sge::gui::widget::edit::on_char(
	sge::font::char_type const _char
)
{
	if(
		!std::isprint(
			_char,
			fcppt::string_conv_locale()
		)
	)
		return;

	text_.insert(
		position_,
		1u,
		_char
	);

	++position_;

	this->text_changed();
}

void
sge::gui::widget::edit::on_focus_changed(
	sge::gui::focus_change const _change
)
{
	has_focus_ =
		_change
		==
		sge::gui::focus_change::gained;

	if(
		has_focus_
	)
	{
		show_cursor_ =
			true;

		cursor_blink_timer_.reset();
	}
}

sge::gui::widget::optional_ref
sge::gui::widget::edit::on_tab(
	sge::gui::widget::optional_focus &
)
{
	return
		sge::gui::widget::optional_ref(
			fcppt::reference_to_base<
				sge::gui::widget::base
			>(
				fcppt::make_ref(
					*this
				)
			)
		);
}

sge::font::draw::static_text
sge::gui::widget::edit::make_static_text()
{
	return
		sge::font::draw::static_text(
			renderer_,
			font_,
			text_,
			sge::font::text_parameters(
				sge::font::align_h::variant{
					sge::font::align_h::left(
						sge::font::align_h::max_width(
							std::max(
								layout_.size().w()
								-
								style_.edit_spacing().w(),
								fcppt::literal<
									sge::font::unit
								>(
									0
								)
							)
						)
					)
				}
			)
			.flags(
				sge::font::flags_field{
					sge::font::flags::no_multi_line
				}
			),
			fcppt::math::vector::structure_cast<
				sge::font::vector,
				fcppt::cast::size_fun
			>(
				layout_.position()
				+
				fcppt::math::vector::fill<
					sge::rucksack::vector
				>(
					style_.edit_spacing().w()
					/
					2
				)
			)
			+
			sge::font::vector(
				0,
				sge::font::v_center(
					font_.metrics().height(),
					layout_.size().h()
					-
					style_.edit_spacing().h()
				)
			),
			style_.text_color().get(),
			sge::renderer::texture::emulate_srgb::no
		);
}

void
sge::gui::widget::edit::text_changed()
{
	static_text_ =
		this->make_static_text();

	text_change_(
		this->text()
	);
}
