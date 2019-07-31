//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/dim2.hpp>
#include <sge/texture/next_power_of_2.hpp>
#include <fcppt/math/next_power_of_2.hpp>


sge::renderer::dim2
sge::texture::next_power_of_2(
	sge::renderer::dim2 const &_size
)
{
	return
		sge::renderer::dim2(
			fcppt::math::next_power_of_2(
				_size.w()
			),
			fcppt::math::next_power_of_2(
				_size.h()
			)
		);
}
