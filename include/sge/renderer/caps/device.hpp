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


#ifndef SGE_RENDERER_CAPS_DEVICE_HPP_INCLUDED
#define SGE_RENDERER_CAPS_DEVICE_HPP_INCLUDED

#include <sge/renderer/adapter.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/caps/clip_plane_indices.hpp>
#include <sge/renderer/caps/description.hpp>
#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/caps/driver_name.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/max_anisotropy.hpp>
#include <sge/renderer/caps/max_texture_size.hpp>
#include <sge/renderer/caps/max_volume_texture_extent.hpp>
#include <sge/renderer/caps/normalized_cvv.hpp>
#include <sge/renderer/caps/render_target_inverted.hpp>
#include <sge/renderer/caps/render_target_supported.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace caps
{

/**
\brief Provides information about an sge::renderer::device

This class provides information about an sge::renderer::device such as the
driver's name, if render targets are supported and certain limitations. It is
important that all the limitations are honored, otherwise functions may have
undefined behavior.
*/
class device
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	/**
	 * \brief Constructs a capabilities object
	 *
	 * This function is for internal use only
	*/
	SGE_RENDERER_SYMBOL
	device(
		sge::renderer::adapter,
		sge::renderer::caps::driver_name const &,
		sge::renderer::caps::description const &,
		sge::renderer::caps::normalized_cvv const &,
		sge::renderer::caps::max_texture_size const &,
		sge::renderer::caps::max_volume_texture_extent,
		sge::renderer::caps::max_anisotropy,
		sge::renderer::caps::render_target_supported,
		sge::renderer::caps::render_target_inverted,
		sge::renderer::caps::clip_plane_indices,
		sge::renderer::caps::light_indices,
		sge::renderer::caps::texture_stages,
		sge::renderer::caps::target_surface_indices
	);

	SGE_RENDERER_SYMBOL
	~device();

	/**
	 * \brief Returns the adapter the renderer::device represents
	 *
	 * This value is the same as has been specified in renderer::parameters
	 * when creating the device.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::adapter const
	adapter() const;

	/**
	 * \brief Returns the driver's name
	 *
	 * A string representation of the driver name.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::driver_name const &
	driver_name() const;

	/**
	 * \brief Returns a description of the renderer::device
	 *
	 * This usually contains the vendor or the model name of the graphics
	 * card.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::description const &
	description() const;

	/**
	 * \brief Returns true if the canonical view volume (CVV) is the unit cube [-1,1]^3
	 *
	 * The canonical view volume is the volume into which the visible
	 * vertices are projected. If you're using a perspective
	 * projection matrix, the view frustum is transformed to the
	 * CVV, perserving the objects' depth order.
	 *
	 * OpenGL and DirectX have different CVVs. OpenGL wants the
	 * vertices projected into the unit cube [-1,1]^3 (e.g. it has a
	 * normalized CVV), DirectX has "half a unit cube". The Z value is
	 * in [0,1] while the X and Y values are in [-1,1].
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::normalized_cvv const &
	normalized_cvv() const;

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
	sge::renderer::caps::max_texture_size const &
	max_texture_size() const;

	/**
	 * \brief Returns the maximum size of a volume texture's side
	 *
	 * This is the maximum size for each side of a volume texture.
	 * Creating anything bigger than that is not supported.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::max_volume_texture_extent const
	max_volume_texture_extent() const;

	/**
	 * \brief Returns the maximum supported anisotropy
	 *
	 * This is the maximum anisotropy supported for anisotropic texture
	 * filters. If this is 0, no anisotropic filtering is supported.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::max_anisotropy const
	max_anisotropy() const;

	/**
	 * \brief Returns if render targets are supported
	 *
	 * If no render targets are supported, then you cannot use
	 * renderer::device::create_target.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::render_target_supported const
	render_target_supported() const;

	/**
	 * \brief Returns if render targets are inverted
	 *
	 * If render targets are not supported, this value has no meaning.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::render_target_inverted const
	render_target_inverted() const;

	/**
	 * \brief Returns the number of clip planes
	 *
	 * Valid clip plane indices range from 0 to the returned value - 1. If
	 * this value is 0, no clip planes are supported.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::clip_plane_indices const
	clip_plane_indices() const;

	/**
	 * \brief Returns the number of light indices
	 *
	 * Valid light indices range from 0 to the returned value - 1. If this
	 * value is 0, no lights are supported.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::light_indices const
	light_indices() const;

	/**
	 * \brief Returns the number of texture stages
	 *
	 * Valid texture stages range from 0 to the returned value - 1. The
	 * 0th texture stage is always supported.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::texture_stages const
	texture_stages() const;

	/**
	\brief Returns the number of target surfaces

	Valid target surface indices range from 0 to the returned value - 1.
	The 0th index is always supported.
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::caps::target_surface_indices const
	target_surfaces() const;
private:
	sge::renderer::adapter const adapter_;

	sge::renderer::caps::driver_name const driver_name_;

	sge::renderer::caps::description const description_;

	sge::renderer::caps::normalized_cvv const normalized_cvv_;

	sge::renderer::caps::max_texture_size const max_texture_size_;

	sge::renderer::caps::max_volume_texture_extent const max_volume_texture_extent_;

	sge::renderer::caps::max_anisotropy const max_anisotropy_;

	sge::renderer::caps::render_target_supported const render_target_supported_;

	sge::renderer::caps::render_target_inverted const render_target_inverted_;

	sge::renderer::caps::clip_plane_indices const clip_plane_indices_;

	sge::renderer::caps::light_indices const light_indices_;

	sge::renderer::caps::texture_stages const texture_stages_;

	sge::renderer::caps::target_surface_indices const target_surfaces_;
};

}
}
}

#endif
