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


#ifndef SGE_OPENGL_TEXTURE_CREATE_LOCK_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CREATE_LOCK_HPP_INCLUDED

#include "lock_base_unique_ptr.hpp"
#include "lock_base.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/method.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

texture::lock_base_unique_ptr
create_lock(
	context::object &,
	renderer::lock_flags::method::type,
	texture::lock_base::size_type read_size,
	texture::lock_base::size_type write_size,
	texture::lock_base::size_type stride,
	renderer::resource_flags_field const &
);

}
}
}

#endif
