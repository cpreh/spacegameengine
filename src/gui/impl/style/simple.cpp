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


#include <sge/gui/fill_color.hpp>
#include <sge/gui/fill_level.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/impl/shrink_rect.hpp>
#include <sge/gui/impl/style/background_color.hpp>
#include <sge/gui/impl/style/border_color.hpp>
#include <sge/gui/impl/style/inner_border.hpp>
#include <sge/gui/impl/style/outer_border.hpp>
#include <sge/gui/impl/style/simple.hpp>
#include <sge/gui/impl/style/spacing.hpp>
#include <sge/gui/impl/style/text_color.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sge::gui::impl::style::simple::simple()
:
	sge::gui::style::base()
{
}

sge::gui::impl::style::simple::~simple()
{
}

sge::rucksack::dim const
sge::gui::impl::style::simple::button_spacing() const
{
	return
		this->spacing();
}

void
sge::gui::impl::style::simple::draw_button(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
) const
{
	_renderer.fill_rect(
		_context,
		_area,
		sge::gui::impl::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sge::gui::impl::style::outer_border::value,
			_area.size()
			-
			2
			*
			sge::gui::impl::style::outer_border::value
		),
		sge::gui::impl::style::background_color()
	);
}

void
sge::gui::impl::style::simple::draw_bar(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area,
	sge::rucksack::axis const _axis,
	sge::gui::fill_level const _fill_level,
	sge::gui::fill_color const &_fill_color
) const
{
	_renderer.fill_rect(
		_context,
		_area,
		sge::gui::impl::style::border_color()
	);

	sge::rucksack::rect const inner_rect(
		sge::gui::impl::shrink_rect(
			_area,
			sge::gui::impl::style::outer_border::value
		)
	);

	_renderer.fill_rect(
		_context,
		inner_rect,
		sge::gui::impl::style::background_color()
	);

	sge::rucksack::scalar const fill_size(
		fcppt::cast::float_to_int<
			sge::rucksack::scalar
		>(
			fcppt::cast::int_to_float<
				sge::gui::fill_level::value_type
			>(
				inner_rect.size()[
					// TODO: Make a function in rucksack for this
					fcppt::cast::enum_to_int<
						fcppt::math::size_type
					>(
						_axis
					)
				]
			)
			*
			_fill_level.get()
		)
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_axis
			==
			sge::rucksack::axis::y
			?
				sge::rucksack::vector(
					inner_rect.pos().x(),
					inner_rect.pos().y()
					+
					inner_rect.h()
					-
					fill_size
				)
			:
				inner_rect.pos()
			,
			sge::rucksack::dim(
				_axis
				==
				sge::rucksack::axis::x
				?
					fill_size
				:
					inner_rect.w()
				,
				_axis
				==
				sge::rucksack::axis::y
				?
					fill_size
				:
					inner_rect.h()
			)
		),
		_fill_color.get()
	);

}

sge::rucksack::padding const
sge::gui::impl::style::simple::frame_padding() const
{
	return
		sge::rucksack::padding{
			10
		};
}

void
sge::gui::impl::style::simple::draw_frame(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area,
	sge::rucksack::padding const _padding
) const
{
	sge::rucksack::scalar const border_size(
		_padding.get()
		/
		2
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos(),
			sge::rucksack::dim(
				_area.w(),
				border_size
			)
		),
		sge::gui::impl::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos(),
			sge::rucksack::dim(
				border_size,
				_area.h()
			)
		),
		sge::gui::impl::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sge::rucksack::dim(
				_area.w()
				-
				border_size,
				0
			),
			sge::rucksack::dim(
				border_size,
				_area.h()
			)
		),
		sge::gui::impl::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sge::rucksack::dim(
				0,
				_area.h()
				-
				border_size
			),
			sge::rucksack::dim(
				_area.w(),
				border_size
			)
		),
		sge::gui::impl::style::border_color()
	);
}

sge::rucksack::dim const
sge::gui::impl::style::simple::edit_spacing() const
{
	return
		this->spacing();
}

void
sge::gui::impl::style::simple::draw_edit(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const _area
) const
{
	_renderer.fill_rect(
		_context,
		_area,
		sge::gui::impl::style::border_color()
	);

	_renderer.fill_rect(
		_context,
		sge::rucksack::rect(
			_area.pos()
			+
			sge::gui::impl::style::outer_border::value,
			_area.size()
			-
			2
			*
			sge::gui::impl::style::outer_border::value
		),
		sge::gui::impl::style::background_color()
	);
}

sge::rucksack::dim const
sge::gui::impl::style::simple::image_spacing() const
{
	return
		fcppt::math::dim::null<
			sge::rucksack::dim
		>();
}

void
sge::gui::impl::style::simple::draw_image(
	sge::gui::renderer::base &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect
) const
{
}

sge::rucksack::dim const
sge::gui::impl::style::simple::text_spacing() const
{
	return
		fcppt::math::dim::null<
			sge::rucksack::dim
		>();
}

void
sge::gui::impl::style::simple::draw_text(
	sge::gui::renderer::base &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect
) const
{
}

sge::gui::text_color
sge::gui::impl::style::simple::text_color() const
{
	return
		sge::gui::text_color(
			sge::gui::impl::style::text_color()
		);
}

sge::rucksack::dim const
sge::gui::impl::style::simple::spacing() const
{
	return
		fcppt::math::dim::fill<
			sge::rucksack::dim
		>(
			sge::gui::impl::style::spacing::value
		);
}
