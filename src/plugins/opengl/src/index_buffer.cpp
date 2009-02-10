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


#include "../index_buffer.hpp"
#include "../vbo.hpp"
#include "../instantiate_buffer_base.hpp"
#include <sge/renderer/make_index_view.hpp>
#include <sge/renderer/index_format_stride.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

SGE_OPENGL_INSTANTIATE_BUFFER_BASE(
	sge::renderer::index_buffer,
	sge::ogl::index_buffer_type,
	sge::ogl::vb_ib_vbo_impl)

sge::ogl::index_buffer::index_buffer(
	renderer::index_format::type const format_,
	size_type const sz,
	renderer::resource_flag_t const flags)
:
	detail::index_buffer_base(
		sz,
		renderer::index_format_stride(format_),
		flags,
		0),
	format_(format_)
{}

sge::renderer::index_format::type
sge::ogl::index_buffer::index_format() const
{
	return format_;
}

GLenum sge::ogl::index_buffer::format() const
{
	switch(format_) {
	case renderer::index_format::index16:
		return GL_UNSIGNED_SHORT;
	case renderer::index_format::index32:
		return GL_UNSIGNED_INT;
	default:
		throw exception(
			SGE_TEXT("Wrong format in ogl::index_buffer!"));
	}
}

sge::ogl::index_buffer::const_pointer
sge::ogl::index_buffer::buffer_offset(
	size_type const sz) const
{
	return base::buffer_offset(sz);
}

void sge::ogl::index_buffer::bind_me() const
{
	base::bind_me();
}

sge::renderer::dynamic_index_view const
sge::ogl::index_buffer::view()
{
	return renderer::make_index_view(
		detail::index_buffer_base::data(),
		lock_size(),
		index_format());
}

sge::renderer::const_dynamic_index_view const
sge::ogl::index_buffer::view() const
{
	return renderer::make_index_view(
		detail::index_buffer_base::data(),
		lock_size(),
		index_format());
}
