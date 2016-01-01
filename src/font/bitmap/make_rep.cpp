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


#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/extract_max_width.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/optional_max_width.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/src/font/bitmap/char_map.hpp>
#include <sge/src/font/bitmap/char_metric.hpp>
#include <sge/src/font/bitmap/char_metric_ref.hpp>
#include <sge/src/font/bitmap/line.hpp>
#include <sge/src/font/bitmap/line_height.hpp>
#include <sge/src/font/bitmap/line_vector.hpp>
#include <sge/src/font/bitmap/logger.hpp>
#include <sge/src/font/bitmap/make_rep.hpp>
#include <sge/src/font/bitmap/rep.hpp>
#include <fcppt/const.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iterator>
#include <locale>
#include <utility>
#include <fcppt/config/external_end.hpp>



sge::font::bitmap::rep
sge::font::bitmap::make_rep(
	sge::font::bitmap::char_map const &_char_map,
	sge::font::bitmap::line_height const _line_height,
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
{
	sge::font::bitmap::line_vector lines;

	sge::font::unit current_x(
		0
	);

	sge::font::unit last_space_width(
		0
	);

	sge::font::flags_field const flags(
		_text_parameters.flags()
	);

	sge::font::align_h::optional_max_width const max_width(
		sge::font::align_h::extract_max_width(
			_text_parameters.align_h()
		)
	);

	sge::font::bitmap::char_metric_ref_vector current_line;

	sge::font::unit width{
		0
	};

	for(
		sge::font::string::const_iterator
			it(
				_string.begin()
			),
			last_space(
				_string.end()
			);
		it != _string.end();
		++it
	)
	{
		// TODO: find_opt
		sge::font::bitmap::char_map::const_iterator const char_it(
			_char_map.find(
				*it
			)
		);

		if(
			char_it
			==
			_char_map.end()
		)
		{
			FCPPT_LOG_ERROR(
				sge::font::bitmap::logger(),
				fcppt::log::_
					<<
					FCPPT_TEXT("Bitmapfont character '")
					<<
					sge::font::to_fcppt_string(
						sge::font::string(
							1u,
							*it
						)
					)
					<<
					FCPPT_TEXT("' not available!")
			);

			continue;
		}

		sge::font::bitmap::char_metric const &metric(
			char_it->second
		);

		current_line.push_back(
			sge::font::bitmap::char_metric_ref(
				metric
			)
		);

		current_x += metric.x_advance();

		bool const space_exceeded(
			fcppt::optional::maybe(
				max_width,
				fcppt::const_(
					false
				),
				[
					current_x
				](
					sge::font::align_h::max_width const _max_width
				)
				{
					return
						current_x
						>
						_max_width.get();
				}
			)
		);

		bool const new_line(
			space_exceeded
			||
			std::next(
				it
			)
			==
			_string.end()
		);

		sge::font::unit current_width(
			current_x
		);

		if(
			space_exceeded
		)
		{
			if(
				current_line.empty()
			)
				break;

			// FIXME: This is probably broken
			if(
				!(
					flags
					&
					sge::font::flags::no_word_wrap
				)
				&&
				last_space
				!=
				_string.end()
			)
			{
				current_line.erase(
					current_line.end()
					-
					std::distance(
						last_space,
						it
					),
					current_line.end()
				);

				it = last_space;

				current_width = last_space_width;
			}
			else
			{
				current_line.pop_back();

				current_width -= metric.x_advance();

				--it;
			}
		}

		if(
			new_line
		)
		{
			lines.push_back(
				sge::font::bitmap::line{
					current_line,
					current_width
				}
			);

			width =
				std::max(
					width,
					current_width
				);

			if(
				flags
				&
				sge::font::flags::no_multi_line
			)
				break;

			current_line.clear();

			current_x = 0;

			last_space = _string.end();
		}
		else
		{
			if(
				std::isspace(
					*it,
					std::locale()
				)
			)
			{
				last_space_width = current_x;

				last_space = it;
			}
		}
	}

	sge::font::unit const left_pos(
		fcppt::variant::match(
			_text_parameters.align_h(),
			[](
				sge::font::align_h::left const &
			)
			{
				return
					0;
			},
			[
				width
			](
				sge::font::align_h::center const &_center
			)
			{
				return
					(
						_center.max_width().get()
						-
						width
					)
					/
					2;
			},
			[
				width
			](
				sge::font::align_h::right const &_right
			)
			{
				return
					_right.max_width().get()
					-
					width;
			}
		)
	);

	sge::font::unit const height(
		_line_height.get()
		*
		fcppt::cast::size<
			sge::font::unit
		>(
			fcppt::cast::to_signed(
				lines.size()
			)
		)
	);

	return
		sge::font::bitmap::rep(
			std::move(
				lines
			),
			sge::font::rect(
				sge::font::rect::vector(
					left_pos,
					0
				),
				sge::font::rect::dim(
					width,
					height
				)
			)
		);
}
