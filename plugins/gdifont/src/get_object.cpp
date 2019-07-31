//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/exception.hpp>
#include <sge/gdifont/get_object.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


void
sge::gdifont::get_object(
	HGDIOBJ const _object,
	std::size_t const _size,
	void *const _result
)
{
	if(
		GetObject(
			_object,
			static_cast<
				int
			>(
				_size
			),
			_result
		)
		==
		0
	)
		throw sge::font::exception(
			FCPPT_TEXT("GetObject failed")
		);
}
