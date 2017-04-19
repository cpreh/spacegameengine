/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE_DS_STATIC_FORMATS_HPP_INCLUDED
#define SGE_IMAGE_DS_STATIC_FORMATS_HPP_INCLUDED

#include <sge/image/ds/d16_format.hpp>
#include <sge/image/ds/d24s8_format.hpp>
#include <sge/image/ds/d32_format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace ds
{

typedef
boost::mpl::vector3<
	sge::image::ds::d16_format,
	sge::image::ds::d32_format,
	sge::image::ds::d24s8_format
>
static_formats;

}
}
}

#endif
