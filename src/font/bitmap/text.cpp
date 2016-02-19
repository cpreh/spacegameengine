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


#include <sge/font/dim.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/view.hpp>
#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/any/clear.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/src/font/bitmap/char_map.hpp>
#include <sge/src/font/bitmap/char_metric.hpp>
#include <sge/src/font/bitmap/char_metric_ref_vector.hpp>
#include <sge/src/font/bitmap/const_view.hpp>
#include <sge/src/font/bitmap/line.hpp>
#include <sge/src/font/bitmap/line_height.hpp>
#include <sge/src/font/bitmap/make_rep.hpp>
#include <sge/src/font/bitmap/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/box/null.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_unsigned.hpp>
#include <fcppt/variant/match.hpp>


sge::font::bitmap::text::text(
	sge::font::bitmap::char_map const &_char_map,
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters,
	sge::font::bitmap::line_height const _line_height
)
:
	line_height_(
		_line_height
	),
	align_h_(
		_text_parameters.align_h()
	),
	rep_(
		sge::font::bitmap::make_rep(
			_char_map,
			_line_height,
			_string,
			_text_parameters
		)
	)
{
}

sge::font::bitmap::text::~text()
{
}

void
sge::font::bitmap::text::render(
	sge::font::view const &_view
)
{
	sge::image2d::algorithm::fill(
		sge::image2d::view::sub(
			_view,
			sge::image2d::rect(
				fcppt::math::vector::null<
					sge::image2d::rect::vector
				>(),
				fcppt::math::dim::structure_cast<
					sge::image2d::rect::dim,
					fcppt::cast::size_fun
				>(
					fcppt::math::dim::to_unsigned(
						rep_.rect().size()
					)
				)
			)
		),
		sge::image::color::any::clear(
			sge::image2d::view::format(
				_view
			)
		),
		sge::image::algorithm::uninitialized::yes
	);

	sge::font::unit top(
		0u
	);

	for(
		sge::font::bitmap::line const &line
		:
		rep_.lines()
	)
	{
		sge::font::unit left(
			fcppt::variant::match(
				align_h_,
				[](
					sge::font::align_h::left const &
				)
				{
					return
						0;
				},
				[
					&line,
					this
				](
					sge::font::align_h::center const &
				)
				{
					return
						(
							this->logical_size().w()
							-
							line.width()
						)
						/
						2;
				},
				[
					&line,
					this
				](
					sge::font::align_h::right const &
				)
				{
					return
						this->logical_size().w()
						-
						line.width();
				}
			)
		);

		sge::font::bitmap::char_metric_ref_vector const &metrics(
			line.char_metrics()
		);

		for(
			auto const &metric
			:
			metrics
		)
		{
			sge::font::bitmap::char_metric const &char_metric(
				metric.get()
			);

			sge::font::bitmap::const_view const source_view(
				char_metric.view()
			);

			sge::image2d::algorithm::copy_and_convert(
				source_view,
				sge::image2d::view::sub(
					_view,
					sge::image2d::rect(
						sge::image2d::rect::vector(
							fcppt::cast::size<
								sge::image::size_type
							>(
								fcppt::cast::to_unsigned(
									left
								)
							),
							fcppt::cast::size<
								sge::image::size_type
							>(
								fcppt::cast::to_unsigned(
									top
								)
							)
						),
						sge::image2d::view::size(
							source_view
						)
					)
				),
				sge::image::algorithm::may_overlap::no,
				sge::image::algorithm::uninitialized::no
			);

			left +=
				char_metric.x_advance();
		}

		top +=
			line_height_.get();
	}
}

sge::font::rect
sge::font::bitmap::text::rect() const
{
	return
		rep_.rect();
}

sge::font::dim
sge::font::bitmap::text::logical_size() const
{
	return
		this->rect().size();
}

sge::font::rect
sge::font::bitmap::text::cursor_rect(
	sge::font::index const _index
) const
{
	// FIXME
	return
		fcppt::math::box::null<
			sge::font::rect
		>();
}

sge::font::optional_index
sge::font::bitmap::text::pos_to_index(
	sge::font::vector const _pos
) const
{
	// FIXME
	return
		sge::font::optional_index();
}
