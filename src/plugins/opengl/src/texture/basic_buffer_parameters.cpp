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


#include <sge/image/color/format.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/basic_buffer_parameters.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>


sge::opengl::texture::basic_buffer_parameters::basic_buffer_parameters(
	sge::opengl::texture::binding const &_binding,
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context,
	sge::renderer::texture::mipmap::level const _level,
	sge::opengl::texture::type const _type,
	sge::opengl::texture::buffer_type const _buffer_type,
	sge::opengl::texture::id const _id,
	sge::renderer::resource_flags_field const &_resource_flags,
	sge::opengl::color_format const _color_format,
	sge::opengl::color_format_type const _color_format_type,
	sge::opengl::internal_color_format const _internal_color_format,
	sge::opengl::texture::is_render_target const _is_render_target
)
:
	binding_(
		_binding
	),
	system_context_(
		_system_context
	),
	device_context_(
		_device_context
	),
	level_(
		_level
	),
	type_(
		_type
	),
	buffer_type_(
		_buffer_type
	),
	id_(
		_id
	),
	resource_flags_(
		_resource_flags
	),
	color_format_(
		_color_format
	),
	color_format_type_(
		_color_format_type
	),
	internal_color_format_(
		_internal_color_format
	),
	is_render_target_(
		_is_render_target
	)
{
}

sge::opengl::texture::binding const &
sge::opengl::texture::basic_buffer_parameters::binding() const
{
	return
		binding_;
}

sge::opengl::context::system::object &
sge::opengl::texture::basic_buffer_parameters::system_context() const
{
	return
		system_context_;
}

sge::opengl::context::device::object &
sge::opengl::texture::basic_buffer_parameters::device_context() const
{
	return
		device_context_;
}

sge::renderer::texture::mipmap::level const
sge::opengl::texture::basic_buffer_parameters::level() const
{
	return
		level_;
}

sge::opengl::texture::type const
sge::opengl::texture::basic_buffer_parameters::type() const
{
	return
		type_;
}

sge::opengl::texture::buffer_type const
sge::opengl::texture::basic_buffer_parameters::buffer_type() const
{
	return
		buffer_type_;
}

sge::opengl::texture::id const
sge::opengl::texture::basic_buffer_parameters::id() const
{
	return
		id_;
}

sge::renderer::resource_flags_field const &
sge::opengl::texture::basic_buffer_parameters::resource_flags() const
{
	return
		resource_flags_;
}

sge::opengl::color_format const
sge::opengl::texture::basic_buffer_parameters::color_format() const
{
	return
		color_format_;
}

sge::opengl::color_format_type const
sge::opengl::texture::basic_buffer_parameters::color_format_type() const
{
	return
		color_format_type_;
}

sge::opengl::internal_color_format const
sge::opengl::texture::basic_buffer_parameters::internal_color_format() const
{
	return
		internal_color_format_;
}

sge::opengl::texture::is_render_target const
sge::opengl::texture::basic_buffer_parameters::is_render_target() const
{
	return
		is_render_target_;
}
