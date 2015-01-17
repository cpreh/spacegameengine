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


#ifndef SGE_IMAGE_DS_LAYOUT_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_IMAGE_DS_LAYOUT_DEPTH_STENCIL_HPP_INCLUDED

#include <sge/image/ds/channel/depth.hpp>
#include <sge/image/ds/channel/stencil.hpp>
#include <sge/image/ds/space/depth_stencil.hpp>
#include <mizuiro/mpl/list.hpp>


namespace sge
{
namespace image
{
namespace ds
{
namespace layout
{

typedef
sge::image::ds::space::depth_stencil<
	mizuiro::mpl::list<
		sge::image::ds::channel::depth,
		sge::image::ds::channel::stencil
	>
>
depth_stencil;

}
}
}
}

#endif
