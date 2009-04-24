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



#ifndef SGE_TEXTURE_SIZED_CREATOR_HPP_INCLUDED
#define SGE_TEXTURE_SIZED_CREATOR_HPP_INCLUDED

#include <sge/texture/fragmented_auto_ptr.hpp>
#include <sge/renderer/filter/texture.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/color_format.hpp>
#include <sge/renderer/dim_types.hpp>

namespace sge
{
namespace texture
{

template<typename T>
class sized_creator {
public:
	sizede_creator(
		renderer::device_ptr rend,
		renderer::color_format::type format,
	        renderer::filter::texture const &filter,
	        renderer::texture::dim_type const &dim);
	fragmented_auto_ptr operator()() const;
private:
	renderer::device_ptr            rend;
	renderer::color_format::type    format;
	renderer::filter::texture       filter;
	renderer::dim_type              dim;
};

}
}

#endif
