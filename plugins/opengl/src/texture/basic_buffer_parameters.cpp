//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/texture/basic_buffer_parameters.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/const_binding_ref.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/object_reference.hpp>


sge::opengl::texture::basic_buffer_parameters::basic_buffer_parameters(
	fcppt::log::object_reference const _log,
	sge::opengl::texture::const_binding_ref const _binding,
	sge::opengl::context::object_ref const _context,
	sge::renderer::texture::mipmap::level const _level,
	sge::opengl::texture::type const _type,
	sge::opengl::texture::buffer_type const _buffer_type,
	sge::opengl::texture::id const _id,
	sge::renderer::resource_flags_field const &_resource_flags,
	sge::opengl::color_order const _color_order,
	sge::opengl::color_base_type const _color_base_type,
	sge::opengl::internal_color_format const _internal_color_format,
	sge::opengl::texture::is_render_target const _is_render_target
)
:
	log_{
		_log
	},
	binding_(
		_binding
	),
	context_(
		_context
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
	color_order_(
		_color_order
	),
	color_base_type_(
		_color_base_type
	),
	internal_color_format_(
		_internal_color_format
	),
	is_render_target_(
		_is_render_target
	)
{
}

fcppt::log::object &
sge::opengl::texture::basic_buffer_parameters::log() const
{
	return
		log_.get();
}

sge::opengl::texture::binding const &
sge::opengl::texture::basic_buffer_parameters::binding() const
{
	return
		binding_.get();
}

sge::opengl::context::object &
sge::opengl::texture::basic_buffer_parameters::context() const
{
	return
		context_.get();
}

sge::renderer::texture::mipmap::level
sge::opengl::texture::basic_buffer_parameters::level() const
{
	return
		level_;
}

sge::opengl::texture::type
sge::opengl::texture::basic_buffer_parameters::type() const
{
	return
		type_;
}

sge::opengl::texture::buffer_type
sge::opengl::texture::basic_buffer_parameters::buffer_type() const
{
	return
		buffer_type_;
}

sge::opengl::texture::id
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

sge::opengl::color_order
sge::opengl::texture::basic_buffer_parameters::color_order() const
{
	return
		color_order_;
}

sge::opengl::color_base_type
sge::opengl::texture::basic_buffer_parameters::color_base_type() const
{
	return
		color_base_type_;
}

sge::opengl::internal_color_format
sge::opengl::texture::basic_buffer_parameters::internal_color_format() const
{
	return
		internal_color_format_;
}

sge::opengl::texture::is_render_target
sge::opengl::texture::basic_buffer_parameters::is_render_target() const
{
	return
		is_render_target_;
}
