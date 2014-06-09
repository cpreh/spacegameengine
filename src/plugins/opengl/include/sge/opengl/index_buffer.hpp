/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/wrapper.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{

class index_buffer
:
	public sge::renderer::index::buffer,
	public sge::opengl::buffer::wrapper
{
	FCPPT_NONCOPYABLE(
		index_buffer
	);
public:
	index_buffer(
		sge::opengl::context::system::object &,
		sge::renderer::index::buffer_parameters const &
	);

	~index_buffer()
	override;

	GLenum
	gl_format() const;

	GLvoid *
	buffer_offset(
		first_type
	) const;

	void
	bind() const;
private:
	sge::renderer::index::buffer::view_type const
	lock(
		sge::renderer::lock_mode,
		sge::renderer::index::buffer::first_type,
		sge::renderer::index::buffer::count_type
	)
	override;

	sge::renderer::index::buffer::const_view_type const
	lock(
		sge::renderer::index::buffer::first_type,
		sge::renderer::index::buffer::count_type
	) const
	override;

	template<
		typename View
	>
	View const
	do_lock(
		sge::renderer::lock_flags::method,
		sge::renderer::index::buffer::first_type,
		sge::renderer::index::buffer::count_type
	) const;

	void
	unlock() const
	override;

	sge::renderer::index::buffer::count_type const
	size() const
	override;

	sge::renderer::resource_flags_field const
	resource_flags() const
	override;

	sge::renderer::index::dynamic::format
	format() const
	override;

	sge::opengl::buffer::object const &
	buffer() const
	override;

	sge::renderer::index::dynamic::format const format_;

	GLenum const gl_format_;

	mutable sge::opengl::buffer::object buffer_;
};

}
}

#endif

