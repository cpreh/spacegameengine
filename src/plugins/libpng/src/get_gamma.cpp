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


#include <sge/libpng/expected_gamma.hpp>
#include <sge/libpng/gamma.hpp>
#include <sge/libpng/get_gamma.hpp>
#include <sge/libpng/info.hpp>
#include <sge/libpng/read_ptr.hpp>


sge::libpng::gamma const
sge::libpng::get_gamma(
	sge::libpng::read_ptr const &_read_ptr,
	sge::libpng::info const &_info
)
{
	sge::libpng::gamma::value_type gamma_raw;

	return
		::png_get_gAMA(
			_read_ptr.ptr(),
			_info.get(),
			&gamma_raw
		)
		== 0
		?
			sge::libpng::expected_gamma()
		:
			sge::libpng::gamma(
				gamma_raw
			)
		;
}
