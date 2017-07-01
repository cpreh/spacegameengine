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


#include <sge/gui/fill_color.hpp>
#include <sge/gui/fill_level.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/widget/bar.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/access_axis.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy_function.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base.hpp>


sge::gui::widget::bar::bar(
	sge::gui::style::base const &_style,
	sge::rucksack::dim const _dim,
	sge::rucksack::axis const _axis,
	sge::gui::fill_color const &_foreground,
	sge::gui::fill_level const _value
)
:
	sge::gui::widget::base(),
	style_(
		_style
	),
	axis_{
		_axis
	},
	foreground_(
		_foreground
	),
	value_(
		_value
	),
	layout_{
		sge::rucksack::make_axis_policy(
			sge::rucksack::axis_policy_function{
				[
					_axis,
					_dim
				](
					sge::rucksack::axis const _cur_axis
				)
				{
					sge::rucksack::scalar const ret{
						sge::rucksack::access_axis(
							_dim,
							_cur_axis
						)
					};

					return
						_axis
						==
						_cur_axis
						?
							sge::rucksack::axis_policy{
								sge::rucksack::minimum_size{
									ret
								}
							}
						:
							sge::rucksack::axis_policy{
								sge::rucksack::preferred_size{
									ret
								}
							}
						;
				}
			}
		)
	}
{
}

sge::gui::widget::bar::~bar()
{
}

void
sge::gui::widget::bar::value(
	sge::gui::fill_level const _value
)
{
	value_ =
		_value;
}

void
sge::gui::widget::bar::on_draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_render_context
)
{
	style_.draw_bar(
		_renderer,
		_render_context,
		this->layout().area(),
		axis_,
		value_,
		foreground_
	);
}

sge::rucksack::widget::base &
sge::gui::widget::bar::layout()
{
	return
		layout_;
}
