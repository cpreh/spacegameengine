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


#ifndef SGE_IMAGE_VIEW_MAKE_MIZUIRO_TYPE_HPP_INCLUDED
#define SGE_IMAGE_VIEW_MAKE_MIZUIRO_TYPE_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/view/basic_format.hpp>
#include <sge/image/view/mizuiro_type.hpp>
#include <mizuiro/image/view_impl.hpp>
#include <mizuiro/image/format/include/interleaved.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename ColorFormat,
	typename Dim,
	typename Constness
>
using make_mizuiro_type
=
sge::image::view::mizuiro_type<
	sge::image::view::basic_format<
		Dim::value,
		ColorFormat
	>,
	Constness
>;

}
}
}

#endif
