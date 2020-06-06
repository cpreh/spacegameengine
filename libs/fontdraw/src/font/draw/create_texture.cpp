//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/rect.hpp>
#include <sge/font/text.hpp>
#include <sge/font/draw/create_texture.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <sge/texture/wrap_npot.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_unsigned.hpp>


sge::texture::part_unique_ptr
sge::font::draw::create_texture(
	sge::renderer::device::core &_renderer,
	sge::font::text &_text,
	sge::image::color::format const _color_format,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
{
	sge::texture::part_unique_ptr result(
		sge::texture::wrap_npot(
			// TODO
			fcppt::make_ref(
				_renderer
			),
			sge::renderer::texture::planar_parameters(
				fcppt::math::dim::structure_cast<
					sge::renderer::dim2,
					fcppt::cast::size_fun
				>(
					fcppt::math::dim::to_unsigned(
						_text.rect().size()
					)
				),
				sge::renderer::texture::color_format(
					_color_format,
					_emulate_srgb
				),
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::capabilities_field::null()
			)
		)
	);

	if(
		fcppt::math::dim::contents(
			result->size()
		)
		!=
		0u
	)
	{
		sge::renderer::texture::scoped_planar_lock const lock(
			fcppt::make_ref(
				result->texture()
			),
			sge::renderer::lock_mode::writeonly
		);

		_text.render(
			lock.value()
		);
	}

	return
		result;
}


