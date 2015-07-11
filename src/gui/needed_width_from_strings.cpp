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


#include <sge/font/dim.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/object.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/gui/needed_width.hpp>
#include <sge/gui/needed_width_from_strings.hpp>
#include <sge/gui/string_container.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::gui::needed_width const
sge::gui::needed_width_from_strings(
	sge::font::object &_font,
	sge::gui::string_container const &_strings
)
{
	return
		fcppt::algorithm::fold(
			_strings,
			sge::gui::needed_width(
				0
			),
			[
				&_font
			](
				sge::font::string const &_text,
				sge::gui::needed_width const _prev_width
			)
			{
				return
					sge::gui::needed_width(
						std::max(
							_prev_width.get(),
							_font.create_text(
								_text,
								sge::font::text_parameters(
									sge::font::align_h::variant{
										sge::font::align_h::left()
									}
								).flags(
									sge::font::flags_field{
										sge::font::flags::no_multi_line
									}
								)
							)->logical_size().w()
						)
					);
			}
		);
}
