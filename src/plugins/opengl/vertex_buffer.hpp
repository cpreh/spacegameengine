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


#ifndef SGE_OPENGL_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_BUFFER_HPP_INCLUDED

#include "vertex_buffer_fwd.hpp"
#include "buffer.hpp"
#include "vertex_declaration_fwd.hpp"
#include "context/object_fwd.hpp"
#include "vf/part_fwd.hpp"
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class vertex_buffer
:
	public renderer::vertex_buffer
{
	FCPPT_NONCOPYABLE(
		vertex_buffer
	);
public:
	vertex_buffer(
		context::object &,
		renderer::vf::dynamic::part_index,
		renderer::vf::dynamic::part const &,
		size_type,
		renderer::resource_flags_field const &
	);

	void
	use(
		opengl::vf::part const &
	) const;

	void
	unuse(
		opengl::vf::part const &
	) const;
private:
	view_type const
	lock(
		renderer::lock_mode::type,
		size_type offset,
		size_type range
	);

	const_view_type const
	lock(
		size_type offset,
		size_type range
	) const;

	void
	unlock() const;

	size_type
	size() const;

	renderer::resource_flags_field const
	flags() const;

	renderer::vf::dynamic::part const
	format_part() const;

	renderer::vf::dynamic::part_index const
	format_part_index() const;

	renderer::vf::dynamic::part_index const part_index_;

	renderer::vf::dynamic::part const format_part_;

	mutable opengl::buffer buffer_;
};

}
}

#endif
