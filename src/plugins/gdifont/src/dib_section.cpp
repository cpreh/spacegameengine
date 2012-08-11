/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/gdifont/create_dib_section.hpp>
#include <sge/gdifont/delete_object_deleter.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/dib_section.hpp>
#include <sge/gdifont/get_bitmap.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


sge::gdifont::dib_section::dib_section(
	sge::gdifont::device_context const &_device_context,
	sge::image2d::dim const &_size
)
:
	data_(
		fcppt::null_ptr()
	),
	hbitmap_(
		sge::gdifont::create_dib_section(
			_device_context,
			_size,
			data_
		)
	),
	bitmap_(
		sge::gdifont::get_bitmap(
			hbitmap_.get()
		)
	)
{
}

sge::gdifont::dib_section::~dib_section()
{
}

sge::image2d::view::const_object const
sge::gdifont::dib_section::view() const
{
	return
		sge::image2d::view::make_const(
			static_cast<
				sge::image::const_raw_pointer
			>(
				data_
			),
			sge::image2d::dim(
				static_cast<
					sge::image2d::dim::value_type
				>(
					bitmap_.bmWidth
				),
				static_cast<
					sge::image2d::dim::value_type
				>(
					bitmap_.bmHeight
				)
			),
			sge::image::color::format::a8,
			sge::image2d::view::optional_pitch(
				sge::image2d::pitch(
					bitmap_.bmWidthBytes - bitmap_.bmWidth
				)
			)
		);
}

HBITMAP
sge::gdifont::dib_section::handle()
{
	return hbitmap_.get();
}
