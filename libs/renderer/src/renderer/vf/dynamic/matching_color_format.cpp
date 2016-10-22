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


#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/matching_color_format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::image::color::format
sge::renderer::vf::dynamic::matching_color_format(
	sge::image::color::format const _format,
	sge::renderer::vf::dynamic::color_format_vector const &_formats
)
{
	return
		fcppt::algorithm::contains(
			_formats,
			_format
		)
		?
			_format
		:
			*fcppt::optional::to_exception(
				fcppt::algorithm::find_if_opt(
					_formats,
					[
						_format
					](
						sge::renderer::vf::dynamic::color_format_vector::value_type const &_value
					)
					{
						return
							sge::image::color::format_stride(
								_format
							)
							==
							sge::image::color::format_stride(
								_value
							);
					}
				),
				[
					_format
				]{
					return
						sge::renderer::exception{
							FCPPT_TEXT("Unsupported vertex color ")
							+
							sge::image::color::format_to_string(
								_format
							)
						};
				}
			)
		;
}
