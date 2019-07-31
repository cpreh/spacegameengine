//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BASIC_BUFFER_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BUFFER_PARAMETERS_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/basic_buffer_parameters_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class basic_buffer_parameters
{
public:
	basic_buffer_parameters(
		fcppt::log::object &,
		sge::opengl::texture::binding const &,
		sge::opengl::context::object &,
		sge::renderer::texture::mipmap::level,
		sge::opengl::texture::type,
		sge::opengl::texture::buffer_type,
		sge::opengl::texture::id,
		sge::renderer::resource_flags_field const &,
		sge::opengl::color_order,
		sge::opengl::color_base_type,
		sge::opengl::internal_color_format,
		sge::opengl::texture::is_render_target
	);

	fcppt::log::object &
	log() const;

	sge::opengl::texture::binding const &
	binding() const;

	sge::opengl::context::object &
	context() const;

	sge::renderer::texture::mipmap::level
	level() const;

	sge::opengl::texture::type
	type() const;

	sge::opengl::texture::buffer_type
	buffer_type() const;

	sge::opengl::texture::id
	id() const;

	sge::renderer::resource_flags_field const &
	resource_flags() const;

	sge::opengl::color_order
	color_order() const;

	sge::opengl::color_base_type
	color_base_type() const;

	sge::opengl::internal_color_format
	internal_color_format() const;

	sge::opengl::texture::is_render_target
	is_render_target() const;
private:
	fcppt::reference<
		fcppt::log::object
	> log_;

	fcppt::reference<
		sge::opengl::texture::binding const
	> binding_;

	fcppt::reference<
		sge::opengl::context::object
	> context_;

	sge::renderer::texture::mipmap::level level_;

	sge::opengl::texture::type type_;

	sge::opengl::texture::buffer_type buffer_type_;

	sge::opengl::texture::id id_;

	sge::renderer::resource_flags_field resource_flags_;

	sge::opengl::color_order color_order_;

	sge::opengl::color_base_type color_base_type_;

	sge::opengl::internal_color_format internal_color_format_;

	sge::opengl::texture::is_render_target is_render_target_;
};

}
}
}

#endif
