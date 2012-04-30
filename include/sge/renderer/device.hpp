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


#ifndef SGE_RENDERER_DEVICE_HPP_INCLUDED
#define SGE_RENDERER_DEVICE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_unique_ptr.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/index_buffer_unique_ptr.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/vertex_buffer_unique_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_unique_ptr.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/caps/object_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/renderer/context/object_unique_ptr.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/glsl/geometry_shader_unique_ptr.hpp>
#include <sge/renderer/glsl/pixel_shader_unique_ptr.hpp>
#include <sge/renderer/glsl/program_unique_ptr.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/vertex_shader_unique_ptr.hpp>
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
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/noncopyable.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/object_fwd.hpp>
#include <sge/cg/profile/object_unique_ptr.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#endif


namespace sge
{
namespace renderer
{

/**
 * \brief Renders primitives and creates renderer ressources
 *
 * sge::renderer::device is the most important class that a renderer plugin
 * implements. It can render indexed and nonindexed primitives and create
 * various ressources like textures and vertex and index buffers. It also
 * manages all state that a renderer might have. A window is always associated
 * with the device.
 */
class SGE_CLASS_SYMBOL device
{
	FCPPT_NONCOPYABLE(
		device
	);
protected:
	SGE_RENDERER_SYMBOL
	device();
public:
	/**
	 * \brief Begins the rendering operation
	 *
	 * To be able to call device::render_indexed or
	 * device::render_nonindexed, this function must be called first. To
	 * end the rendering process and present it, use device::end_rendering.
	 *
	 * \see sge::renderer::scoped_block
	 *
	 * \warning The behaviour is undefined if this function is called more
	 * than once without a call to device::end_rendering
	*/
	virtual
	sge::renderer::context::object_unique_ptr
	begin_rendering(
		sge::renderer::target::base &
	) = 0;

	/**
	 * \brief Ends the rendering operation
	 *
	 * After a call to device::begin_rendering this function must
	 * be called to present the rendered things in between.
	 *
	 * \warning The behaviour is undefined if begin_rendering wasn't called
	*/
	virtual
	void
	end_rendering(
		sge::renderer::context::object &
	) = 0;

	/**
	 * \brief Creates a glsl program
	 *
	 * Creates an empty glsl program.
	 *
	 * \return A unique pointer to the created glsl program
	 *
	 * \see sge::renderer::caps::object::glsl_supported
	 *
	 * \warning The behaviour is undefined if
	 * sge::renderer::caps::object::glsl_supported is false
	 */
	virtual
	sge::renderer::glsl::program_unique_ptr
	create_glsl_program() = 0;

	/**
	 * \brief Creates a glsl vertex shader
	 *
	 * Creates a glsl vertex shader from \a source
	 *
	 * \param source The source for the shader
	 *
	 * \return A unique pointer to the created vertex shader
	 *
	 * \see sge::renderer::caps::object::glsl_supported
	 *
	 * \warning The behaviour is undefined if
	 * sge::renderer::caps::object::glsl_supported is false
	 */
	virtual
	sge::renderer::glsl::vertex_shader_unique_ptr
	create_glsl_vertex_shader(
		sge::renderer::glsl::string const &source
	) = 0;

	/**
	 * \brief Creates a glsl pixel shader
	 *
	 * Creates a glsl pixel shader from \a source
	 *
	 * \param source The source for the shader
	 *
	 * \return A unique pointer to the created pixel shader
	 *
	 * \see sge::renderer::caps::object::glsl_supported
	 *
	 * \warning The behaviour is undefined if
	 * sge::renderer::caps::object::glsl_supported is false
	 */
	virtual
	sge::renderer::glsl::pixel_shader_unique_ptr
	create_glsl_pixel_shader(
		sge::renderer::glsl::string const &source
	) = 0;

