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


#ifndef SGE_TEXTURE_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_FRAGMENTED_HPP_INCLUDED

#include "../shared_ptr.hpp"
#include "../renderer/texture.hpp"
#include "part.hpp"

namespace sge
{
namespace texture
{

class fragmented {
public:
	virtual const part_ptr consume_fragment(
		const renderer::texture::dim_type&) = 0;
	virtual void return_fragment(
		const  part&) = 0;
	virtual const renderer::texture_ptr get_texture() const = 0;
	virtual bool repeatable() const = 0;
	virtual ~fragmented(){}
};

typedef shared_ptr<fragmented> fragmented_ptr;

}
}

#endif
