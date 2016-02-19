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


#ifndef SGE_OPENGL_BUFFER_MAKE_HARDWARE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_MAKE_HARDWARE_HPP_INCLUDED

#include <sge/opengl/buffer/base_unique_ptr.hpp>
#include <sge/opengl/buffer/hardware.hpp>
#include <sge/opengl/buffer/hardware_config_fwd.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

template<
	typename... Args
>
std::array<
	sge::opengl::buffer::base_unique_ptr,
	sizeof...(Args)
>
make_hardware(
	sge::opengl::buffer::hardware_config const &_config,
	Args const ..._args
)
{
	return
		std::array<
			sge::opengl::buffer::base_unique_ptr,
			sizeof...(Args)
		>{{
			fcppt::unique_ptr_to_base<
				sge::opengl::buffer::base
			>(
				fcppt::make_unique_ptr<
					sge::opengl::buffer::hardware
				>(
					fcppt::strong_typedef_construct_cast<
						sge::opengl::buffer::type,
						fcppt::cast::static_cast_fun
					>(
						_args
					),
					_config
				)
			)...
		}};
}

}
}
}

#endif
