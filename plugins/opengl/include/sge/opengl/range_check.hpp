//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_RANGE_CHECK_HPP_INCLUDED
#define SGE_OPENGL_RANGE_CHECK_HPP_INCLUDED

#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
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
