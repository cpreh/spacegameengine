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


#ifndef SGE_RENDERER_TRANSFORM_PIXELS_HPP_INCLUDED
#define SGE_RENDERER_TRANSFORM_PIXELS_HPP_INCLUDED

#include "image_view.hpp"
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <boost/gil/algorithm.hpp>

namespace sge
{
namespace renderer
{

template<
	typename Dst,
	typename Op
>
struct transform_pixels_fn {
	typedef void result_type;

	Dst &_dst;

	transform_pixels_fn(
		Dst& dst,
		Op const &op)
	:
		_dst(dst),
		op(op)
	{}

	template<
		typename Src
	>
	void operator()(
		Src const &src) const
	{
		boost::gil::transform_pixels(
			_dst,
			src,
			op);
	}
private:
	Op const op;
};

template<
	typename Src,
	typename Dst,
	typename Op
>
void variant_transform_pixels_fn(
	boost::gil::variant<Src> const &src,
	boost::gil::variant<Dst> const &dst,
	Op const &op)
{
	transform_pixels_fn<Dst, Op> fn(dst, op);
	boost::gil::apply_operation(src, fn);
}

template<
	typename Op
>
SGE_SYMBOL void transform_pixels(
	const_image_view const &src,
	image_view const &dst,
	Op const &op)
{
	variant_transform_pixels_fn(
		src,
		dst,
		op);
}

}
}

#endif
