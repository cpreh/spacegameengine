/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_FBO_TARGET_HPP_INCLUDED
#define SGE_OPENGL_FBO_TARGET_HPP_INCLUDED

#include "target_fwd.hpp"
#include "context_fwd.hpp"
#include "render_buffer_fwd.hpp"
#include "render_buffer_binding_fwd.hpp"
#include "object.hpp"
#include "texture_binding_fwd.hpp"
#include "../common.hpp"
#include "../target.hpp"
#include "../texture_surface_base_ptr.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/target.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace opengl
{
namespace fbo
{

class target
:
	public sge::renderer::target,
	public opengl::target
{
	FCPPT_NONCOPYABLE(
		target
	)
public:
	explicit target(
		opengl::context::object &
	);

	~target();

	void
	bind() const;

	void
	unbind() const;
private:
	void
	add_surface(
		renderer::color_surface_ptr
	);

	void
	remove_surface(
		renderer::color_surface_ptr
	);

	void
	add_surface(
		renderer::depth_stencil_surface_ptr
	);

	void
	remove_surface(
		renderer::depth_stencil_surface_ptr
	);

	renderer::screen_unit
	height() const;

	void
	add_texture_binding(
		opengl::texture_surface_base_ptr,
		GLenum
	);

	void
	attach_buffer(
		GLenum component,
		GLenum attachment
	);

	fbo::context &context_;

	opengl::fbo::object fbo_;

	typedef boost::ptr_vector<
		fbo::texture_binding
	> texture_binding_vector;

	texture_binding_vector texture_bindings_;

	typedef boost::ptr_vector<
		opengl::fbo::render_buffer
	> render_buffer_vector;

	typedef boost::ptr_vector<
		opengl::fbo::render_buffer_binding
	> render_buffer_binding_vector;

	render_buffer_vector render_buffers_;

	render_buffer_binding_vector render_buffer_bindings_;
};

}
}
}

#endif
