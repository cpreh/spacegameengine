//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>


sge::opengl::texture::buffer_base::buffer_base(
	sge::opengl::texture::buffer_type const _buffer_type,
	sge::opengl::texture::id const _id,
	sge::renderer::texture::mipmap::level const _level,
	sge::opengl::texture::is_render_target const _is_render_target
)
:
	buffer_type_(
		_buffer_type
	),
	id_(
		_id
	),
	level_(
		_level
	),
	is_render_target_(
		_is_render_target
	)
{
}

sge::opengl::texture::buffer_base::~buffer_base()
= default;

sge::opengl::texture::buffer_type
sge::opengl::texture::buffer_base::buffer_type() const
{
	return
		buffer_type_;
}

sge::opengl::texture::id
sge::opengl::texture::buffer_base::id() const
{
	return
		id_;
}

sge::renderer::texture::mipmap::level
sge::opengl::texture::buffer_base::level() const
{
	return
		level_;
}

sge::opengl::texture::is_render_target
sge::opengl::texture::buffer_base::is_render_target() const
{
	return
		is_render_target_;
}
