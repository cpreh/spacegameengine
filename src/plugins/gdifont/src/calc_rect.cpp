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


#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/extract_max_width.hpp>
#include <sge/font/align_h/left_fwd.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/gdifont/calc_rect.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/draw_text.hpp>
#include <sge/gdifont/format.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/scoped_select.hpp>
#include <fcppt/const.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


sge::font::rect const
sge::gdifont::calc_rect(
	sge::gdifont::device_context const &_device_context,
	HFONT const _font,
	sge::font::string const &_string,
	sge::font::align_h::variant const &_align_h,
	sge::gdifont::format const _format
)
{
	sge::gdifont::scoped_select const select_font(
		_device_context,
		_font
	);

	LONG const max_unit(
		std::numeric_limits<
			LONG
		>::max()
	);

	RECT result =
	{
		0,
		0,
		fcppt::maybe(
			sge::font::align_h::extract_max_width(
				_align_h
			),
			fcppt::const_(
				max_unit
			),
			[](
				sge::font::align_h::max_width const _max_width
			)
			{
				return
					fcppt::cast::size<
						LONG
					>(
						_max_width.get()
					);
			}
		),
		max_unit
	};

	sge::gdifont::draw_text(
		_device_context,
		_string,
		result,
		_format.get()
		|
		DT_CALCRECT
	);

	FCPPT_ASSERT_ERROR(
		result.left == 0
		&&
		result.top == 0
	);

	// TODO: Do this in a functional style!

	class align_visitor
	{
		FCPPT_NONASSIGNABLE(
			align_visitor
		);
	public:
		explicit
		align_visitor(
			RECT &_result
		)
		:
			result_(
				_result
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
			result_.left = (_center.max_width().get() - result_.right) / 2;

			result_.right = (_center.max_width().get() + result_.right) / 2;
		}

		result_type
		operator()(
			sge::font::align_h::right const &_right
		) const
		{
			result_.left = _right.max_width().get() - result_.right;

			result_.right = _right.max_width().get();
		}
	private:
		RECT &result_;
	};

	fcppt::variant::apply_unary(
		align_visitor(
			result
		),
		_align_h
	);

	return
		sge::font::rect(
			sge::font::rect::vector(
				static_cast<
					sge::font::rect::value_type
				>(
					result.left
				),
				static_cast<
					sge::font::rect::value_type
				>(
					result.top
				)
			),
			sge::font::rect::dim(
				static_cast<
					sge::font::rect::value_type
				>(
					result.right - result.left
				),
				static_cast<
					sge::font::rect::value_type
				>(
					result.bottom - result.top
				)
			)
		);
}
