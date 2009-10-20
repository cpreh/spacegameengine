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


#ifndef SGE_SPRITE_WITH_TEXTURE_HPP_INCLUDED
#define SGE_SPRITE_WITH_TEXTURE_HPP_INCLUDED

#include <sge/texture/part_fwd.hpp>

namespace sge
{
namespace sprite
{

template<
	unsigned Num = 1
>
class with_texture;

template<
	unsigned Num
>
class with_texture {
public:
	// TODO!
};

template<>
class with_texture<
	1u
>
{
public:
	explicit with_texture(
		sge::texture::const_part_ptr const texture_
	)
	:
		texture_(texture_)
	{}

	void
	texture(
		sge::texture::const_part_ptr const ntexture_
	)
	{
		texture_ = ntexture_;
	}

	sge::texture::const_part_ptr const
	texture() const
	{
		return texture_;
	}
protected:
	~with_texture()
	{}
private:
	sge::texture::const_part_ptr texture_;
};

}
}

#endif
