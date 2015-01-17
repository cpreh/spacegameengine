/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_REF_TYPE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_REF_TYPE_HPP_INCLUDED

#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace primitives
{

template<
	sge::sprite::config::texture_ownership Ownership
>
struct texture_ref_type;

template<>
struct texture_ref_type<
	sge::sprite::config::texture_ownership::reference
>
{
	typedef sge::texture::const_optional_part_ref type;
};

template<>
struct texture_ref_type<
	sge::sprite::config::texture_ownership::shared
>
{
	typedef sge::texture::const_part_shared_ptr type;
};

}
}
}
}

#endif
