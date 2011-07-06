/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE_DYNAMIC_VIEW_BASIC_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_DYNAMIC_VIEW_BASIC_ELEMENTS_HPP_INCLUDED

#include "../color/formats.hpp"
#include <sge/image/size_type.hpp>
#include <sge/image/view/element_base.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>

namespace sge
{
namespace image
{
namespace dynamic
{
namespace view
{

template<
	sge::image::size_type Dim,
	typename Constness
>
struct basic_elements
:
boost::mpl::transform<
	dynamic::color::formats,
	sge::image::view::element_base<
		boost::mpl::_1,
		Dim,
		Constness
	>
>
{
};

}
}
}
}

#endif
