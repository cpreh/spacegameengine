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


#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/device_output.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/math/dim/output.hpp>


fcppt::io::ostream &
sge::renderer::caps::operator<<(
	fcppt::io::ostream &_stream,
	sge::renderer::caps::device const &_caps
)
{
	return
		_stream
		<< FCPPT_TEXT("caps: driver_name = \"")
		<< _caps.driver_name()
		<< FCPPT_TEXT("\", description = \"")
		<< _caps.description()
		<< FCPPT_TEXT("\", normalized_cvv = ")
		<< _caps.normalized_cvv()
		<< FCPPT_TEXT(", max_texture_size = ")
		<< _caps.max_texture_size()
		<< FCPPT_TEXT(", max_volume_texture_extent = ")
		<< _caps.max_volume_texture_extent()
		<< FCPPT_TEXT(", non_power_of_2_textures = ")
		<< _caps.non_power_of_2_textures()
		<< FCPPT_TEXT(", max_anisotropy = ")
		<< _caps.max_anisotropy()
		<< FCPPT_TEXT(", render_target_supported = ")
		<< _caps.render_target_supported()
		<< FCPPT_TEXT(", render_target_inverted = ")
		<< _caps.render_target_inverted()
		<< FCPPT_TEXT(", clip_plane_indices = ")
		<< _caps.clip_plane_indices()
		<< FCPPT_TEXT(", light_indices = ")
		<< _caps.light_indices()
		<< FCPPT_TEXT(", texture_stages = ")
		<< _caps.texture_stages()
		<< FCPPT_TEXT(", target_surfaces = ")
		<< _caps.target_surfaces()
		<< FCPPT_TEXT(", srgb_framebuffer = ")
		<< _caps.srgb_framebuffer()
		;
}
