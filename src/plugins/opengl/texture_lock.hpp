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


#ifndef SGE_OPENGL_TEXTURE_LOCK_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_LOCK_HPP_INCLUDED

#include "texture_lock_fwd.hpp"
#include "lock_method.hpp"
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class texture_lock
{
	FCPPT_NONCOPYABLE(
		texture_lock
	);
protected:
	texture_lock();
public:
	typedef renderer::size_type size_type;
	typedef renderer::raw_value value_type;
	typedef value_type *pointer;
	typedef value_type const *const_pointer;

	virtual ~texture_lock();

	virtual void
	lock() = 0;

	virtual void
	unlock() = 0;

	virtual void
	pre_unlock() = 0;

	virtual void
	post_copy() = 0;

	virtual pointer
	read_pointer() = 0;

	virtual pointer
	write_pointer() = 0;

	virtual pointer
	read_view_pointer() = 0;

	virtual pointer
	write_view_pointer() = 0;

	virtual lock_method::type
	method() const = 0;
};

}
}

#endif
