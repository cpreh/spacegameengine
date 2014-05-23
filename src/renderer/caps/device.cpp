/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/caps/clip_plane_indices.hpp>
#include <sge/renderer/caps/description.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/driver_name.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/max_anisotropy.hpp>
#include <sge/renderer/caps/max_texture_size.hpp>
#include <sge/renderer/caps/max_volume_texture_extent.hpp>
#include <sge/renderer/caps/non_power_of_2_textures.hpp>
#include <sge/renderer/caps/normalized_cvv.hpp>
#include <sge/renderer/caps/render_target_inverted.hpp>
#include <sge/renderer/caps/render_target_supported.hpp>
#include <sge/renderer/caps/srgb_framebuffer.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/caps/texture_stages.hpp>


sge::renderer::caps::device::device(
	sge::renderer::caps::driver_name const &_driver_name,
	sge::renderer::caps::description const &_description,
	sge::renderer::caps::normalized_cvv const &_normalized_cvv,
	sge::renderer::caps::max_texture_size const &_max_texture_size,
	sge::renderer::caps::max_volume_texture_extent const _max_volume_texture_extent,
	sge::renderer::caps::non_power_of_2_textures const _non_power_of_2_textures,
	sge::renderer::caps::max_anisotropy const _max_anisotropy,
	sge::renderer::caps::render_target_supported const _render_target_supported,
	sge::renderer::caps::render_target_inverted const _render_target_inverted,
	sge::renderer::caps::clip_plane_indices const _clip_plane_indices,
	sge::renderer::caps::light_indices const _light_indices,
	sge::renderer::caps::texture_stages const _texture_stages,
	sge::renderer::caps::target_surface_indices const _target_surfaces,
	sge::renderer::caps::srgb_framebuffer const _srgb_framebuffer
)
:
	driver_name_(
		_driver_name
	),
	description_(
		_description
	),
	normalized_cvv_(
		_normalized_cvv
	),
	max_texture_size_(
		_max_texture_size
	),
	max_volume_texture_extent_(
		_max_volume_texture_extent
	),
	non_power_of_2_textures_(
		_non_power_of_2_textures
	),
	max_anisotropy_(
		_max_anisotropy
	),
	render_target_supported_(
		_render_target_supported
	),
	render_target_inverted_(
		_render_target_inverted
	),
	clip_plane_indices_(
		_clip_plane_indices
	),
	light_indices_(
		_light_indices
	),
	texture_stages_(
		_texture_stages
	),
	target_surfaces_(
		_target_surfaces
	),
	srgb_framebuffer_(
		_srgb_framebuffer
	)
{
}

sge::renderer::caps::driver_name const &
sge::renderer::caps::device::driver_name() const
{
	return driver_name_;
}

sge::renderer::caps::description const &
sge::renderer::caps::device::description() const
{
	return description_;
}

sge::renderer::caps::normalized_cvv const &
sge::renderer::caps::device::normalized_cvv() const
{
	return normalized_cvv_;
}

sge::renderer::caps::max_texture_size const &
sge::renderer::caps::device::max_texture_size() const
{
	return max_texture_size_;
}

sge::renderer::caps::max_volume_texture_extent const
sge::renderer::caps::device::max_volume_texture_extent() const
{
	return max_volume_texture_extent_;
}

sge::renderer::caps::non_power_of_2_textures const
sge::renderer::caps::device::non_power_of_2_textures() const
{
	return non_power_of_2_textures_;
}

sge::renderer::caps::max_anisotropy const
sge::renderer::caps::device::max_anisotropy() const
{
	return max_anisotropy_;
}

sge::renderer::caps::render_target_supported const
sge::renderer::caps::device::render_target_supported() const
{
	return render_target_supported_;
}

sge::renderer::caps::render_target_inverted const
sge::renderer::caps::device::render_target_inverted() const
{
	return render_target_inverted_;
}

sge::renderer::caps::clip_plane_indices const
sge::renderer::caps::device::clip_plane_indices() const
{
	return clip_plane_indices_;
}

sge::renderer::caps::light_indices const
sge::renderer::caps::device::light_indices() const
{
	return light_indices_;
}

sge::renderer::caps::texture_stages const
sge::renderer::caps::device::texture_stages() const
{
	return texture_stages_;
}

sge::renderer::caps::target_surface_indices const
sge::renderer::caps::device::target_surfaces() const
{
	return target_surfaces_;
}

sge::renderer::caps::srgb_framebuffer const
sge::renderer::caps::device::srgb_framebuffer() const
{
	return srgb_framebuffer_;
}
