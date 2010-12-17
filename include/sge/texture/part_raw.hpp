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


#ifndef SGE_TEXTURE_PART_RAW_HPP_INCLUDED
#define SGE_TEXTURE_PART_RAW_HPP_INCLUDED

#include <sge/texture/part.hpp>
#include <sge/texture/symbol.hpp>
#include <sge/renderer/texture_ptr.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <fcppt/math/box/basic_impl.hpp>

namespace sge
{
namespace texture
{

class part_raw
:
	public part
{
	FCPPT_NONCOPYABLE(
		part_raw
	)
public:
	SGE_TEXTURE_SYMBOL explicit part_raw(
		renderer::texture_ptr
	);

	SGE_TEXTURE_SYMBOL part_raw(
		renderer::texture_ptr,
		renderer::lock_rect const &
	);

	SGE_TEXTURE_SYMBOL ~part_raw();

	SGE_TEXTURE_SYMBOL void
	data(
		image2d::view::const_object const &
	);

	SGE_TEXTURE_SYMBOL renderer::lock_rect const &
	area() const;

	SGE_TEXTURE_SYMBOL renderer::texture_ptr const
	texture();

	SGE_TEXTURE_SYMBOL renderer::const_texture_ptr const
	texture() const;

	SGE_TEXTURE_SYMBOL bool repeatable() const;
private:
	renderer::lock_rect   const area_;

	renderer::texture_ptr const tex_;
};

}
}

#endif
