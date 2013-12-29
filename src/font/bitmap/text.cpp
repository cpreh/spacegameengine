/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/view.hpp>
#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/extract_max_width.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/optional_max_width.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
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
#include <sge/src/font/bitmap/char_metric_ref.hpp>
#include <sge/src/font/bitmap/char_metric_ref_vector.hpp>
#include <sge/src/font/bitmap/const_view.hpp>
#include <sge/src/font/bitmap/line.hpp>
#include <sge/src/font/bitmap/logger.hpp>
#include <sge/src/font/bitmap/text.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iterator>
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
	),
	align_h_(
		_text_parameters.align_h()
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

	sge::font::align_h::optional_max_width const max_width(
		sge::font::align_h::extract_max_width(
			align_h_
		)
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
		sge::font::bitmap::char_map::const_iterator const char_it(
			_char_map.find(
				*it
			)
		);

		if(
			char_it == _char_map.end()
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
			*char_it->second
		);

		current_line.push_back(
			sge::font::bitmap::char_metric_ref(
				metric
			)
		);

		current_x += metric.x_advance();

		bool const space_exceeded(
			max_width
			&&
			current_x
			>
			max_width->get()
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

	rect_.h(
		line_height_
		*
		static_cast<
			sge::font::unit
		>(
			lines_.size()
		)
	);

	class align_visitor
	{
		FCPPT_NONASSIGNABLE(
			align_visitor
		);
	public:
		explicit
		align_visitor(
			sge::font::rect &_rect
		)
		:
			rect_(
				_rect
			)
		{
		}

		typedef
		void
		result_type;

		result_type
		operator()(
			sge::font::align_h::left const &
		) const
		{
		}

		result_type
		operator()(
			sge::font::align_h::center const &_center
		) const
		{
			rect_.left(
				(_center.max_width().get() - rect_.w()) / 2
			);
		}

		result_type
		operator()(
			sge::font::align_h::right const &_right
		) const
		{
			rect_.left(
				_right.max_width().get() - rect_.w()
			);
		}
	private:
		sge::font::rect &rect_;
	};

	fcppt::variant::apply_unary(
		align_visitor(
			rect_
		),
		align_h_
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
	sge::image2d::algorithm::fill(
		sge::image2d::view::sub(
			_view,
			sge::image2d::rect(
				sge::image2d::rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::image2d::rect::dim
				>(
					rect_.size()
				)
			)
		),
		sge::image::color::any::clear(
			sge::image2d::view::format(
				_view
			)
		)
	);

	sge::font::unit top(
		0u
	);

	for(
		sge::font::bitmap::line const &line
		:
		lines_
	)
	{
		class align_visitor
		{
			FCPPT_NONASSIGNABLE(
				align_visitor
			);
		public:
			align_visitor(
				sge::font::rect const &_rect,
				sge::font::bitmap::line const &_line
			)
			:
				rect_(
					_rect
				),
				line_(
					_line
				)
			{
			}

			typedef
			sge::font::unit
			result_type;

			result_type
			operator()(
				sge::font::align_h::left const &
			) const
			{
				return
					0;
			}

			result_type
			operator()(
				sge::font::align_h::center const &
			) const
			{
				return
					(rect_.w() - line_.width()) / 2;
			}

			result_type
			operator()(
				sge::font::align_h::right const &
			) const
			{
				return
					rect_.w() - line_.width();
			}
		private:
			sge::font::rect const rect_;

			sge::font::bitmap::line const &line_;
		};

		sge::font::unit left(
			fcppt::variant::apply_unary(
				align_visitor(
					rect_,
					line
				),
				align_h_
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
