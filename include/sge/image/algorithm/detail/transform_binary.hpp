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


#ifndef SGE_IMAGE_ALGORITHM_DETAIL_TRANSFORM_BINARY_HPP_INCLUDED
#define SGE_IMAGE_ALGORITHM_DETAIL_TRANSFORM_BINARY_HPP_INCLUDED

#include <cstddef>

namespace sge
{
namespace image
{
namespace algorithm
{
namespace detail
{

template<
	typename Op
>
class transform_binary {
public:
	typedef void result_type;

	explicit transform_binary(
		Op const &op)
	:
		op(op)
	{}

	template<
		typename Src1,
		typename Src2,
		typename Dest
	>
	result_type
	operator()(
		Src1 const &src1,
		Src2 const &src2,
		Dest const &dest) const
	{

		for (std::ptrdiff_t y = 0; y < dest.height(); ++y)
		{
			typename Src1::x_iterator const src1_it = src1.row_begin(y);
			typename Src2::x_iterator const src2_it = src2.row_begin(y);
			typename Dest::x_iterator const dest_it = dest.row_begin(y);
			for (std::ptrdiff_t x = 0; x < dest.width(); ++x)
				op(src1_it[x], src2_it[x], dest_it[x]);
		}
	}
private:
	Op const op;
};

}
}
}
}

#endif
