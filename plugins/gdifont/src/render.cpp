//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/dim.hpp>
#include <sge/font/string.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/draw_text.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/render.hpp>



void
sge::gdifont::render(
	sge::gdifont::device_context const &_device_context,
	sge::font::string const &_string,
	sge::font::dim const &_size,
	sge::gdifont::format const _format
)
{
	RECT rect =
	{
		0,
		0,
		_size.w(),
		_size.h()
	};

	sge::gdifont::draw_text(
		_device_context,
		_string,
		rect,
		_format.get()
	);
}
