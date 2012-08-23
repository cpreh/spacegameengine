/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/font/optional_unit.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/view.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/src/font/bitmap/char_map.hpp>
#include <sge/src/font/bitmap/char_metric.hpp>
#include <sge/src/font/bitmap/char_metric_ref_vector.hpp>
#include <sge/src/font/bitmap/const_view.hpp>
#include <sge/src/font/bitmap/line.hpp>
#include <sge/src/font/bitmap/text.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <algorithm>
#include <locale>
#include <fcppt/config/external_end.hpp>


sge::font::bitmap::text::text(
	sge::font::bitmap::char_map const &_char_map,
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters,
	sge::font::unit const _line_height
)
:
	lines_(),
	rect_(
		sge::font::rect::null()
	),
	line_height_(
		_line_height
	)
{
	sge::font::unit current_x(
		0
	);

	sge::font::unit last_space_width(
		0
	);

	sge::font::flags_field const flags(
		_text_parameters.flags()
	);

	sge::font::optional_unit const max_width(
		_text_parameters.max_width()
	);

	sge::font::bitmap::char_metric_ref_vector current_line;

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

		sge::font::bitmap::char_map::const_iterator const char_it(
			_char_map.find(
				*it
			)
		);

		if(
			char_it == _char_map.end()
		)
			continue;

		sge::font::bitmap::char_metric const &metric(
			*char_it->second
		);

		if(
			(
				max_width
				&&
				*max_width
				<
				current_x + metric.x_advance()
			)
			||
			boost::next(
				it
			)
			==
			_string.end()
		)
		{
			if(
				current_line.empty()
			)
				break;

			sge::font::unit current_width(
				current_x
			);

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
					current_line.begin()
					+
					std::distance(
						last_space,
						it
					),
					current_line.end()
				);

				it = last_space;

				last_space = _string.end();

				current_width = last_space_width;
			}

			fcppt::container::ptr::push_back_unique_ptr(
				lines_,
				fcppt::make_unique_ptr<
					sge::font::bitmap::line
				>(
					current_line,
					current_width
				)
			);

			rect_.w(
				std::max(
					rect_.w(),
					current_width
				)
			);

			if(
				flags
				&
				sge::font::flags::no_multi_line
			)
				break;

			current_line.clear();

			current_x = 0;
		}

		current_line.push_back(
			fcppt::cref(
				metric
			)
		);

		current_x += metric.x_advance();
	}

	rect_.h(
		line_height_
		*
		static_cast<
			sge::font::unit
		>(
			lines_.size()
		)
	);
}

sge::font::bitmap::text::~text()
{
}

void
sge::font::bitmap::text::render(
	sge::font::view const &_view
)
{
	sge::font::unit top(
		0u
	);

	for(
		sge::font::bitmap::text::line_vector::const_iterator it(
			lines_.begin()
		);
		it != lines_.end();
		++it
	)
	{
		sge::font::bitmap::line const &line(
			*it
		);

		// TODO!
		sge::font::unit left(
			0u
		);

		sge::font::bitmap::char_metric_ref_vector const &metrics(
			line.char_metrics()
		);

		for(
			sge::font::bitmap::char_metric_ref_vector::const_iterator char_it(
				metrics.begin()
			);
			char_it != metrics.end();
			++char_it
		)
		{
			sge::font::bitmap::char_metric const &char_metric(
				*char_it
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
							static_cast<
								sge::image::size_type
							>(
								left
							),
							static_cast<
								sge::image::size_type
							>(
								top
							)
						),
						sge::image2d::view::size(
							source_view
						)
					)
				),
				sge::image::algorithm::may_overlap::no
			);

			left += char_metric.x_advance();
		}

		top += line_height_;
	}
}

sge::font::rect const
sge::font::bitmap::text::rect()
{
	return rect_;
}
