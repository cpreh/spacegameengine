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

#include <sge/renderer/texture_fwd.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/lock_flags.hpp>
#include <sge/noncopyable.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace renderer
{

class scoped_texture_lock {
	SGE_NONCOPYABLE(scoped_texture_lock)
public:
	SGE_SYMBOL scoped_texture_lock(
		texture_ptr,
		lock_flag_t);
	
	SGE_SYMBOL scoped_texture_lock(
		texture_ptr,
		lock_rect const &,
		lock_flag_t);
	
	SGE_SYMBOL image_view const
	value() const;

	SGE_SYMBOL ~scoped_texture_lock();
private:
	texture_ptr const tex;
	image_view const view;
};

}
}

#endif
