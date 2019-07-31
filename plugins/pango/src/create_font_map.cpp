//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/dpi.hpp>
#include <sge/font/parameters.hpp>
#include <sge/pango/create_font_map.hpp>
#include <sge/pango/glib_deleter.hpp>
#include <sge/pango/pango_font_map_unique_ptr.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pangoft2.h>
#include <fcppt/config/external_end.hpp>


sge::pango::pango_font_map_unique_ptr
sge::pango::create_font_map(
	sge::font::parameters const &_parameters
)
{
	sge::pango::pango_font_map_unique_ptr result(
		::pango_ft2_font_map_new()
	);

	fcppt::optional::maybe_void(
		_parameters.dpi(),
		[
			&result
		](
			sge::font::dpi const _dpi
		)
		{
			::pango_ft2_font_map_set_resolution(
				reinterpret_cast<
					PangoFT2FontMap *
				>(
					result.get_pointer()
				),
				_dpi.w(),
				_dpi.h()
			);
		}
	);

	return
		result;
}
