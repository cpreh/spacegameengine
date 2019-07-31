//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/color_buffer/writable_surface.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/target/from_texture.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>


sge::renderer::target::offscreen_unique_ptr
sge::renderer::target::from_texture(
	sge::renderer::device::core &_device,
	sge::renderer::texture::planar &_texture
)
{
	if(
		!(
			_texture.capabilities()
			&
			sge::renderer::texture::capabilities::render_target
		)
	)
		throw
			sge::renderer::exception(
				FCPPT_TEXT("renderer::target_from_texture() called with a texture ")
				FCPPT_TEXT("that is not a render target!")
			);

	sge::renderer::target::offscreen_unique_ptr target(
		_device.create_target()
	);

	target->color_surface(
		sge::renderer::color_buffer::optional_surface_ref(
			fcppt::reference_to_base<
				sge::renderer::color_buffer::surface
			>(
				fcppt::make_ref(
					_texture.level(
						sge::renderer::texture::mipmap::level(
							0u
						)
					)
				)
			)
		),
		sge::renderer::target::surface_index(
			0u
		)
	);

	target->viewport(
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect(
				fcppt::math::vector::null<
					sge::renderer::pixel_rect::vector
				>(),
				fcppt::math::dim::structure_cast<
					sge::renderer::pixel_rect::dim,
					fcppt::cast::to_signed_fun
				>(
					fcppt::math::dim::structure_cast<
						sge::renderer::screen_size,
						fcppt::cast::size_fun
					>(
						_texture.size()
					)
				)
			)
		)
	);

	return
		target;
}
