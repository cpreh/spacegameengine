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



#ifndef SGE_SPRITE_DETAIL_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VERTEX_FORMAT_HPP_INCLUDED

#include <sge/sprite/funit.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/color.hpp>
#include <boost/mpl/vector.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

typedef renderer::rgba8_color base_color;

typedef renderer::vf::pos<funit, 3> vertex_pos;
typedef renderer::vf::color<base_color> vertex_color;
typedef renderer::vf::texpos<funit, 2> vertex_texpos;

typedef renderer::vf::format<
	boost::mpl::vector<
		vertex_pos,
		vertex_color,
		vertex_texpos
	>
> vertex_format;

}
}
}

#endif
