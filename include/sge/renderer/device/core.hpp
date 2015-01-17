/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_DEVICE_CORE_HPP_INCLUDED
#define SGE_RENDERER_DEVICE_CORE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/caps/device_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/parameters_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/parameters_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/target/onscreen_fwd.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_unique_ptr.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_unique_ptr.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer_parameters_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/profile/shader_type_fwd.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#endif


namespace sge
{
namespace renderer
{
namespace device
{

/**
\brief Provides core functionality (without ffp support)

The core device provides creation of resources and a core rendering context.
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL core
{
	FCPPT_NONCOPYABLE(
		core
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	core();
public:
	/**
	\brief Begins the rendering operation

	To be able to call device::render_indexed or device::render_nonindexed,
	this function must be called first. To end the rendering process and
	present it, use device::end_rendering.

	\param target The render target to use, which can either be
	device::onscreen_target or an offscreen target.

	\see sge::renderer::scoped_block

	\warning The behavior is undefined if this function is called more than
	once before a call to device::end_rendering
	*/
	virtual
	sge::renderer::context::core_unique_ptr
	begin_rendering(
		sge::renderer::target::base &target
	) = 0;

	/**
	\brief Ends the rendering operation

	Use this function to present the rendered scene which has been rendered
	using \a context.

	\param context The render context obtained from device::begin_rendering

	\warning The behavior is undefined if begin_rendering wasn't called
	*/
	virtual
	void
	end_rendering(
		sge::renderer::context::core &context
	) = 0;

	/**
	\brief Creates a render target

	Creates an empty render target.

	\return A unique pointer to the created target

	\see sge::renderer::caps::object::render_target_supported

	\warning The behavior is undefined if
	sge::renderer::caps::object::render_target_supported is false
	*/
	virtual
	sge::renderer::target::offscreen_unique_ptr
	create_target() = 0;

	/**
	\brief Creates a planar texture

	Creates a planar texture from \a parameters. Initially, the contents
	of the texture are undefined.

	\param parameters The parameters class for the planar texture, using
	sge::renderer::dim2 as its dimensions and sge::image::color::format as
	its format

	\return A unique pointer to the created planar texture

	\see sge::renderer::caps::object::max_texture_size

	\throw sge::renderer::exception if anything goes wrong
	*/
	virtual
	sge::renderer::texture::planar_unique_ptr
	create_planar_texture(
		sge::renderer::texture::planar_parameters const &parameters
	) = 0;

	/**
	\brief Creates a depth stencil texture

	Creates a depth stencil texture from \a parameters.
	Initially, the contents of the texture are undefined.

	\param parameters The parameters class for the depth stencil texture,
	using sge::renderer::dim2 as its dimensions and
	sge::renderer::depth_stencil_format as its format

	\return A unique pointer to the created depth stencil texture

	\see sge::renderer::caps::object::max_texture_size

	\throw sge::renderer::exception if anything goes wrong
	*/
	virtual
	sge::renderer::texture::depth_stencil_unique_ptr
	create_depth_stencil_texture(
		sge::renderer::texture::depth_stencil_parameters const &parameters
	) = 0;

	/**
	\brief Creates a depth stencil surface

	Creates a depth stencil surface with dimension \a size and format \a
	format. Initially, the contents of the surface are undefined.

	\param parameters The parameters for the surface, including its
	format and size

	\return A unique pointer to the created depth stencil surface

	\throw sge::renderer::exception if anything goes wrong
	*/
	virtual
	sge::renderer::depth_stencil_buffer::surface_unique_ptr
	create_depth_stencil_surface(
		sge::renderer::depth_stencil_buffer::surface_parameters const &parameters
	) = 0;

	/**
	\brief Creates a volume texture

	Creates a volume texture from \a parameters.  Initially, the contents
	of the texture are undefined.

	\param parameters The parameters class for the depth stencil texture,
	using sge::renderer::dim3 as its dimensions and
	sge::image::color::format as its format

	\return A unique pointer to the created volume texture

	\see sge::renderer::caps::object::max_volume_texture_extent

	\throw sge::renderer::exception if anything goes wrong
	*/
	virtual
	sge::renderer::texture::volume_unique_ptr
	create_volume_texture(
		sge::renderer::texture::volume_parameters const &parameters
	) = 0;

