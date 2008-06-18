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


#ifndef SGE_TEXTURE_SIZED_CREATOR_HPP_INCLUDED
#define SGE_TEXTURE_SIZED_CREATOR_HPP_INCLUDED

#include "../renderer/texture_filter.hpp"
#include "../renderer/device.hpp"
#include "../renderer/types.hpp"

namespace sge
{
namespace texture
{

class fragmented;

template<typename T>
class sized_creator {
public:
	sizede_creator(
		renderer::device_ptr rend,
	        const renderer::filter_args& filter,
	        const renderer::texture::dim_type& dim);
	fragmented* operator()() const;
private:
	renderer::device_ptr        rend;
	renderer::filter_args       filter;
	renderer::texture::dim_type dim;
};

}
}

#endif
