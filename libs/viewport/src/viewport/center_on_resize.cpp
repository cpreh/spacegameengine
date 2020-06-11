//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/viewport/resize_callback.hpp>
#include <sge/viewport/impl/center.hpp>
#include <sge/window/dim.hpp>
#include <awl/window/event/resize.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::viewport::resize_callback
sge::viewport::center_on_resize(
	sge::window::dim const &_dim
)
{
	return
		sge::viewport::resize_callback{
			[
				_dim
			](
				awl::window::event::resize const &_resize
			)
			{
				return
					sge::viewport::impl::center(
						_dim,
						fcppt::math::dim::structure_cast<
							sge::window::dim,
							fcppt::cast::size_fun
						>(
							_resize.dim()
						)
					);
			}
		};
}
