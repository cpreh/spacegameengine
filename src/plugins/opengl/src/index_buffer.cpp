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
#include <sge/renderer/index/format_stride.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

SGE_OPENGL_INSTANTIATE_BUFFER_BASE(
	sge::renderer::index_buffer,
	sge::ogl::index_buffer_type,
	sge::ogl::vb_ib_vbo_impl)

sge::ogl::index_buffer::index_buffer(
	renderer::index::format::type const format_,
	size_type const sz,
	renderer::resource_flag_t const flags)
:
	detail::index_buffer_base(
		sz,
		renderer::index::format_stride(format_),
		flags,
		0),
	format_(format_)
{}

sge::renderer::index::format::type
sge::ogl::index_buffer::format() const
{
	return format_;
}

GLenum sge::ogl::index_buffer::gl_format() const
{
	switch(format_) {
	case renderer::index::format::i16:
		return GL_UNSIGNED_SHORT;
	case renderer::index::format::i32:
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

sge::renderer::index::view const
sge::ogl::index_buffer::view()
{
	// FIXME: allocate the buffer so type punning is not needed!
	switch(format()) {
	case renderer::index::format::i16:
		return renderer::index::view_16(
			reinterpret_cast<renderer::index::view_16::pointer>(
				data()),
			lock_size() / stride());
	case renderer::index::format::i32:
		return renderer::index::view_32(
			reinterpret_cast<renderer::index::view_32::pointer>(
				data()),
			lock_size() / stride());
	default:
		throw exception(
			SGE_TEXT("Invalid format in ogl::index_buffer::view()!"));
	}
}

sge::renderer::index::const_view const
sge::ogl::index_buffer::view() const
{
	switch(format()) {
	case renderer::index::format::i16:
		return renderer::index::const_view_16(
			reinterpret_cast<renderer::index::const_view_16::pointer>(
				data()),
			lock_size() / stride());
	case renderer::index::format::i32:
		return renderer::index::const_view_32(
			reinterpret_cast<renderer::index::const_view_32::pointer>(
				data()),
			lock_size() / stride());
	default:
		throw exception(
			SGE_TEXT("Invalid stride in ogl::index_buffer::view()!"));
	}
}
