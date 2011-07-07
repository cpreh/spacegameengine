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


#ifndef SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_PERMUATE_COMPARE_HPP_INCLUDED
#define SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_PERMUATE_COMPARE_HPP_INCLUDED

#include <algorithm>

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
	typename Layout
>
bool
permuate_compare(
	Layout const &_layout1,
	Layout const &_layout2
)
{
	for(
		typename Layout::const_iterator it(
			_layout1.begin()
		);
		it != _layout1.end();
		++it
	)
		if(
			std::find(
				_layout2.begin(),
				_layout2.end(),
				*it
			)
			== _layout2.end()
		)
			return false;

	return true;
}

}
}
}
}
}

#endif
