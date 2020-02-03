//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/visual.hpp>
#include <sge/d3d9/parameters/extract_srgb.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <awl/visual/object.hpp>
#include <fcppt/const.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe.hpp>


sge::renderer::pixel_format::srgb
sge::d3d9::parameters::extract_srgb(
	awl::visual::object const &_visual
)
{
	return
		fcppt::optional::maybe(
			fcppt::cast::dynamic<
				sge::d3d9::visual const
			>(
				_visual
			),
			fcppt::const_(
				sge::renderer::pixel_format::srgb::no
			),
			[](
				fcppt::reference<
					sge::d3d9::visual const
				> const _d3d_visual
			)
			{
				return
					_d3d_visual.get().pixel_format().srgb();
			}
		);
}
