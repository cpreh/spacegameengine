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
#include "attachment_fwd.hpp"
#include "attachment_unique_ptr.hpp"
#include "context_fwd.hpp"
#include "render_buffer_fwd.hpp"
#include "object.hpp"
#include "../basic_target.hpp"
#include "../common.hpp"
#include "../texture_surface_base_ptr.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/surface_index.hpp>
#include <sge/renderer/target.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sge
{
namespace opengl
{
namespace fbo
{

class target
:
	public opengl::basic_target<
		sge::renderer::target
	>
{
	FCPPT_NONCOPYABLE(
		target
	)
public:
	typedef opengl::basic_target<
		sge::renderer::target
	> base;

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
	color_surface(
		renderer::color_surface_ptr,
		renderer::surface_index
	);

	void
	depth_stencil_surface(
		renderer::depth_stencil_surface_ptr
	);

	renderer::optional_dim2 const
	dim() const;

	renderer::screen_unit
	height() const;

	fbo::attachment_unique_ptr
	create_texture_binding(
		opengl::texture_surface_base_ptr,
		GLenum attachment
	);

	fbo::attachment_unique_ptr
	create_buffer_binding(
		fbo::render_buffer const &,
		GLenum attachment
	);

	void
	add_dim(
		sge::renderer::dim2 const &
	);

	void
	remove_dim();

	void
	check();

	fbo::context &context_;

	opengl::fbo::object fbo_;

	typedef boost::ptr_map<
		renderer::surface_index,
		fbo::attachment
	> attachment_map;

	attachment_map color_attachments_;

	typedef fcppt::scoped_ptr<
		fbo::attachment
	> scoped_attachment;

	scoped_attachment depth_stencil_attachment_;

	renderer::optional_dim2 dim_;
};

}
}
}

#endif
