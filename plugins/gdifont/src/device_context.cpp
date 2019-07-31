//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/exception.hpp>
#include <sge/gdifont/device_context.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>


sge::gdifont::device_context::device_context()
:
	hdc_{
		::CreateCompatibleDC(
			nullptr
		)
	}
{
	if(
		hdc_
		==
		nullptr
	)
		throw
			sge::font::exception{
				FCPPT_TEXT("CreateCompatibleDC failed!")
			};
}

sge::gdifont::device_context::~device_context()
{
	FCPPT_ASSERT_ERROR(
		::DeleteDC(
			hdc_
		)
		!= 0
	);
}

HDC
sge::gdifont::device_context::get() const
{
	return
		hdc_;
}
