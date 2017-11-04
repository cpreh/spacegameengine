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
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/static_text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sge::gui::widget::static_text::static_text(
	sge::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_value,
	sge::gui::text_color const &_text_color
)
:
	sge::gui::widget::base(),
	style_(
		_style
	),
	static_text_(
		_renderer,
		_font,
		_value,
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
		_text_color.get(),
		sge::renderer::texture::emulate_srgb::no
	),
	layout_{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					static_text_.logical_size().w()
					+
					style_.text_spacing().w()
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					_font.metrics().height().get()
					+
					style_.text_spacing().h()
				}
			}
		}
	}
{
}

sge::gui::widget::static_text::~static_text()
{
}

sge::rucksack::widget::base &
sge::gui::widget::static_text::layout()
{
	return
		layout_;
}

void
sge::gui::widget::static_text::on_draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	style_.draw_text(
		_renderer,
		_context,
		this->layout().area()
	);

	static_text_.pos(
		fcppt::math::vector::structure_cast<
			sge::font::vector,
			fcppt::cast::size_fun
		>(
			this->layout().position()
			+
			(
				style_.text_spacing()
				/
				2
			).get_unsafe()
		)
	);

	_renderer.draw_static_text(
		_context,
		static_text_
	);
}
