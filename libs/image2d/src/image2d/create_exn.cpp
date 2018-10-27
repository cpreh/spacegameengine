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


#include <sge/image/color/format_to_string.hpp>
#include <sge/image2d/create_exn.hpp>
#include <sge/image2d/exception.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/media/extension_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::image2d::file_unique_ptr
sge::image2d::create_exn(
	sge::image2d::system &_system,
	sge::image2d::view::const_object const &_view,
	sge::media::extension const &_extension
)
{
	return
		fcppt::optional::to_exception(
			_system.create(
				_view,
				_extension
			),
			[
				&_view,
				&_extension
			]{
				return
					sge::image2d::exception(
						FCPPT_TEXT("No image2d system can create an image with extension ")
						+
						_extension.get()
						+
						FCPPT_TEXT(" and type ")
						+
						sge::image::color::format_to_string(
							sge::image2d::view::format(
								_view
							)
						)
						+
						FCPPT_TEXT('!')
					);
			}
		);
}
