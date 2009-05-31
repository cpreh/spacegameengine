/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/vf/dynamic_ordered_element.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/variant/apply_unary.hpp>

sge::ogl::vf::pointer_actor::pointer_actor(
	renderer::vf::dynamic_ordered_element const &e,
	renderer::vf::vertex_size const stride_)
:
	format_(
		variant::apply_unary(
			convert_format(),
			e.element().info()
		)
	),
	stride_(
		static_cast<GLsizei>(
			stride_
		)
	),
	pointer_(
		0
	),
	index_(
		e.element().index()
	),
	offset_(
		e.offset()
	)
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

sge::renderer::vf::vertex_size
sge::ogl::vf::pointer_actor::index() const
{
	return index_;
}

void
sge::ogl::vf::pointer_actor::source(
	vf::pointer const src)
{
	pointer_ = static_cast<renderer::const_raw_pointer>(src) + offset_;
}
