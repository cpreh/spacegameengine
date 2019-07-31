//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/wininput/cursor/pixmap.hpp>
#include <awl/backends/windows/module_handle.hpp>
#include <awl/backends/windows/system_metrics.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>


sge::wininput::cursor::pixmap::pixmap()
:
	cursor_(
		[]{
			int const
				cursor_width(
					awl::backends::windows::system_metrics(
						SM_CXCURSOR
					)
				),
				cursor_height(
					awl::backends::windows::system_metrics(
						SM_CYCURSOR
					)
				);

			typedef
			std::vector<
				BYTE
			>
			byte_vector;

			static_assert(
				std::is_unsigned<
					BYTE
				>::value,
				"BYTE should be unsigned"
			);

			byte_vector::size_type const size(
				FCPPT_ASSERT_OPTIONAL_ERROR(
					fcppt::math::ceil_div(
						fcppt::cast::size<
							byte_vector::size_type
						>(
							fcppt::cast::to_unsigned(
								cursor_width
								*
								cursor_height
							)
						),
						fcppt::cast::size<
							byte_vector::size_type
						>(
							std::numeric_limits<
								BYTE
							>::digits
						)
					)
				)
			);

			byte_vector const
				and_values(
					size,
					std::numeric_limits<
						BYTE
					>::max()
				),
				xor_values(
					size,
					fcppt::literal<
						BYTE
					>(
						0u
					)
				);

			return
				::CreateCursor(
					awl::backends::windows::module_handle(),
					0,
					0,
					cursor_width,
					cursor_height,
					and_values.data(),
					xor_values.data()
				);
		}()
	)
{

	if(
		cursor_
		==
		NULL
	)
		throw
			sge::input::exception(
				FCPPT_TEXT("CreateCursor() failed!")
			);
}

sge::wininput::cursor::pixmap::~pixmap()
{
	::DestroyCursor(
		cursor_
	);
}

HCURSOR
sge::wininput::cursor::pixmap::get() const
{
	return
		cursor_;
}
