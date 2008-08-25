/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_SCOPED_TEXTURE_LOCK_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_TEXTURE_LOCK_HPP_INCLUDED

#include "texture.hpp"
#include "image_view.hpp"
#include "scoped_lock_wrapper.hpp"
#include "scoped_lock.hpp"
#include "../export.hpp"

namespace sge
{
namespace renderer
{

typedef scoped_lock<
	texture_ptr,
	image_view
> scoped_texture_lock;

typedef scoped_lock<
	const_texture_ptr,
	const_image_view
> const_scoped_texture_lock;

typedef scoped_lock_wrapper<
	texture_ptr,
	image_view
> scoped_texture_lock_wrapper;

typedef scoped_lock_wrapper<
	const_texture_ptr,
	const_image_view
> const_scoped_texture_lock_wrapper;

SGE_SYMBOL scoped_texture_lock_wrapper const
make_scoped_lock(
	texture_ptr,
	lock_flag_t);

SGE_SYMBOL scoped_texture_lock_wrapper const
make_scoped_lock(
	texture_ptr t,
	lock_rect const &r,
	lock_flag_t flags);

SGE_SYMBOL const_scoped_texture_lock_wrapper const
make_scoped_lock(
	const_texture_ptr t,
	lock_rect const &r);

SGE_SYMBOL const_scoped_texture_lock_wrapper const
make_scoped_lock(
	const_texture_ptr t);

}
}

#endif
