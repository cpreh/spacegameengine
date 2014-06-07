/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/texture/next_power_of_2.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <sge/texture/wrap_npot.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::texture::part_unique_ptr
sge::texture::wrap_npot(
	sge::renderer::device::core &_device,
	sge::renderer::texture::planar_parameters const &_parameters
)
{
	return
		sge::texture::part_unique_ptr(
			fcppt::make_unique_ptr<
				sge::texture::part_raw_ptr
			>(
				_device.create_planar_texture(
					sge::renderer::texture::planar_parameters(
						_device.caps().non_power_of_2_textures().get()
						?
							_parameters.size()
						:
							sge::texture::next_power_of_2(
								_parameters.size()
							)
						,
						_parameters.format(),
						_parameters.mipmap(),
						_parameters.resource_flags(),
						_parameters.capabilities()
					)
				),
				sge::renderer::lock_rect(
					sge::renderer::lock_rect::vector::null(),
					_parameters.size()
				)
			)
		);
}
