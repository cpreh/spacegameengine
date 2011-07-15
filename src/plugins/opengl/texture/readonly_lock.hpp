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


#ifndef SGE_OPENGL_TEXTURE_READONLY_LOCK_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_READONLY_LOCK_HPP_INCLUDED

#include "lock_base.hpp"
#include "../buffer.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace texture
{

class readonly_lock
:
	public opengl::texture::lock_base
{
	FCPPT_NONCOPYABLE(
		readonly_lock
	);
public:
	readonly_lock(
		opengl::context::object &,
		size_type whole_size,
		size_type stride,
		renderer::resource_flags_field const &
	);

	~readonly_lock();

	void
	lock();

	void
	unlock();

	void
	pre_unlock();

	void
	post_copy();

	pointer
	read_pointer();

	pointer
	write_pointer();

	pointer
	read_view_pointer();

	pointer
	write_view_pointer();
private:
	renderer::lock_flags::method::type
	method() const;

	opengl::buffer buffer_;
};

}
}
}

#endif
