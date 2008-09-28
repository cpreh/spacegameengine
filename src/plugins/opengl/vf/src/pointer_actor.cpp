/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../pointer_actor.hpp"
#include "../convert_format.hpp"
#include "../../vbo.hpp"
#include "../../vbo_base.hpp"
#include <sge/renderer/vf/dynamic_ordered_element.hpp>
#include <boost/variant/apply_visitor.hpp>

sge::ogl::vf::pointer_actor::pointer_actor(
	renderer::vf::dynamic_ordered_element const &e,
	renderer::vf::vertex_size const stride_)
:
	format_(
		boost::apply_visitor(
			convert_format(),
			e.element().info())),
	stride_(
		static_cast<GLsizei>(
			stride_)),
	pointer_(
		vb_ib_vbo_impl().buffer_offset(
			vertex_buffer_type(),
			static_cast<GLsizei>(
				e.offset())))
{}

GLenum sge::ogl::vf::pointer_actor::format() const
{
	return format_;
}

GLsizei sge::ogl::vf::pointer_actor::stride() const
{
	return stride_;
}

GLvoid const *sge::ogl::vf::pointer_actor::pointer() const
{
	return pointer_;
}