	/**
	 * \brief Creates a glsl geometry shader
	 *
	 * Creates a glsl geometry shader from \a source
	 *
	 * \param source The source for the shader
	 *
	 * \return A unique pointer to the created geometry shader
	 *
	 * \see sge::renderer::caps::object::glsl_supported
	 *
	 * \warning The behaviour is undefined if
	 * sge::renderer::caps::object::glsl_supported is false
	 */
	virtual
	sge::renderer::glsl::geometry_shader_unique_ptr
	create_glsl_geometry_shader(
		sge::renderer::glsl::string const &source
	) = 0;

	/**
	 * \brief Creates a render target
	 *
	 * Creates an empty render target.
	 *
	 * \return A unique pointer to the created target
	 *
	 * \see sge::renderer::caps::object::render_target_supported
	 *
	 * \warning The behaviour is undefined if
	 * sge::renderer::caps::object::render_target_supported is false
	 */
	virtual
	sge::renderer::target::offscreen_unique_ptr
	create_target() = 0;

	/**
	 * \brief Creates a planar texture
	 *
	 * Creates a planar texture from \a parameters.
	 * Initially, the contents of the texture are undefined.
	 *
	 * \param parameters The parameters class for the planar texture, using
	 * sge::renderer::dim2 as its dimensions and
	 * sge::image::color::format::type as its format
	 *
	 * \return A unique pointer to the created planar texture
	 *
	 * \see sge::renderer::caps::object::max_texture_size
	 *
	 * \throw sge::renderer::exception if anything goes wrong
	*/
	virtual
	sge::renderer::texture::planar_unique_ptr
	create_planar_texture(
		sge::renderer::texture::planar_parameters const &parameters
	) = 0;

	/**
	 * \brief Creates a depth stencil texture
	 *
	 * Creates a depth stencil texture from \a parameters.
	 * Initially, the contents of the texture are undefined.
	 *
	 * \param parameters The parameters class for the depth stencil
	 * texture, using sge::renderer::dim2 as its dimensions and
	 * sge::renderer::depth_stencil_format::type as its format
	 *
	 * \return A unique pointer to the created depth stencil texture
	 *
	 * \see sge::renderer::caps::object::max_texture_size
	 *
	 * \throw sge::renderer::exception if anything goes wrong
	 */
	virtual
	sge::renderer::texture::depth_stencil_unique_ptr
	create_depth_stencil_texture(
		sge::renderer::texture::depth_stencil_parameters const &parameters
	) = 0;

	/**
	 * \brief Creates a depth stencil surface
	 *
	 * Creates a depth stencil surface with dimension \a size and format \a
	 * format. Initially, the contents of the surface are undefined.
	 *
	 * \param size The size of the surface
	 * \param format The format of the surface
	 *
	 * \return A unique pointer to the created depth stencil surface
	 *
	 * \throw sge::renderer::exception if anything goes wrong
	 */
	virtual
	sge::renderer::depth_stencil_surface_unique_ptr
	create_depth_stencil_surface(
		sge::renderer::dim2 const &size,
		sge::renderer::depth_stencil_format::type format
	) = 0;

	/**
	 * \brief Creates a volume texture
	 *
	 * Creates a volume texture from \a parameters.
	 * Initially, the contents of the texture are undefined.
	 *
	 * \param parameters The parameters class for the depth stencil
	 * texture, using sge::renderer::dim3 as its dimensions and
	 * sge::image::color::format::type as its format
	 *
	 * \return A unique pointer to the created volume texture
	 *
	 * \see sge::renderer::caps::object::max_volume_texture_extent
	 *
	 * \throw sge::renderer::exception if anything goes wrong
	 */
	virtual
	sge::renderer::texture::volume_unique_ptr
	create_volume_texture(
		sge::renderer::texture::volume_parameters const &parameters
	) = 0;

