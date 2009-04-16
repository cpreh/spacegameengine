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


#ifndef SGE_RENDERER_COLOR_FORMAT_STATIC_HPP_INCLUDED
#define SGE_RENDERER_COLOR_FORMAT_STATIC_HPP_INCLUDED

#include <sge/renderer/color_types.hpp>
#include <sge/renderer/color_format.hpp>
#include <sge/mpl/index_of.hpp>
#include <boost/static_assert.hpp>

namespace sge
{
namespace renderer
{

template<
	typename Color
>
class color_format_static {
public:
	static color_format::type const value
		= static_cast<color_format::type>(
			mpl::index_of<
				color_types,
				Color
			>::value);
	BOOST_STATIC_ASSERT(
		value < color_format::size);
};

}
}

#endif
