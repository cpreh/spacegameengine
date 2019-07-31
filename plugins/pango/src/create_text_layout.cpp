//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/utf8_string.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/align_h/extract_max_width.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/pango/create_text_layout.hpp>
#include <sge/pango/glib_deleter.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <sge/pango/convert/alignment.hpp>
#include <sge/pango/convert/to_unit.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


sge::pango::pango_layout_unique_ptr
sge::pango::create_text_layout(
	PangoLayout &_layout,
	sge::charconv::utf8_string const &_string,
	sge::font::text_parameters const &_text_parameters
)
{
	sge::pango::pango_layout_unique_ptr layout(
		::pango_layout_copy(
			&_layout
		)
	);

	::pango_layout_set_text(
		layout.get_pointer(),
		fcppt::cast::to_char_ptr<
			char const *
		>(
			_string.data()
		),
		fcppt::cast::size<
			int
		>(
			fcppt::cast::to_signed(
				_string.size()
			)
		)
	);

	::pango_layout_set_alignment(
		layout.get_pointer(),
		sge::pango::convert::alignment(
			_text_parameters.align_h()
		)
	);

	fcppt::optional::maybe_void(
		sge::font::align_h::extract_max_width(
			_text_parameters.align_h()
		),
		[
			&layout
		](
			sge::font::align_h::max_width const _max_width
		)
		{
			::pango_layout_set_width(
				layout.get_pointer(),
				sge::pango::convert::to_unit(
					_max_width.get()
				)
			);
		}
	);

	::pango_layout_set_wrap(
		layout.get_pointer(),
		(
			_text_parameters.flags()
			&
			sge::font::flags::no_word_wrap
		)
		?
			PANGO_WRAP_CHAR
		:
			PANGO_WRAP_WORD
	);

	::pango_layout_set_single_paragraph_mode(
		layout.get_pointer(),
		(
			_text_parameters.flags()
			&
			sge::font::flags::no_multi_line
		)
		?
			TRUE
		:
			FALSE
	);

	::pango_layout_set_ellipsize(
		layout.get_pointer(),
		PANGO_ELLIPSIZE_END
	);

	::pango_layout_set_indent(
		layout.get_pointer(),
		0
	);

	return
		layout;
}
