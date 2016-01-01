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


#include <sge/font/dim.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/v_center.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/get_focus.hpp>
#include <sge/gui/needed_width.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


sge::gui::widget::button::button(
	sge::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_text,
	sge::gui::optional_needed_width const _opt_needed_width
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
	static_text_(
		this->make_static_text(
			_text
		)
	),
	layout_{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					fcppt::optional::maybe(
						_opt_needed_width,
						[
							this
						]{
							return
								static_text_.logical_size().w();
						},
						[](
							sge::gui::needed_width const _needed_width
						)
						{
							return
								_needed_width.get();
						}
					)
					+
					_style.button_spacing().w()
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					_font.metrics().height().get()
					+
					_style.button_spacing().h()
				}
			}
		}
	},
	click_()
{
}

sge::gui::widget::button::~button()
{
}

fcppt::signal::auto_connection
sge::gui::widget::button::click(
	sge::gui::click_callback const &_callback
)
{
	return
		click_.connect(
			_callback
		);
}

sge::font::string const &
sge::gui::widget::button::text() const
{
	return
		text_;
}

void
sge::gui::widget::button::text(
	sge::font::string const &_text
)
{
	static_text_ =
		this->make_static_text(
			_text
		);
}

sge::rucksack::widget::base &
sge::gui::widget::button::layout()
{
	return
		layout_;
}

void
sge::gui::widget::button::on_draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	style_.draw_button(
		_renderer,
		_context,
		this->layout().area()
	);

	static_text_.pos(
		fcppt::math::vector::structure_cast<
			sge::font::vector,
			fcppt::cast::size_fun
		>(
			layout_.position()
			+
			style_.button_spacing()
			/
			2
		)
		+
		sge::font::vector(
			0,
			sge::font::v_center(
				font_.metrics().height(),
				layout_.size().h()
				-
				style_.button_spacing().h()
			)
		)
	);

	_renderer.draw_static_text(
		_context,
		static_text_
	);
}

sge::gui::get_focus
sge::gui::widget::button::on_click(
	sge::rucksack::vector
)
{
	if(
		!this->enabled()
	)
		return
			sge::gui::get_focus(
				false
			);

	click_();

	return
		sge::gui::get_focus(
			true
		);
}

sge::font::draw::static_text
sge::gui::widget::button::make_static_text(
	sge::font::string const &_text
)
{
	return
		sge::font::draw::static_text(
			renderer_,
			font_,
			_text,
			sge::font::text_parameters(
				sge::font::align_h::variant{
					sge::font::align_h::left()
				}
			)
			.flags(
				sge::font::flags_field{
					sge::font::flags::no_multi_line
				}
			),
			fcppt::math::vector::null<
				sge::font::vector
			>(),
			style_.text_color().get(),
			sge::renderer::texture::emulate_srgb::no
		);
}
