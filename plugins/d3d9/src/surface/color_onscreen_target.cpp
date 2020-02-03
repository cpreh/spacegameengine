//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/get_render_target.hpp>
#include <sge/d3d9/surface/color_create_function.hpp>
#include <sge/d3d9/surface/color_onscreen_target.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::d3d9::surface::color_create_function
sge::d3d9::surface::color_onscreen_target(
	IDirect3DDevice9 &_device
)
{
	return
		sge::d3d9::surface::color_create_function{
			[
				&_device
			]{
				return
					fcppt::optional::to_exception(
						sge::d3d9::devicefuncs::get_render_target(
							_device,
							sge::renderer::target::surface_index(
								0u
							)
						),
						[]{
							return
								sge::renderer::exception{
									FCPPT_TEXT("Unable to get render target.")
								};
						}
					);
			}
		};
}
