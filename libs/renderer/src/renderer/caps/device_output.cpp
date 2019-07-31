//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
