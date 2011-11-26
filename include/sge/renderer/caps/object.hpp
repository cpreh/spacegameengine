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

/**
 * \brief Provides a description of a renderer::device
 *
 * This class provides descriptions of a renderer::device such as the driver's
 * name, the preferred texture format and certain limitations. Not violating
 * the limitations is important. Certain functions have undefined behaviour or
 * throw exceptions the limitations are violated.
*/
class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	/**
	 * \brief Constructs a capabilities object
	 *
	 * This function is for internal use only
	*/
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

	/**
	 * \brief Returns the adapter the renderer::device represents
	 *
	 * This value is the same as has been specified in renderer::parameters
	 * when creating the device.
	*/
	SGE_RENDERER_SYMBOL
	renderer::adapter const
	adapter() const;

	/**
	 * \brief Returns the driver's name
	 *
	 * A string representation of the driver name.
	*/
	SGE_RENDERER_SYMBOL
	caps::driver_name const &
	driver_name() const;

	/**
	 * \brief Returns a description of the renderer::device
	 *
	 * This usually contains the vendor or the model name of the graphics
	 * card.
	*/
	SGE_RENDERER_SYMBOL
	caps::description const &
	description() const;

	/**
	 * \brief Returns the maximum size of a planar texture
	 *
	 * This is the maximum size for a renderer::texture::planar. Creating
	 * anything bigger in any of the dimensions (width or height) is not
	 * supported. This value is highly dependant on your graphics drivers
	 * and your graphics card. Typical values might be (4096,4096)
	 * or (8192,8192).
	*/
	SGE_RENDERER_SYMBOL
	caps::max_texture_size const &
	max_texture_size() const;

	/**
	 * \brief Returns the maximum size of a volume texture's side
	 *
	 * This is the maximum size for each side of a volume texture.
	 * Creating anything bigger than that is not supported.
	*/
	SGE_RENDERER_SYMBOL
	caps::max_volume_texture_extent const
	max_volume_texture_extent() const;

	/**
	 * \brief Returns the maximum supported anisotropy
	 *
	 * This is the maximum anisotropy supported for anisotropic texture
	 * filters. If this is 0, no anisotropic filtering is supported.
	*/
	SGE_RENDERER_SYMBOL
	caps::max_anisotropy const
	max_anisotropy() const;

	/**
	 * \brief Returns if render target are supported
	 *
	 * If no render targets are supported, then you cannot use
	 * renderer::device::create_target.
	*/
	SGE_RENDERER_SYMBOL
	caps::render_target_supported const
	render_target_supported() const;

	/**
	 * \brief Returns if GLSL is supported
	 *
	 * If GLSL is not supported, you cannot create glsl shaders or
	 * programs.
	*/
	SGE_RENDERER_SYMBOL
	caps::glsl_supported const
	glsl_supported() const;

	/**
	 * \brief Returns the preferred texture format
	 *
	 * The preferred texture format is the format the driver thinks is the
	 * fastest. Usually, graphics cards can only handle specific formats
	 * (like BGR(A) for nvidia) well, and have to convert others.
	 * Conversions are usually done by the graphics card itself and not in
	 * the driver, so the performance impact might not be that huge if non
	 * preferred formats are used.
	*/
	SGE_RENDERER_SYMBOL
	caps::preferred_texture_format const
	preferred_texture_format() const;

	/**
	 * \brief Returns the number of clip planes
	 *
	 * Valid clip plane indices range from 0 to the returned value - 1. If
	 * this value is 0, no clip planes are supported.
	*/
	SGE_RENDERER_SYMBOL
	caps::clip_plane_indices const
	clip_plane_indices() const;

	/**
	 * \brief Returns the number of light indices
	 *
	 * Valid light indices range from 0 to the returned value - 1. If this
	 * value is 0, no lights are supported.
	*/
	SGE_RENDERER_SYMBOL
	caps::light_indices const
	light_indices() const;

	/**
	 * \brief Returns the number of texture stages
	 *
	 * Valid texture stages range from 0 to the returned value - 1. The
	 * 0th texture stage is always supported.
	*/
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
