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


#ifndef SGE_RENDERER_IMAGE_VIEW_HPP_INCLUDED
#define SGE_RENDERER_IMAGE_VIEW_HPP_INCLUDED

#include <boost/gil/image_view.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/dynamic_image/any_image_view.hpp>
#include <boost/mpl/vector.hpp>

namespace sge
{
namespace renderer
{

// TODO: maybe replace this with a macro to make generation easier

typedef boost::gil::any_image_view<
	boost::mpl::vector<
		boost::gil::rgba8_view_t,
		boost::gil::argb8_view_t,
		boost::gil::bgra8_view_t
	>
> image_view;

typedef boost::gil::any_image_view<
	boost::mpl::vector<
		boost::gil::rgba8c_view_t,
		boost::gil::argb8c_view_t,
		boost::gil::bgra8c_view_t
	>
> const_image_view;

}
}

#endif
