//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_FROM_MIZUIRO_DIM_HPP_INCLUDED
#define SGE_IMAGE_IMPL_FROM_MIZUIRO_DIM_HPP_INCLUDED

#include <mizuiro/size_type.hpp>
#include <mizuiro/image/dimension.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/init.hpp>
#include <fcppt/math/dim/static.hpp>


namespace sge
{
namespace image
{
namespace impl
{

template<
	typename T,
	mizuiro::size_type N
>
fcppt::math::dim::static_<
	T,
	fcppt::cast::size<
		fcppt::math::size_type
	>(
		N
	)
>
from_mizuiro_dim(
	mizuiro::image::dimension<
		N,
		T
	> const &_src
)
{
	return
		fcppt::math::dim::init<
			fcppt::math::dim::static_<
				T,
				fcppt::cast::size<
					fcppt::math::size_type
				>(
					N
				)
			>
		>(
			[
				&_src
			](
				fcppt::math::size_type const _index
			)
			{
				return
					_src[
						_index
					];
			}
		);
}

}
}
}

#endif
