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


#ifndef SGE_OPENGL_TEXTURE_BASIC_BUFFER_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BUFFER_PARAMETERS_HPP_INCLUDED

#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/basic_buffer_parameters_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class basic_buffer_parameters
{
	FCPPT_NONASSIGNABLE(
		basic_buffer_parameters
	);
public:
	basic_buffer_parameters(
		sge::opengl::texture::binding const &,
		sge::opengl::context::system::object &,
		sge::opengl::context::device::object &,
		sge::renderer::texture::mipmap::level,
		sge::opengl::texture::type,
		sge::opengl::texture::buffer_type,
		sge::opengl::texture::id,
		sge::renderer::resource_flags_field const &,
		sge::opengl::color_format,
		sge::opengl::color_format_type,
		sge::opengl::internal_color_format,
		sge::opengl::texture::is_render_target
	);

	sge::opengl::texture::binding const &
	binding() const;

	sge::opengl::context::system::object &
	system_context() const;

	sge::opengl::context::device::object &
	device_context() const;

	sge::renderer::texture::mipmap::level const
	level() const;

	sge::opengl::texture::type const
	type() const;

	sge::opengl::texture::buffer_type const
	buffer_type() const;

	sge::opengl::texture::id const
	id() const;

	sge::renderer::resource_flags_field const &
	resource_flags() const;

	sge::opengl::color_format const
	color_format() const;

	sge::opengl::color_format_type const
	color_format_type() const;

	sge::opengl::internal_color_format const
	internal_color_format() const;

	sge::opengl::texture::is_render_target const
	is_render_target() const;
private:
	sge::opengl::texture::binding const &binding_;

	sge::opengl::context::system::object &system_context_;

	sge::opengl::context::device::object &device_context_;

	sge::renderer::texture::mipmap::level const level_;

	sge::opengl::texture::type const type_;

	sge::opengl::texture::buffer_type const buffer_type_;

	sge::opengl::texture::id const id_;

	sge::renderer::resource_flags_field const resource_flags_;

	sge::opengl::color_format const color_format_;

	sge::opengl::color_format_type const color_format_type_;

	sge::opengl::internal_color_format const internal_color_format_;

	sge::opengl::texture::is_render_target const is_render_target_;
};

}
}
}

#endif