	/**
	 * \brief Creates a cube texture
	 *
	 * Creates a cube texture from \a parameters.
	 * Initially, the contents of the texture are undefined.
	 *
	 * \param parameters The parameters class for the depth stencil
	 * texture, using sge::renderer::size_type as its dimensions and
	 * sge::image::color::format::type as its format
	 *
	 * \return A unique pointer to the created cube texture
	 *
	 * \throw sge::renderer::exception if anything goes wrong
	 */
	virtual
	sge::renderer::texture::cube_unique_ptr
	create_cube_texture(
		sge::renderer::texture::cube_parameters const &parameters
	) = 0;

	/**
	 * \brief Creates a vertex declaration
	 *
	 * Creates a vertex declaration from \a format
	 *
	 * \param format The dynamic vertex format to use
	 *
	 * \return A unique pointer to the created vertex declaration
	 *
	 * \throw sge::renderer::exception if anything goes wrong
	 */
	virtual
	sge::renderer::vertex_declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::vf::dynamic::format const &format
	) = 0;

	/**
	 * \brief Creates a vertex buffer
	 *
	 * Creates a vertex buffer that is going to hold data described by \a
	 * part of \a vertex_declaration. It will be able to hold \a
	 * vertex_count vertices. \a flags describes the capabilities of the
	 * buffer. Initially, the contents of the buffer are undefined.
	 *
	 * \param vertex_declaration The vertex declaration the buffer belongs
	 * to
	 *
	 * \param part The part of the vertex declaration the buffer will be
	 * holding vertices for
	 *
	 * \param vertex_count The number of vertices the buffer will hold
	 *
	 * \param flags The capabilitiies of the buffer
	 *
	 * \return A unique pointer to the created vertex buffer
	 *
	 * \throw sge::renderer::exception if anything goes wrong
	 */
	virtual
	sge::renderer::vertex_buffer_unique_ptr
	create_vertex_buffer(
		sge::renderer::vertex_declaration const &vertex_declaration,
		sge::renderer::vf::dynamic::part_index part,
		sge::renderer::vertex_count vertex_count,
		sge::renderer::resource_flags_field const &flags
	) = 0;

	/**
	 * \brief Creates an index buffer
	 *
	 * Creates an index buffer that is going to hold data described by \a
	 * format. It will be able to hold \a index_count indices. \a flags
	 * describes the capabilities of the buffer. Initially, the contents
	 * of the buffer are undefined.
	 *
	 * \param format The format of the indices
	 * \param index_count The number of indices the buffer will hold
	 * \param flags The capabilitiies of the buffer
	 *
	 * \return A unique pointer to the created index buffer
	 *
	 * \throw sge::renderer::exception if anything goes wrong
	 */
	virtual
	sge::renderer::index_buffer_unique_ptr
	create_index_buffer(
		sge::renderer::index::dynamic::format::type format,
		sge::renderer::index_count index_count,
		sge::renderer::resource_flags_field const &flags
	) = 0;

#if defined(SGE_RENDERER_HAVE_CG)
	virtual
	sge::cg::profile::object_unique_ptr
	create_cg_profile(
		sge::cg::profile::shader_type::type
	) = 0;

	virtual
	sge::cg::program::compile_options const
	cg_compile_options(
		sge::cg::context::object const &,
		sge::cg::profile::object const &
	) = 0;

	virtual
	sge::renderer::cg::loaded_program_unique_ptr
	load_cg_program(
		sge::cg::program::object &
	) = 0;
#endif

	/**
	 * \brief Returns the onscreen target
	 *
	 * A device always has an onscreen target even though another render
	 * target has been set.
	 *
	 * \return The onscreen target
	*/
	virtual
	sge::renderer::target::onscreen &
	onscreen_target() const = 0;

	/**
	 * \brief Returns the capabilities of the device
	 *
	 * \return The capabilities
	*/
	virtual
	sge::renderer::caps::object const &
	caps() const = 0;

	SGE_RENDERER_SYMBOL
	virtual
	~device() = 0;
};

}
}

#endif
