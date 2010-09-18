/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "fbo_target_fwd.hpp"
#include "target.hpp"
#include "texture_ptr.hpp"
#include "depth_stencil_texture_ptr.hpp"
#include "texture_base_ptr.hpp"
#include "fbo.hpp"
#include "fbo_texture_binding.hpp"
#include "fbo_context_fwd.hpp"
#include "render_buffer_fwd.hpp"
#include "render_buffer_binding_fwd.hpp"
#include "common.hpp"
#include "context/object_fwd.hpp"
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/texture_ptr.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace opengl
{

class fbo_target
:
	public opengl::target
{
	FCPPT_NONCOPYABLE(fbo_target)
public:
	explicit fbo_target(
		opengl::context::object &,
		sge::renderer::parameters const &,
		opengl::texture_ptr,
		opengl::depth_stencil_texture_ptr
	);

	~fbo_target();

	void
	bind() const;

	void
	unbind() const;
private:
	image::view::const_object const
	lock(
		renderer::lock_rect const &
	) const;

	void
	unlock() const;

	dim_type const
	dim() const;

	void
	add_texture_binding(
		opengl::texture_base_ptr,
		GLenum
	);

	void
	attach_buffer(
		GLenum component,
		GLenum attachment
	);

	fbo_context &context_;

	sge::renderer::texture_ptr const texture_;

	dim_type const dim_;

	opengl::fbo fbo_;

	typedef boost::ptr_vector<
		fbo_texture_binding
	> fbo_texture_binding_vector;

	fbo_texture_binding_vector texture_bindings_;

	typedef boost::ptr_vector<
		opengl::render_buffer
	> render_buffer_vector;

	typedef boost::ptr_vector<
		opengl::render_buffer_binding
	> render_buffer_binding_vector;

	render_buffer_vector render_buffers_;

	render_buffer_binding_vector render_buffer_bindings_;
};

}
}

#endif
