//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/create_depth_stencil_surface.hpp>
#include <sge/opengl/fbo/depth_stencil_surface.hpp>
#include <sge/opengl/fbo/get_config.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::depth_stencil_buffer::surface_unique_ptr
sge::opengl::fbo::create_depth_stencil_surface(
	sge::opengl::context::object &_context,
	sge::renderer::depth_stencil_buffer::surface_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::depth_stencil_buffer::surface
		>(
			fcppt::make_unique_ptr<
				sge::opengl::fbo::depth_stencil_surface
			>(
				sge::opengl::fbo::get_config(
					sge::opengl::context::use<
						sge::opengl::fbo::context
					>(
						_context,
						_context.info()
					)
				),
				_parameters
			)
		);
}
