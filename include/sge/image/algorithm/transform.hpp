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



#ifndef SGE_IMAGE_ALGORITHM_TRANSFORM_HPP_INCLUDED
#define SGE_IMAGE_ALGORITHM_TRANSFORM_HPP_INCLUDED

#include <sge/image/algorithm/detail/transform_unary.hpp>
#include <sge/image/algorithm/detail/transform_binary.hpp>
#include <sge/image/view/object.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/variant/apply_unary.hpp>
#include <sge/variant/apply_binary.hpp>
#include <sge/variant/apply_ternary.hpp>
#include <sge/variant/object_impl.hpp>
#include <boost/bind.hpp>
#include <cstddef>

// TODO: provide all overloads

namespace sge
{
namespace image
{
namespace algorithm
{

template<
	typename Src,
	typename Dest,
	typename Op
>
void transform(
	Src const &src,
	Dest const &dest,
	Op const &op)
{
	detail::transform_unary<
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
void transform(
	view::const_object const &src,
	view::object const &dst,
	Op const &op)
{
	variant::apply_binary(
		detail::transform_unary<
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
void transform(
	Src const &src,
	view::object const &dest,
	Op const &op)
{
	variant::apply_unary(
		boost::bind(
			detail::transform_unary<
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
void transform(
	view::const_object const &src,
	Dest const &dest,
	Op const &op)
{
	variant::apply_unary(
		boost::bind(
			detail::transform_unary<
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
void transform(
	Src1 const &src1,
	view::const_object const &src2,
	view::object const &dest,
	Op const &op)
{
	variant::apply_binary(
		boost::bind(
			detail::transform_binary<
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
void transform(
	view::const_object const &src1,
	view::const_object const &src2,
	view::object const &dest,
	Op const &op)
{
	variant::apply_ternary(
		detail::transform_binary<
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
}

#endif
