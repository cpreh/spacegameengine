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



#include "../vertex_buffer.hpp"
#include "../vbo.hpp"
#include "../convert_vertex_colors.hpp"
#include "../instantiate_basic_buffer.hpp"
#include <sge/assert.hpp>
#include <boost/foreach.hpp>

SGE_OPENGL_INSTANTIATE_BASIC_BUFFER(
	sge::ogl::vertex_buffer_type,
	sge::ogl::vb_ib_vbo_impl)

sge::ogl::vertex_buffer::vertex_buffer(
	renderer::vf::dynamic_format const &format_,
	size_type const sz,
	resource_flag_type const flags)
:
	format_(format_),
	buf(
		sz,
		format_.stride(),
		flags,
		0)
{}

void sge::ogl::vertex_buffer::set_format() const
{
	buf.bind_me();
	format_.use_me(
		buf.buffer_offset(0)
	);
}

sge::ogl::vertex_buffer::view_type const
sge::ogl::vertex_buffer::lock(
	lock_flag_type const flags,
	size_type const offset,
	size_type const range)
{
	buf.lock(
		convert_lock_method(
			flags),
		offset,
		range);
	
	return view_type(
		buf.data(),
		buf.lock_size(),
		format());
}

sge::ogl::vertex_buffer::const_view_type const
sge::ogl::vertex_buffer::lock(
	size_type const offset,
	size_type const range) const
{
	buf.lock(
		lock_method::readonly,
		offset,
		range);

	return const_view_type(
		buf.data(),
		buf.lock_size(),
		format());
}

void
sge::ogl::vertex_buffer::unlock() const
{
	renderer::vf::dynamic_ordered_element_list const &elems(
		format().elements());
	
	renderer::size_type const stride(
		format().stride());

	SGE_ASSERT(buf.lock_size() % stride == 0);

	BOOST_FOREACH(renderer::vf::dynamic_ordered_element_list::const_reference elem, elems)
		if(elem.element().role() == renderer::vf::role::color)
			convert_vertex_colors(
				elem,
				stride,
				buf.lock_size() / stride,
				const_cast<unsigned char *>(
					buf.data())); // FIXME
	
	buf.unlock();
}

sge::ogl::vertex_buffer::size_type
sge::ogl::vertex_buffer::size() const
{
	return buf.size();
}

sge::ogl::vertex_buffer::resource_flag_type
sge::ogl::vertex_buffer::flags() const
{
	return buf.flags();
}

sge::renderer::vf::dynamic_format const &
sge::ogl::vertex_buffer::format() const
{
	return format_.get();
}
