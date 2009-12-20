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


#ifndef SGE_TEXTURE_PART_HPP_INCLUDED
#define SGE_TEXTURE_PART_HPP_INCLUDED

#include <sge/texture/part_fwd.hpp>
#include <sge/texture/fragmented_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace texture
{

class SGE_CLASS_SYMBOL part
{
	FCPPT_NONCOPYABLE(part)
protected:
	SGE_SYMBOL part();
public:
	SGE_SYMBOL virtual ~part();

	virtual void
	data(
		image::view::const_object const &
	) = 0;

	virtual renderer::lock_rect const &
	area() const = 0;

	virtual renderer::texture_ptr const
	texture() = 0;

	virtual renderer::const_texture_ptr const
	texture() const = 0;

	virtual bool
	repeatable() const = 0;
};

}
}

#endif
