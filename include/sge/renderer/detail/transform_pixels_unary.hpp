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


#ifndef SGE_RENDERER_DETAIL_TRANSFORM_PIXELS_UNARY_HPP_INCLUDED
#define SGE_RENDERER_DETAIL_TRANSFORM_PIXELS_UNARY_HPP_INCLUDED

#include <cstddef>

namespace sge
{
namespace renderer
{
namespace detail
{

template<
	typename Op
>
class transform_pixels_unary {
public:
	typedef void result_type;

	explicit transform_pixels_unary(
		Op const &op)
	:
		op(op)
	{}

	template<
		typename Src,
		typename Dest
	>
	result_type
	operator()(
		Src const &src,
		Dest const &dst) const
	{
		for (std::ptrdiff_t y = 0; y < dst.height(); ++y)
		{
			typename Src::x_iterator const src_it = src.row_begin(y);
			typename Dest::x_iterator const dst_it = dst.row_begin(y);
			for (std::ptrdiff_t x = 0; x < dst.width(); ++x)
				op(src_it[x], dst_it[x]);
		}
	}
private:
	Op const op;
};

}
}
}

#endif
