/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_FBO_DEPTH_STENCIL_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_FBO_DEPTH_STENCIL_SURFACE_HPP_INCLUDED

#include <sge/image/ds/format.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/context_fwd.hpp>
#include <sge/opengl/fbo/depth_stencil_surface_fwd.hpp>
#include <sge/opengl/fbo/render_buffer.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/depth_stencil_buffer/surface.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class depth_stencil_surface
:
	public sge::renderer::depth_stencil_buffer::surface
{
	FCPPT_NONCOPYABLE(
		depth_stencil_surface
	);
public:
	depth_stencil_surface(
		sge::opengl::fbo::context const &,
		sge::renderer::depth_stencil_buffer::surface_parameters const &
	);

	~depth_stencil_surface();

	sge::opengl::fbo::render_buffer const &
	render_buffer() const;
private:
	dim const
	size() const;

	sge::image::ds::format
	format() const;

	sge::opengl::fbo::render_buffer const render_buffer_;

	dim const dim_;

	sge::image::ds::format const format_;
};

}
}
}

#endif
