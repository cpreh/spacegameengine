/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_WRITEONLY_TEXTURE_LOCK_HPP_INCLUDED
#define SGE_OPENGL_WRITEONLY_TEXTURE_LOCK_HPP_INCLUDED

#include "texture_lock.hpp"
#include "buffer.hpp"
#include "context/object_fwd.hpp"
#include <sge/renderer/resource_flags_field.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class writeonly_texture_lock
:
	public texture_lock
{
	FCPPT_NONCOPYABLE(
		writeonly_texture_lock
	)
public:
	writeonly_texture_lock(
		context::object &,
		size_type lock_size,
		size_type stride,
		renderer::resource_flags_field const &
	);

	~writeonly_texture_lock();

	void
	lock();

	void
	unlock();

	void
	pre_unlock();

	void
	post_copy();

	pointer
	write_pointer();

	pointer
	view_pointer();
private:
	lock_method::type
	method() const;

	buffer buffer_;
};

}
}

#endif
