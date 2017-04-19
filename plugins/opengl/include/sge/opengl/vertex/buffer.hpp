/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/wrapper.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vertex/buffer_fwd.hpp>
#include <sge/opengl/vf/part_fwd.hpp>
#include <sge/renderer/dim1_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/lock_segment_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/dynamic/const_view_fwd.hpp>
#include <sge/renderer/vf/dynamic/converter.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/part_cref.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/view_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace vertex
{

class buffer
:
	public sge::renderer::vertex::buffer,
	public sge::opengl::buffer::wrapper
{
	FCPPT_NONCOPYABLE(
		buffer
	);
public:
	buffer(
		sge::opengl::context::object &,
		sge::renderer::vf::dynamic::part_index,
		sge::renderer::vf::dynamic::part const &,
		sge::renderer::vertex::count,
		sge::renderer::resource_flags_field const &
	);

	~buffer()
	override;

	void
	use(
		sge::opengl::vf::part const &
	) const;

	void
	unuse(
		sge::opengl::vf::part const &
	) const;
private:
	sge::renderer::vf::dynamic::view
	lock(
		sge::renderer::lock_segment const &,
		sge::renderer::lock_mode
	)
	override;

	sge::renderer::vf::dynamic::const_view
	lock_c(
		sge::renderer::lock_segment const &
	) const
	override;

	template<
		typename View
	>
	View
	do_lock(
		sge::renderer::lock_flags::method,
		sge::renderer::lock_segment const &
	) const;

	void
	unlock() const
	override;

	sge::renderer::dim1
	size() const
	override;

	sge::renderer::resource_flags_field
	resource_flags() const
	override;

	sge::renderer::vf::dynamic::part_cref
	format() const
	override;

	sge::renderer::vf::dynamic::part_index
	format_part_index() const
	override;

	sge::opengl::buffer::object const &
	get() const
	override;

	sge::renderer::vf::dynamic::part_index const part_index_;

	sge::renderer::vf::dynamic::part const format_part_;

	mutable sge::renderer::vf::dynamic::converter converter_;

	mutable sge::opengl::buffer::object buffer_;
};

}
}
}

#endif
