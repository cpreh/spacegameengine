//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/exception.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/unit.hpp>
#include <sge/pango/font_description.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <glib.h>
#include <pango/pango-font.h>
#include <fcppt/config/external_end.hpp>


sge::pango::font_description::font_description()
:
	impl_(
		::pango_font_description_new()
	)
{
}

sge::pango::font_description::~font_description()
{
	::pango_font_description_free(
		impl_
	);
}

void
sge::pango::font_description::ttf_size(
	sge::font::ttf_size const _ttf_size
)
{
	::pango_font_description_set_size(
		impl_,
		static_cast<
			gint
		>(
			_ttf_size
		)
	);
}

void
sge::pango::font_description::family(
	fcppt::string const &_family
)
{
	::pango_font_description_set_family(
		impl_,
		fcppt::optional::to_exception(
			fcppt::to_std_string(
				_family
			),
			[
				&_family
			]{
				return
					sge::font::exception{
						FCPPT_TEXT("Failed to convert font family: ")
						+
						_family
					};
			}
		).c_str()
	);
}

void
sge::pango::font_description::weight(
	sge::font::weight::unit const _weight
)
{
	::pango_font_description_set_weight(
		impl_,
		static_cast<
			PangoWeight
		>(
			_weight
		)
	);
}

void
sge::pango::font_description::italic()
{
	::pango_font_description_set_style(
		impl_,
		PANGO_STYLE_ITALIC
	);
}

PangoFontDescription *
sge::pango::font_description::get()
{
	return
		impl_;
}
