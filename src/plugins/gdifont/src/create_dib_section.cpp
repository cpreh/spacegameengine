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


#include <sge/font/exception.hpp>
#include <sge/gdifont/create_dib_section.hpp>
#include <sge/gdifont/delete_object_deleter.hpp>
#include <sge/gdifont/device_context.hpp>
#include <sge/gdifont/hbitmap_unique_ptr.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/image2d/dim.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>


sge::gdifont::hbitmap_unique_ptr
sge::gdifont::create_dib_section(
	sge::gdifont::device_context const &_device_context,
	sge::image2d::dim const &_dim,
	VOID *&_bits_result
)
{
	BITMAPINFO info;

	ZeroMemory(
		&info,
		sizeof(
			BITMAPINFO
		)
	);

	BITMAPINFOHEADER &header(
		info.bmiHeader
	);

	header.biSize =
		fcppt::cast::size<
			DWORD
		>(
			sizeof(BITMAPINFOHEADER)
		);

	header.biWidth
		=
		fcppt::cast::size<
			LONG
		>(
			fcppt::cast::to_signed(
				_dim.w()
			)
		);

	// negative values indicate topdown bitmaps
	header.biHeight
		=
		-fcppt::cast::size<
			LONG
		>(
			fcppt::cast::to_signed(
				_dim.h()
			)
		);

	header.biPlanes = 1;

	// TODO: Support more formats!
	header.biBitCount = 8;

	header.biCompression = BI_RGB;

	header.biSizeImage = 0;

	header.biXPelsPerMeter = 0; // TODO!

	header.biYPelsPerMeter = 0; // TODO!

	header.biClrUsed = 0;

	header.biClrImportant = 0;

	HBITMAP const result(
		::CreateDIBSection(
			_device_context.get(),
			&info,
			DIB_RGB_COLORS,
			&_bits_result,
			nullptr,
			0u
		)
	);

	if(
		result
		==
		nullptr
	)
		throw sge::font::exception(
			FCPPT_TEXT("CreateDIBSection failed!")
		);

	return
		sge::gdifont::hbitmap_unique_ptr(
			result
		);
}
