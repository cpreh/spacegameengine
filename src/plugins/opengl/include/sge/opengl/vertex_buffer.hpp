/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/opengl/vertex_buffer_fwd.hpp>
#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/wrapper.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/vf/part_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vf/dynamic/converter.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{

class vertex_buffer
:
	public sge::renderer::vertex::buffer,
	public sge::opengl::buffer::wrapper
{
	FCPPT_NONCOPYABLE(
		vertex_buffer
	);
public:
	vertex_buffer(
		sge::opengl::context::system::object &,
		sge::renderer::vf::dynamic::part_index,
		sge::renderer::vf::dynamic::part const &,
		count_type,
		sge::renderer::resource_flags_field const &
	);

	~vertex_buffer();

	void
	use(
		sge::opengl::vf::part const &
	) const;

	void
	unuse(
		sge::opengl::vf::part const &
	) const;
private:
	view_type const
	lock(
		sge::renderer::lock_mode,
		first_type,
		count_type
	);

	const_view_type const
	lock(
		first_type,
		count_type
	) const;

	template<
		typename View
	>
	View const
	do_lock(
		sge::renderer::lock_flags::method,
		first_type,
		count_type
	) const;

	void
	unlock() const;

	count_type const
	size() const;

	sge::renderer::resource_flags_field const
	resource_flags() const;

	sge::renderer::vf::dynamic::part const
	format_part() const;

	sge::renderer::vf::dynamic::part_index const
	format_part_index() const;

	sge::opengl::buffer::object const &
	buffer() const;

	sge::renderer::vf::dynamic::part_index const part_index_;

	sge::renderer::vf::dynamic::part const format_part_;

	mutable sge::renderer::vf::dynamic::converter converter_;

	mutable sge::opengl::buffer::object buffer_;
};

}
}

#endif
