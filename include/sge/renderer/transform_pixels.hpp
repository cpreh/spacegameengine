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

#include <sge/renderer/image_view.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <boost/bind.hpp>
#include <cstddef>

namespace sge
{
namespace renderer
{

template<
	typename View1,
	typename View2,
	typename View3,
	typename F
>
void transform_pixels_static( // TODO: rename this when all overloads are there
	View1 const &src1,
	View2 const &src2,
	View3 const &dst,
	F const &fun)
{
	for (std::ptrdiff_t y = 0; y < dst.height(); ++y)
	{
		typename View1::x_iterator const src1_it = src1.row_begin(y);
		typename View2::x_iterator const src2_it = src2.row_begin(y);
		typename View3::x_iterator const dst_it = dst.row_begin(y);
		for (std::ptrdiff_t x = 0; x < dst.width(); ++x)
			fun(src1_it[x], src2_it[x], dst_it[x]);
	}
}

template<
	typename Op
>
struct transform_pixels_fn {
	typedef void result_type;

	explicit transform_pixels_fn(
		Op const &op)
	:
		op(op)
	{}

	template<
		typename Src,
		typename Dest
	>
	void operator()(
		Src const &src,
		Dest const &dest) const
	{
		boost::gil::transform_pixels(
			src,
			dest,
			op);
	}
private:
	Op const op;
};

template<
	typename Op
>
struct transform_pixels_binary_fn {
	typedef void result_type;

	explicit transform_pixels_binary_fn(
		Op const &op)
	:
		op(op)
	{}

	template<
		typename Src1,
		typename Src2,
		typename Dest
	>
	void operator()(
		Src1 const &src1,
		Src2 const &src2,
		Dest const &dest) const
	{
		transform_pixels_static(
			src1,
			src2,
			dest,
			op);
	}
private:
	Op const op;
};

template<
	typename Op
>
void transform_pixels(
	const_image_view const &src,
	image_view const &dst,
	Op const &op)
{
	boost::gil::apply_operation(
		src,
		dst,
		transform_pixels_fn<Op>(
			op));
}

template<
	typename Src,
	typename Op
>
void transform_pixels(
	Src const &src,
	image_view const &dest,
	Op const &op)
{
	boost::gil::apply_operation(
		dest,
		boost::bind(
			transform_pixels_fn<Op>(
				op),
			src,
			_1));
}

template<
	typename Dest,
	typename Op
>
void transform_pixels(
	const_image_view const &src,
	Dest const &dest,
	Op const &op)
{
	boost::gil::apply_operation(
		src,
		boost::bind(
			transform_pixels_fn<Op>(
				op),
			_1,
			dest));
}

template<
	typename Src1,
	typename Op
>
void transform_pixels(
	Src1 const &src1,
	const_image_view const &src2,
	image_view const &dest,
	Op const &op)
{
	boost::gil::apply_operation(
		src2,
		dest,
		boost::bind(
			transform_pixels_binary_fn<Op>(
				op),
			src1,
			_1,
			_2));
}

}
}

#endif
