/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image3d/dim.hpp>
#include <sge/image3d/algorithm/copy_and_convert.hpp>
#include <sge/image3d/view/const_object_fwd.hpp>
#include <sge/image3d/view/format.hpp>
#include <sge/image3d/view/size.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/create_volume_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/scoped_volume_lock.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::texture::volume_unique_ptr
sge::renderer::texture::create_volume_from_view(
	sge::renderer::device::core &_renderer,
	sge::image3d::view::const_object const &_view,
	sge::renderer::texture::mipmap::object const &_mipmap,
	sge::renderer::resource_flags_field const &_resource_flags,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
{
	sge::renderer::texture::volume_unique_ptr tex(
		_renderer.create_volume_texture(
			sge::renderer::texture::volume_parameters(
				sge::image3d::view::size(
					_view
				),
				sge::renderer::texture::color_format(
					sge::image3d::view::format(
						_view
					),
					_emulate_srgb
				),
				_mipmap,
				_resource_flags,
				sge::renderer::texture::capabilities_field::null()
			)
		)
	);

	sge::renderer::texture::scoped_volume_lock const lock(
		*tex,
		sge::renderer::lock_mode::writeonly
	);

	sge::image3d::algorithm::copy_and_convert(
		_view,
		lock.value(),
		sge::image::algorithm::may_overlap::no
	);

	return
		std::move(
			tex
		);
}
