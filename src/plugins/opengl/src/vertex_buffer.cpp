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
#include <sge/renderer/vf/dynamic/view.hpp>
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>

SGE_OPENGL_INSTANTIATE_BASIC_BUFFER(
	sge::opengl::vertex_buffer_type,
	sge::opengl::vb_ib_vbo_impl
)

sge::opengl::vertex_buffer::vertex_buffer(
	renderer::vf::dynamic::format const &format_,
	size_type const sz,
	renderer::resource_flags_field const &flags
)
:
	format_(format_),
	buf(
		sz,
		format_.stride(),
		flags,
		0
	)
{}

void
sge::opengl::vertex_buffer::set_format() const
{
	buf.bind_me();

	format_.use_me(
		buf.buffer_offset(
			0
		)
	);
}

void
sge::opengl::vertex_buffer::unset_format() const
{
	format_.unuse_me();
}

sge::opengl::vertex_buffer::view_type const
sge::opengl::vertex_buffer::lock(
	renderer::lock_mode::type const flags,
	size_type const offset,
	size_type const range
)
{
	buf.lock(
		convert_lock_method(
			flags
		),
		offset,
		range
	);

	return view_type(
		buf.data(),
		buf.lock_size(),
		format()
	);
}

sge::opengl::vertex_buffer::const_view_type const
sge::opengl::vertex_buffer::lock(
	size_type const offset,
	size_type const range
) const
{
	buf.lock(
		lock_method::readonly,
		offset,
		range
	);

	return const_view_type(
		buf.data(),
		buf.lock_size(),
		format()
	);
}

void
sge::opengl::vertex_buffer::unlock() const
{
	renderer::vf::dynamic::ordered_element_list const &elems(
		format().elements()
	);

	renderer::size_type const stride(
		format().stride()
	);

	FCPPT_ASSERT(buf.lock_size() % stride == 0);

	BOOST_FOREACH(
		renderer::vf::dynamic::ordered_element_list::const_reference elem,
		elems
	)
		if(elem.element().role() == renderer::vf::role::color)
			convert_vertex_colors(
				elem,
				stride,
				buf.lock_size() / stride,
				buf.data()
			);

	buf.unlock();
}

sge::opengl::vertex_buffer::size_type
sge::opengl::vertex_buffer::size() const
{
	return buf.size();
}

sge::renderer::resource_flags_field const
sge::opengl::vertex_buffer::flags() const
{
	return buf.flags();
}

sge::renderer::vf::dynamic::format const &
sge::opengl::vertex_buffer::format() const
{
	return format_.get();
}
