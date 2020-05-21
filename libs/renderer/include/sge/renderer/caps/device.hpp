//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CAPS_DEVICE_HPP_INCLUDED
#define SGE_RENDERER_CAPS_DEVICE_HPP_INCLUDED

#include <sge/renderer/caps/clip_plane_indices.hpp>
#include <sge/renderer/caps/description.hpp>
#include <sge/renderer/caps/device_fwd.hpp>
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
#include <sge/renderer/detail/symbol.hpp>


namespace sge
{
namespace renderer
{
namespace caps
{

/**
\brief Provides information about an sge::renderer::device

\ingroup sge_renderer

This class provides information about an sge::renderer::device such as the
driver's name, if render targets are supported and certain limitations. It is
important that all the limitations are honored, otherwise functions may have
undefined behavior.
*/
class device
{
public:
	/**
	\brief Constructs a capabilities object

	This function is for internal use only
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	device(
		sge::renderer::caps::driver_name &&,
		sge::renderer::caps::description &&,
		sge::renderer::caps::normalized_cvv,
		sge::renderer::caps::max_texture_size,
		sge::renderer::caps::max_volume_texture_extent,
		sge::renderer::caps::non_power_of_2_textures,
		sge::renderer::caps::max_anisotropy,
		sge::renderer::caps::render_target_supported,
		sge::renderer::caps::render_target_inverted,
		sge::renderer::caps::clip_plane_indices,
		sge::renderer::caps::light_indices,
		sge::renderer::caps::texture_stages,
		sge::renderer::caps::target_surface_indices,
		sge::renderer::caps::srgb_framebuffer
	);

	/**
	\brief Returns the driver's name

	A string representation of the driver name.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::driver_name const &
	driver_name() const;

	/**
	\brief Returns a description of the renderer::device

	This usually contains the vendor or the model name of the graphics
	card.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::description const &
	description() const;

	/**
	\brief Returns true if the canonical view volume (CVV) is the unit cube
	[-1,1]^3

	The canonical view volume is the volume into which the visible vertices
	are projected. If you're using a perspective projection matrix, the
	view frustum is transformed to the CVV, perserving the objects' depth
	order.

	OpenGL and DirectX have different CVVs. OpenGL wants the vertices
	projected into the unit cube [-1,1]^3 (e.g. it has a normalized CVV),
	DirectX has "half a unit cube". The Z value is in [0,1] while the X and
	Y values are in [-1,1].
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::normalized_cvv
	normalized_cvv() const;

	/**
	\brief Returns the maximum size of a planar texture

	This is the maximum size for an sge::renderer::texture::planar.
	Creating anything bigger in any of the dimensions (width or height) is
	not supported. This value is highly dependant on your graphics drivers
	and your graphics card. Typical values might be (4096,4096) or
	(8192,8192).
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::max_texture_size const &
	max_texture_size() const;

	/**
	\brief Returns the maximum size of a volume texture's side

	This is the maximum size for each side of a volume texture. Creating
	anything bigger than that is not supported.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::max_volume_texture_extent
	max_volume_texture_extent() const;

	/**
	\brief Returns if non power of 2 textures are supported

	Older hardware or environments with limited capabilities (like OpenGL
	in a virtual machine, over vnc or rdesktop, etc.) might not support non
	power of 2 textures.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::non_power_of_2_textures
	non_power_of_2_textures() const;

	/**
	\brief Returns the maximum supported anisotropy

	This is the maximum anisotropy supported for anisotropic texture
	filters. If this is 0, no anisotropic filtering is supported.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::max_anisotropy
	max_anisotropy() const;

	/**
	\brief Returns if render targets are supported

	If no render targets are supported, then you cannot use
	sge::renderer::device::create_target.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::render_target_supported
	render_target_supported() const;

	/**
	\brief Returns if render targets are inverted

	An inverted render target means that the buffers are flipped
	vertically. If render targets are not supported, this value has no
	meaning.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::render_target_inverted
	render_target_inverted() const;

	/**
	\brief Returns the number of clip planes

	Valid clip plane indices range from 0 to the returned value - 1. If
	this value is 0, no clip planes are supported.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::clip_plane_indices
	clip_plane_indices() const;

	/**
	\brief Returns the number of light indices

	Valid light indices range from 0 to the returned value - 1. If this
	value is 0, no lights are supported.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::light_indices
	light_indices() const;

	/**
	\brief Returns the number of texture stages

	Valid texture stages range from 0 to the returned value - 1. The 0th
	texture stage is always supported.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::texture_stages
	texture_stages() const;

	/**
	\brief Returns the number of target surfaces

	Valid target surface indices range from 0 to the returned value - 1.
	The 0th index is always supported.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::target_surface_indices
	target_surfaces() const;

	/**
	\brief Returns whether srgb framebuffers are supported

	This is required for creating a pixel format with srgb support.
	*/
	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::caps::srgb_framebuffer
	srgb_framebuffer() const;
private:
	sge::renderer::caps::driver_name driver_name_;

	sge::renderer::caps::description description_;

	sge::renderer::caps::normalized_cvv normalized_cvv_;

	sge::renderer::caps::max_texture_size max_texture_size_;

	sge::renderer::caps::max_volume_texture_extent max_volume_texture_extent_;

	sge::renderer::caps::non_power_of_2_textures non_power_of_2_textures_;

	sge::renderer::caps::max_anisotropy max_anisotropy_;

	sge::renderer::caps::render_target_supported render_target_supported_;

	sge::renderer::caps::render_target_inverted render_target_inverted_;

	sge::renderer::caps::clip_plane_indices clip_plane_indices_;

	sge::renderer::caps::light_indices light_indices_;

	sge::renderer::caps::texture_stages texture_stages_;

	sge::renderer::caps::target_surface_indices target_surfaces_;

	sge::renderer::caps::srgb_framebuffer srgb_framebuffer_;
};

}
}
}

#endif
