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
			_renderer,
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
			result->texture(),
			sge::renderer::lock_mode::writeonly
		);

		_text.render(
			lock.value()
		);
	}

	return
		result;
}