	/**
	\brief Creates a cube texture

	Creates a cube texture from \a parameters. Initially, the contents of
	the texture are undefined.

	\param parameters The parameters class for the depth stencil
	texture, using sge::renderer::size_type as its dimensions and
	sge::image::color::format as its format

	\return A unique pointer to the created cube texture

	\throw sge::renderer::exception if anything goes wrong
	*/
	virtual
	sge::renderer::texture::cube_unique_ptr
	create_cube_texture(
		sge::renderer::texture::cube_parameters const &parameters
	) = 0;

	/**
	\brief Creates a vertex declaration

	Creates a vertex declaration described by \a parameters

	\param parameters Describes the vertex declaration

	\return A unique pointer to the created vertex declaration

	\throw sge::renderer::exception if anything goes wrong
	*/
	virtual
	sge::renderer::vertex::declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::vertex::declaration_parameters const &parameters
	) = 0;

	/**
	\brief Creates a vertex buffer

	Creates a vertex buffer that is going to hold data described by \a
	parameters.

	\param parameters Describes the vertex buffer

	\return A unique pointer to the created vertex buffer

	\throw sge::renderer::exception if anything goes wrong
	*/
	virtual
	sge::renderer::vertex::buffer_unique_ptr
	create_vertex_buffer(
		sge::renderer::vertex::buffer_parameters const &parameters
	) = 0;

	/**
	\brief Creates an index buffer

	Creates an index buffer describes by \a parameters Initially, the
	contents of the buffer are undefined.

	\return A unique pointer to the created index buffer

	\throw sge::renderer::exception if anything goes wrong
	*/
	virtual
	sge::renderer::index::buffer_unique_ptr
	create_index_buffer(
		sge::renderer::index::buffer_parameters const &
	) = 0;

	virtual
	sge::renderer::occlusion_query::object_unique_ptr
	create_occlusion_query() = 0;

	virtual
	sge::renderer::state::core::blend::object_unique_ptr
	create_blend_state(
		sge::renderer::state::core::blend::parameters const &
	) = 0;

	virtual
	sge::renderer::state::core::depth_stencil::object_unique_ptr
	create_depth_stencil_state(
		sge::renderer::state::core::depth_stencil::parameters const &
	) = 0;

	virtual
	sge::renderer::state::core::rasterizer::object_unique_ptr
	create_rasterizer_state(
		sge::renderer::state::core::rasterizer::parameters const &
	) = 0;

	virtual
	sge::renderer::state::core::sampler::object_unique_ptr
	create_sampler_state(
		sge::renderer::state::core::sampler::parameters const &
	) = 0;

#if defined(SGE_RENDERER_HAVE_CG)
	virtual
	sge::cg::profile::object
	create_cg_profile(
		sge::cg::profile::shader_type
	) = 0;

	virtual
	sge::cg::program::compile_options
	cg_compile_options(
		sge::cg::context::object const &,
		sge::cg::profile::object const &
	) = 0;

	virtual
	sge::renderer::cg::loaded_program_unique_ptr
	load_cg_program(
		sge::cg::program::object &
	) = 0;

	virtual
	sge::renderer::cg::loaded_texture_unique_ptr
	load_cg_texture(
		sge::cg::parameter::object const &,
		sge::renderer::texture::base &
	) = 0;

	virtual
	sge::cg::program::source
	transform_cg_vertex_program(
		sge::renderer::vertex::declaration const &,
		sge::cg::program::source const &
	) = 0;
#endif

	/**
	\brief Returns the onscreen target

	A device always has an onscreen target even though another render
	target has been set.
	*/
	virtual
	sge::renderer::target::onscreen &
	onscreen_target() const = 0;

	/**
	\brief Returns the capabilities of the device
	*/
	virtual
	sge::renderer::caps::device const &
	caps() const = 0;

	/**
	\brief Returns the current display mode

	The display mode can change over time (for example, if the window is
	moved between monitors). It can be used for dpi or refresh rate
	calculations. Note, that it is possible to have no current display mode
	(e.g. if the window is invisible).
	*/
	virtual
	sge::renderer::display_mode::optional_object
	display_mode() const = 0;

	/**
	\brief Tries to set a new display mode

	Tries to set the display mode of the monitor the window is on to \a
	mode. Passing a mode returned by sge::renderer::system::display_modes
	should be safe.

	\param mode The display mode to use

	\throw sge::renderer::exception If the display mode cannot be set.
	*/
	virtual
	void
	display_mode(
		sge::renderer::display_mode::optional_object const &mode
	) = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~core() = 0;
};

}
}
}

#endif
