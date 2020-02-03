//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/parameters/extract_size.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <awl/window/object.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/optional/maybe.hpp>


sge::renderer::screen_size const
sge::d3d9::parameters::extract_size(
	sge::renderer::display_mode::optional_object const &_display_mode,
	awl::window::object &_window
)
{
	return
		fcppt::optional::maybe(
			_display_mode,
			[
				&_window
			]
			{
				return
					fcppt::math::dim::structure_cast<
						sge::renderer::screen_size,
						fcppt::cast::size_fun
					>(
						_window.size()
					);

			},
			[](
				sge::renderer::display_mode::object const &_mode
			)
			{
				return
					_mode.pixel_size().get();
			}
		);
}
