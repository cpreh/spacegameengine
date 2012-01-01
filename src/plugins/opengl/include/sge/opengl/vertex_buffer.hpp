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
#include <sge/opengl/vertex_declaration_fwd.hpp>
#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/wrapper.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/part_fwd.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/lock_flags/method.hpp>
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
	public renderer::vertex_buffer,
	public opengl::buffer::wrapper
{
	FCPPT_NONCOPYABLE(
		vertex_buffer
	);
public:
	vertex_buffer(
		context::object &,
		renderer::vf::dynamic::part_index,
		renderer::vf::dynamic::part const &,
		count_type,
		renderer::resource_flags_field const &
	);

	~vertex_buffer();

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
		renderer::lock_flags::method::type,
		first_type,
		count_type
	) const;

	void
	unlock() const;

	count_type const
	size() const;

	renderer::resource_flags_field const
	resource_flags() const;

	renderer::vf::dynamic::part const
	format_part() const;

	renderer::vf::dynamic::part_index const
	format_part_index() const;

	opengl::buffer::object const &
	buffer() const;

	renderer::vf::dynamic::part_index const part_index_;

	renderer::vf::dynamic::part const format_part_;

	mutable renderer::vf::dynamic::converter converter_;

	mutable opengl::buffer::object buffer_;
};

}
}

#endif
