/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_RENDERER_TEXTURE_BASE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASE_HPP_INCLUDED

#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/lock_flags.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL texture_base {
	SGE_NONCOPYABLE(texture_base)
protected:
	SGE_SYMBOL texture_base();
public:
	typedef renderer::size_type                   size_type;
	typedef resource_flag_t                       resource_flag_type;
	typedef lock_flag_t                           lock_flag_type;

	SGE_SYMBOL virtual ~texture_base();
	virtual size_type content() const = 0;
	virtual resource_flag_type flags() const = 0;
};

}
}

#endif
