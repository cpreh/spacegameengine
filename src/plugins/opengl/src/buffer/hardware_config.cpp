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


#include <sge/opengl/buffer/hardware_config.hpp>
#include <sge/opengl/buffer/is_native.hpp>


sge::opengl::buffer::hardware_config::hardware_config(
	sge::opengl::buffer::is_native const _is_native,
	gl_gen_buffers _gen_buffers,
	gl_delete_buffers _delete_buffers,
	gl_bind_buffer _bind_buffer,
	gl_map_buffer _map_buffer,
	gl_unmap_buffer _unmap_buffer,
	gl_buffer_data _buffer_data,
	gl_buffer_sub_data _buffer_sub_data,
	optional_gl_map_buffer_range const _map_buffer_range
)
:
	is_native_(
		_is_native
	),
	gen_buffers_(
		_gen_buffers
	),
	delete_buffers_(
		_delete_buffers
	),
	bind_buffer_(
		_bind_buffer
	),
	map_buffer_(
		_map_buffer
	),
	unmap_buffer_(
		_unmap_buffer
	),
	buffer_data_(
		_buffer_data
	),
	buffer_sub_data_(
		_buffer_sub_data
	),
	map_buffer_range_(
		_map_buffer_range
	)
{
}

sge::opengl::buffer::is_native const
sge::opengl::buffer::hardware_config::is_native() const
{
	return
		is_native_;
}

sge::opengl::buffer::hardware_config::gl_gen_buffers
sge::opengl::buffer::hardware_config::gen_buffers() const
{
	return
		gen_buffers_;
}

sge::opengl::buffer::hardware_config::gl_delete_buffers
sge::opengl::buffer::hardware_config::delete_buffers() const
{
	return
		delete_buffers_;
}

sge::opengl::buffer::hardware_config::gl_bind_buffer
sge::opengl::buffer::hardware_config::bind_buffer() const
{
	return
		bind_buffer_;
}

sge::opengl::buffer::hardware_config::gl_map_buffer
sge::opengl::buffer::hardware_config::map_buffer() const
{
	return
		map_buffer_;
}

sge::opengl::buffer::hardware_config::gl_unmap_buffer
sge::opengl::buffer::hardware_config::unmap_buffer() const
{
	return
		unmap_buffer_;
}

sge::opengl::buffer::hardware_config::gl_buffer_data
sge::opengl::buffer::hardware_config::buffer_data() const
{
	return
		buffer_data_;
}

sge::opengl::buffer::hardware_config::gl_buffer_sub_data
sge::opengl::buffer::hardware_config::buffer_sub_data() const
{
	return
		buffer_sub_data_;
}

sge::opengl::buffer::hardware_config::optional_gl_map_buffer_range
sge::opengl::buffer::hardware_config::map_buffer_range() const
{
	return
		map_buffer_range_;
}
