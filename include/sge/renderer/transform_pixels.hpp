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



#ifndef SGE_RENDERER_TRANSFORM_PIXELS_HPP_INCLUDED
#define SGE_RENDERER_TRANSFORM_PIXELS_HPP_INCLUDED

#include <sge/renderer/detail/transform_pixels_unary.hpp>
#include <sge/renderer/detail/transform_pixels_binary.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/apply_binary.hpp>
#include <sge/variant/apply_ternary.hpp>
#include <sge/variant/object_impl.hpp>
#include <boost/bind.hpp>
#include <cstddef>

// TODO: provide all overloads

namespace sge
{
namespace renderer
{

template<
	typename Src,
	typename Dest,
	typename Op
>
void transform_pxiels(
	Src const &src,
	Dest const &dest,
	Op const &op)
{
	detail::transform_pixels_unary<
		Op
	> const fun(
		op
	);

	fun(
		src,
		dest
	);
}

template<
	typename Op
>
void transform_pixels(
	const_image_view const &src,
	image_view const &dst,
	Op const &op)
{
	variant::apply_binary(
		detail::transform_pixels_unary<
			Op
		>(
			op
		),
		src,
		dst
	);
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
	variant::apply_unary(
		boost::bind(
			detail::transform_pixels_unary<
				Op
			>(
				op
			),
			src,
			_1
		),
		dest
	);
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
	variant::apply_unary(
		boost::bind(
			detail::transform_pixels_unary<
				Op
			>(
				op
			),
			_1,
			dest
		),
		src
	);
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
	variant::apply_binary(
		boost::bind(
			detail::transform_pixels_binary<
				Op
			>(
				op
			),
			src1,
			_1,
			_2
		),
		src2,
		dest
	);
}

template<
	typename Op
>
void transform_pixels(
	const_image_view const &src1,
	const_image_view const &src2,
	image_view const &dest,
	Op const &op)
{
	variant::apply_ternary(
		detail::transform_pixels_binary<
			Op
		>(
			op
		),
		src1,
		src2,
		dest
	);
}

}
}

#endif
