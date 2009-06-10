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


#ifndef SGE_OPENGL_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_BUFFER_HPP_INCLUDED

#include "vbo.hpp"
#include "basic_buffer.hpp"
#include "vf/format.hpp"
#include <sge/renderer/vertex_buffer.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{
class dynamic_format;
}
}
namespace opengl
{

class vertex_buffer : public renderer::vertex_buffer {
public:
	vertex_buffer(
		renderer::vf::dynamic_format const &,
		size_type sz,
		resource_flag_type flags);

	void set_format() const;
private:
	view_type const
	lock(
		lock_flag_type flags,
		size_type offset,
		size_type range);

	const_view_type const
	lock(
		size_type offset,
		size_type range) const;

	void unlock() const;

	size_type size() const;
	resource_flag_type flags() const;

	renderer::vf::dynamic_format const &
	format() const;

	vf::format const format_;

	typedef basic_buffer<
		vertex_buffer_type,
		vb_ib_vbo_impl
	> buffer_type;

	mutable buffer_type buf;
};

}
}

#endif
