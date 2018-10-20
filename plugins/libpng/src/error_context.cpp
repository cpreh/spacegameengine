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


#include <sge/image2d/file_exception.hpp>
#include <sge/libpng/error_context.hpp>
#include <sge/libpng/png.hpp>
#include <sge/media/error_string.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/warning.hpp>


sge::libpng::error_context::error_context(
	fcppt::log::object &_log,
	sge::media::optional_name const &_name
)
:
	log_{
		_log
	},
	name_(
		_name
	)
{
}

sge::libpng::error_context::~error_context()
{
}

void
sge::libpng::error_context::handle_warning(
	png_structp const _read_ptr,
	png_const_charp const _data
)
{
	sge::libpng::error_context::get_instance(
		_read_ptr
	).handle_warning_impl(
		_data
	);
}

void
sge::libpng::error_context::handle_error(
	png_structp const _read_ptr,
	png_const_charp const _data
)
{
	sge::libpng::error_context::get_instance(
		_read_ptr
	).handle_error_impl(
		_data
	);
}

void
sge::libpng::error_context::handle_warning_impl(
	png_const_charp const _message
)
{
	FCPPT_LOG_WARNING(
		log_,
		fcppt::log::out <<
			sge::media::error_string(
				name_,
				fcppt::from_std_string(
					_message
				)
			)
	);
}

void
sge::libpng::error_context::handle_error_impl(
	png_const_charp const _message
)
{
	throw
		sge::image2d::file_exception(
			name_,
			fcppt::from_std_string(
				_message
			)
		);
}

sge::libpng::error_context &
sge::libpng::error_context::get_instance(
	png_structp const _read_ptr
)
{
	return
		*fcppt::cast::from_void_ptr<
			sge::libpng::error_context *
		>(
			::png_get_error_ptr(
				_read_ptr
			)
		);
}
