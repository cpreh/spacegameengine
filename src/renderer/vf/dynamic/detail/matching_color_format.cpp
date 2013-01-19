/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/src/renderer/vf/dynamic/detail/matching_color_format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains.hpp>


sge::image::color::format
sge::renderer::vf::dynamic::detail::matching_color_format(
	sge::image::color::format const _format,
	sge::renderer::vf::dynamic::color_format_vector const &_formats
)
{
	if(
		fcppt::algorithm::contains(
			_formats,
			_format
		)
	)
		return _format;

	for(
		sge::renderer::vf::dynamic::color_format_vector::const_iterator format_it(
			_formats.begin()
		);
		format_it != _formats.end();
		++format_it
	)
	{
		sge::renderer::vf::dynamic::color_format_vector::value_type const value(
			*format_it
		);

		if(
			sge::image::color::format_stride(
				_format
			)
			==
			sge::image::color::format_stride(
				value
			)
		)
			return value;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Unsupported vertex color ")
		+ sge::image::color::format_to_string(
			_format
		)
	);
}


