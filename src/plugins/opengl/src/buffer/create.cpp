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


#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/base_unique_ptr.hpp>
#include <sge/opengl/buffer/create.hpp>
#include <sge/opengl/buffer/hardware.hpp>
#include <sge/opengl/buffer/hw_supported.hpp>
#include <sge/opengl/buffer/software.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::opengl::buffer::base_unique_ptr
sge::opengl::buffer::create(
	sge::opengl::buffer::hw_supported const _hw_supported
)
{
	return
		_hw_supported.get()
		?
			fcppt::unique_ptr_to_base<
				sge::opengl::buffer::base
			>(
				fcppt::make_unique_ptr_fcppt<
					sge::opengl::buffer::hardware
				>()
			)
		:
			fcppt::unique_ptr_to_base<
				sge::opengl::buffer::base
			>(
				fcppt::make_unique_ptr_fcppt<
					sge::opengl::buffer::software
				>()
			)
		;
}
