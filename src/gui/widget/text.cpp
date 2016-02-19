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


#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/v_center.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/gui/needed_width.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/impl/relayout_ancestor.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe.hpp>


sge::gui::widget::text::text(
	sge::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_value,
	sge::gui::text_color const &_text_color,
	sge::gui::optional_needed_width const _needed_width
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
	text_color_(
		_text_color
	),
	needed_width_(
		_needed_width
	),
	value_(
		_value
	),
	layout_{
		sge::rucksack::axis_policy2{
			this->horizontal_policy(),
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					font_.metrics().height().get()
					+
					style_.text_spacing().h()
				}
			}
		}
	}
{
}

sge::gui::widget::text::~text()
{
}

void
sge::gui::widget::text::value(
	sge::font::string const &_value
)
{
	value_ =
		_value;

	layout_.axis_policy(
		sge::rucksack::axis_policy2(
			this->horizontal_policy(),
			layout_.axis_policy().y()
		)
	);

	sge::gui::impl::relayout_ancestor(
		*this
	);
}

void
sge::gui::widget::text::text_color(
	sge::gui::text_color const &_text_color
)
{
	text_color_ =
		_text_color;
}

sge::rucksack::widget::base &
sge::gui::widget::text::layout()
{
	return
		layout_;
}

void
sge::gui::widget::text::on_draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	style_.draw_text(
		_renderer,
		_context,
		this->layout().area()
	);

	sge::font::draw::static_text const static_text(
		renderer_,
		font_,
		value_,
		sge::font::text_parameters(
			sge::font::align_h::variant{
				sge::font::align_h::center(
					sge::font::align_h::max_width(
						layout_.size().w()
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
		)
		+
		sge::font::vector(
			0,
			sge::font::v_center(
				font_.metrics().height(),
				layout_.size().h()
			)
		),
		text_color_.get(),
		sge::renderer::texture::emulate_srgb::no
	);

	_renderer.draw_static_text(
		_context,
		static_text
	);
}

sge::rucksack::axis_policy
sge::gui::widget::text::horizontal_policy() const
{
	return
		sge::rucksack::axis_policy{
			sge::rucksack::preferred_size{
				fcppt::optional::maybe(
					needed_width_,
					[
						this
					]{
						return
							font_.create_text(
								value_,
								sge::font::text_parameters(
									sge::font::align_h::variant{
										sge::font::align_h::left()
									}
								)
							)->logical_size().w();
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
				style_.text_spacing().w()
			}
		};
}
