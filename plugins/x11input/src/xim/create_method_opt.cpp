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


#include <sge/input/exception.hpp>
#include <sge/x11input/xim/create_method.hpp>
#include <sge/x11input/xim/create_method_opt.hpp>
#include <sge/x11input/xim/get_supported_styles.hpp>
#include <sge/x11input/xim/method.hpp>
#include <sge/x11input/xim/method_unique_ptr.hpp>
#include <sge/x11input/xim/optional_method_unique_ptr.hpp>
#include <sge/x11input/xim/supported_styles_unique_ptr.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains_if.hpp>
#include <fcppt/bit/mask_c.hpp>
#include <fcppt/bit/test.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <boost/range/iterator_range_core.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::x11input::xim::optional_method_unique_ptr
sge::x11input::xim::create_method_opt(
	fcppt::log::object &_log,
	awl::backends::x11::display const &_display
)
try
{
	sge::x11input::xim::method_unique_ptr result{
		sge::x11input::xim::create_method(
			_log,
			_display
		)
	};

	sge::x11input::xim::supported_styles_unique_ptr const styles{
		sge::x11input::xim::get_supported_styles(
			*result
		)
	};

	if(
		fcppt::algorithm::contains_if(
			boost::make_iterator_range(
				styles->supported_styles,
				styles->supported_styles
				+
				styles->count_styles
			),
			[](
				XIMStyle const &_style
			)
			{
				return
					fcppt::bit::test(
						_style,
						fcppt::bit::mask_c<
							XIMStyle,
							XIMPreeditNothing
						>()
					)
					&&
					fcppt::bit::test(
						_style,
						fcppt::bit::mask_c<
							XIMStyle,
							XIMStatusNothing
						>()
					);
			}
		)
	)
		return
			sge::x11input::xim::optional_method_unique_ptr{
				std::move(
					result
				)
			};

	FCPPT_LOG_ERROR(
		_log,
		fcppt::log::out
			<<
			FCPPT_TEXT("The selected XIM IME does not support PreeditNothing | StatusNothing!")
	);

	return
		sge::x11input::xim::optional_method_unique_ptr{};
}
catch(
	sge::input::exception const &_error
)
{
	FCPPT_LOG_ERROR(
		_log,
		fcppt::log::out
			<<
			FCPPT_TEXT("Failed to open XIM: ")
			<<
			_error.string()
	);

	return
		sge::x11input::xim::optional_method_unique_ptr();
}
