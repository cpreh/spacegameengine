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


#ifndef SGE_SRC_IMAGE_DYNAMIC_ALGORITHM_CAC_FUNCTION_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_ALGORITHM_CAC_FUNCTION_HPP_INCLUDED

#include <sge/src/image/dynamic/algorithm/cac/source.hpp>
#include <mizuiro/color/object.hpp>


namespace sge
{
namespace image
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

template<
	typename SourceFormat,
	typename DestFormat
>
struct function
{
	typedef
		mizuiro::color::object<
			typename DestFormat::color_format
		> const
		(
			*type
		)(
			typename cac::source<
				SourceFormat
			>::type const &,
			typename mizuiro::color::object<
				typename DestFormat::color_format
			>::format_store_type const &
		);
};

}
}
}
}
}

#endif
