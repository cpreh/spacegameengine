/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/caps/driver_name.hpp>
#include <sge/renderer/caps/glsl_supported.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/max_anisotropy.hpp>
#include <sge/renderer/caps/max_texture_size.hpp>
#include <sge/renderer/caps/max_volume_texture_extent.hpp>
#include <sge/renderer/caps/object.hpp>
#include <sge/renderer/caps/preferred_texture_format.hpp>
#include <sge/renderer/caps/render_target_supported.hpp>
#include <sge/renderer/caps/texture_stages.hpp>


sge::renderer::caps::object::object(
	renderer::adapter const _adapter,
	caps::driver_name const &_driver_name,
	caps::description const &_description,
	caps::max_texture_size const &_max_texture_size,
	caps::max_volume_texture_extent const _max_volume_texture_extent,
	caps::max_anisotropy const _max_anisotropy,
	caps::render_target_supported const _render_target_supported,
	caps::glsl_supported const _glsl_supported,
	caps::preferred_texture_format const _preferred_texture_format,
	caps::clip_plane_indices const _clip_plane_indices,
	caps::light_indices const _light_indices,
	caps::texture_stages const _texture_stages
)
:
	adapter_(
		_adapter
	),
	driver_name_(
		_driver_name
	),
	description_(
		_description
	),
	max_texture_size_(
		_max_texture_size
	),
	max_volume_texture_extent_(
		_max_volume_texture_extent
	),
	max_anisotropy_(
		_max_anisotropy
	),
	render_target_supported_(
		_render_target_supported
	),
	glsl_supported_(
		_glsl_supported
	),
	preferred_texture_format_(
		_preferred_texture_format
	),
	clip_plane_indices_(
		_clip_plane_indices
	),
	light_indices_(
		_light_indices
	),
	texture_stages_(
		_texture_stages
	)
{
}

sge::renderer::caps::object::~object()
{
}

sge::renderer::adapter const
sge::renderer::caps::object::adapter() const
{
	return adapter_;
}

sge::renderer::caps::driver_name const &
sge::renderer::caps::object::driver_name() const
{
	return driver_name_;
}

sge::renderer::caps::description const &
sge::renderer::caps::object::description() const
{
	return description_;
}

sge::renderer::caps::max_texture_size const &
sge::renderer::caps::object::max_texture_size() const
{
	return max_texture_size_;
}

sge::renderer::caps::max_volume_texture_extent const
sge::renderer::caps::object::max_volume_texture_extent() const
{
	return max_volume_texture_extent_;
}

sge::renderer::caps::max_anisotropy const
sge::renderer::caps::object::max_anisotropy() const
{
	return max_anisotropy_;
}

sge::renderer::caps::render_target_supported const
sge::renderer::caps::object::render_target_supported() const
{
	return render_target_supported_;
}

sge::renderer::caps::glsl_supported const
sge::renderer::caps::object::glsl_supported() const
{
	return glsl_supported_;
}

sge::renderer::caps::preferred_texture_format const
sge::renderer::caps::object::preferred_texture_format() const
{
	return preferred_texture_format_;
}

sge::renderer::caps::clip_plane_indices const
sge::renderer::caps::object::clip_plane_indices() const
{
	return clip_plane_indices_;
}

sge::renderer::caps::light_indices const
sge::renderer::caps::object::light_indices() const
{
	return light_indices_;
}

sge::renderer::caps::texture_stages const
sge::renderer::caps::object::texture_stages() const
{
	return texture_stages_;
}
