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


#ifndef SGE_TEXTURE_PART_RAW_PTR_FWD_HPP_INCLUDED
#define SGE_TEXTURE_PART_RAW_PTR_FWD_HPP_INCLUDED

#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/texture/basic_part_raw_fwd.hpp>


namespace sge
{
namespace texture
{

typedef
sge::texture::basic_part_raw<
	sge::renderer::texture::planar_unique_ptr &&
>
part_raw_ptr;

}
}

#endif
