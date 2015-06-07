/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_BUFFER_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_OBJECT_HPP_INCLUDED

#include <sge/opengl/buffer/base_fwd.hpp>
#include <sge/opengl/buffer/holder.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/object_fwd.hpp>
#include <sge/opengl/buffer/optional_id_fwd.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef sge::renderer::size_type size_type;

	typedef sge::renderer::raw_value value_type;

	typedef value_type *pointer;

	typedef value_type const *const_pointer;

	typedef sge::renderer::lock_flags::method lock_flag_type;

	object(
		sge::opengl::buffer::base &,
		size_type size,
		size_type stride,
		sge::renderer::resource_flags_field const &,
		const_pointer src
	);

	~object();

	static size_type const npos = static_cast<size_type>(-1);

	void
	lock(
		lock_flag_type const &,
		size_type first = 0,
		size_type count = npos
	);

	void
	unlock();

	void
	sub_data(
		const_pointer data,
		size_type first,
		size_type count
	);

	size_type
	size() const;

	size_type
	stride() const;

	sge::renderer::resource_flags_field const &
	flags() const;

	pointer
	data();

	const_pointer
	data() const;

	size_type
	lock_size() const;

	void
	unbind();

	void
	bind() const;

	pointer
	buffer_offset(
		size_type offset
	) const;

	pointer
	raw_buffer() const;

	sge::opengl::buffer::id const
	id() const;

	bool
	native() const;
private:
	void
	bind_id(
		sge::opengl::buffer::optional_id const &
	) const;

	sge::opengl::buffer::base &base_;

	size_type const
		size_,
		stride_;

	sge::renderer::resource_flags_field const flags_;

	pointer dest_;

	sge::opengl::buffer::holder const holder_;

	size_type
		lock_offset_,
		lock_size_;
};

}
}
}

#endif
