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


#ifndef SGE_TEXTURE_ATLASING_BORDER_W_HPP_INCLUDED
#define SGE_TEXTURE_ATLASING_BORDER_W_HPP_INCLUDED

#include <sge/image/algorithm/uninitialized_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/atlasing/inner_rect.hpp>
#include <sge/texture/detail/symbol.hpp>


namespace sge
{
namespace texture
{
namespace atlasing
{

SGE_TEXTURE_DETAIL_SYMBOL
void
border_w(
	sge::renderer::texture::planar &,
	sge::image2d::view::const_object const &,
	sge::texture::atlasing::inner_rect const &,
	sge::image::algorithm::uninitialized
);

}
}
}

#endif
