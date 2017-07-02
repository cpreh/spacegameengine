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


#ifndef SGE_OPENGL_RANGE_CHECK_HPP_INCLUDED
#define SGE_OPENGL_RANGE_CHECK_HPP_INCLUDED

#include <fcppt/use.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/algorithm/all_of.hpp>
#include <fcppt/math/int_range_count.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/at.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/at.hpp>


namespace sge
{
namespace opengl
{

template<
	typename T,
	fcppt::math::size_type N,
	typename S
>
bool
range_check(
	fcppt::math::dim::object<
		T,
		N,
		S
	> const &_dim,
	fcppt::math::box::object<
		T,
		N
	> const &_box
)
{
	return
		fcppt::algorithm::all_of(
			fcppt::math::int_range_count<
				N
			>{},
			[
				&_dim,
				&_box
			](
				auto const _index
			)
			{
				FCPPT_USE(
					_index
				);

				typedef
				fcppt::tag_type<
					decltype(
						_index
					)
				>
				index;

				return
					fcppt::math::vector::at<
						index::value
					>(
						_box.max()
					)
					<=
					fcppt::math::dim::at<
						index::value
					>(
						_dim
					);
			}
		);
}

}
}

#endif
