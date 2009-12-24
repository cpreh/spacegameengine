/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "../context_base.hpp"
#include <sge/image/file_exception.hpp>
#include <sge/log/global.hpp>
#include <fcppt/iconv.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/headers.hpp>

sge::libpng::context_base::context_base(
	fcppt::filesystem::path const &_path
)
:
	path_(
		_path
	)
{
}

void sge::libpng::context_base::handle_warning(
	png_structp read_ptr,
	png_const_charp data)
{
	static_cast<context_base *>(png_get_io_ptr(read_ptr))->handle_warning_impl(
		data);
}

void sge::libpng::context_base::handle_warning_impl(
	png_const_charp const message)
{
	FCPPT_LOG_WARNING(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("libpng: file: ")
			<< path_.string()
			<< FCPPT_TEXT(": ")
			<< fcppt::iconv(message)
	);
}

void sge::libpng::context_base::handle_error(
	png_structp read_ptr,
	png_const_charp data)
{
	static_cast<context_base *>(png_get_io_ptr(read_ptr))->handle_error_impl(
		data);
}

void sge::libpng::context_base::handle_error_impl(
	png_const_charp const message)
{
	throw
		image::file_exception(
			path_,
			fcppt::iconv(
				message
			)
		);
}

sge::libpng::context_base::~context_base() {}
