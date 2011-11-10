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


#ifndef SGE_RENDERER_CAPS_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_CAPS_OBJECT_HPP_INCLUDED

#include <sge/renderer/adapter.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/caps/clip_plane_indices.hpp>
#include <sge/renderer/caps/description.hpp>
#include <sge/renderer/caps/driver_name.hpp>
#include <sge/renderer/caps/glsl_supported.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/max_anisotropy.hpp>
#include <sge/renderer/caps/max_texture_size.hpp>
#include <sge/renderer/caps/max_volume_texture_extent.hpp>
#include <sge/renderer/caps/object_fwd.hpp>
#include <sge/renderer/caps/preferred_texture_format.hpp>
#include <sge/renderer/caps/render_target_supported.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace caps
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_RENDERER_SYMBOL
	object(
		renderer::adapter,
		caps::driver_name const &,
		caps::description const &,
		caps::max_texture_size const &,
		caps::max_volume_texture_extent,
		caps::max_anisotropy,
		caps::render_target_supported,
		caps::glsl_supported,
		caps::preferred_texture_format,
		caps::clip_plane_indices,
		caps::light_indices,
		caps::texture_stages
	);

	SGE_RENDERER_SYMBOL
	~object();

	SGE_RENDERER_SYMBOL
	renderer::adapter const
	adapter() const;

	SGE_RENDERER_SYMBOL
	caps::driver_name const &
	driver_name() const;

	SGE_RENDERER_SYMBOL
	caps::description const &
	description() const;

	SGE_RENDERER_SYMBOL
	caps::max_texture_size const &
	max_texture_size() const;

	SGE_RENDERER_SYMBOL
	caps::max_volume_texture_extent const
	max_volume_texture_extent() const;

	SGE_RENDERER_SYMBOL
	caps::max_anisotropy const
	max_anisotropy() const;

	SGE_RENDERER_SYMBOL
	caps::render_target_supported const
	render_target_supported() const;

	SGE_RENDERER_SYMBOL
	caps::glsl_supported const
	glsl_supported() const;

	SGE_RENDERER_SYMBOL
	caps::preferred_texture_format const
	preferred_texture_format() const;

	SGE_RENDERER_SYMBOL
	caps::clip_plane_indices const
	clip_plane_indices() const;

	SGE_RENDERER_SYMBOL
	caps::light_indices const
	light_indices() const;

	SGE_RENDERER_SYMBOL
	caps::texture_stages const
	texture_stages() const;
private:
	renderer::adapter const adapter_;

	caps::driver_name const driver_name_;

	caps::description const description_;

	caps::max_texture_size const max_texture_size_;

	caps::max_volume_texture_extent const max_volume_texture_extent_;

	caps::max_anisotropy const max_anisotropy_;

	caps::render_target_supported const render_target_supported_;

	caps::glsl_supported const glsl_supported_;

	caps::preferred_texture_format const preferred_texture_format_;

	caps::clip_plane_indices const clip_plane_indices_;

	caps::light_indices const light_indices_;

	caps::texture_stages const texture_stages_;
};

}
}
}

#endif
