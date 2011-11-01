/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/file_exception.hpp>
#include <sge/libpng/context_base.hpp>
#include <sge/libpng/logger.hpp>
#include <sge/libpng/png.hpp>
#include <sge/log/global.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>


sge::libpng::context_base::context_base(
	sge::image::optional_path const &_path
)
:
	path_(
		_path
	)
{
}

sge::libpng::context_base::~context_base()
{
}

void
sge::libpng::context_base::handle_warning(
	png_structp read_ptr,
	png_const_charp data
)
{
	static_cast<context_base *>(png_get_io_ptr(read_ptr))->handle_warning_impl(
		data);
}

void
sge::libpng::context_base::handle_warning_impl(
	png_const_charp const message
)
{
	fcppt::string const prelude =
		path_
		?
			FCPPT_TEXT("file: ")+
			fcppt::filesystem::path_to_string(
				*path_)
		:
			FCPPT_TEXT("stream");

	FCPPT_LOG_WARNING(
		logger(),
		fcppt::log::_
			<< FCPPT_TEXT("libpng: ")
			<< prelude
			<< FCPPT_TEXT(": ")
			<< fcppt::from_std_string(message)
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
	if(path_)
		throw
			image::file_exception(
				path_,
				fcppt::from_std_string(
					message
				)
			);
}
