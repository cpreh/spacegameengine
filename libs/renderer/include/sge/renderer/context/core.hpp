//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_CONTEXT_CORE_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_CORE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/config.hpp> // IWYU pragma: keep
#include <sge/renderer/primitive_type_fwd.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/state/core/blend/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/optional_offscreen_ref_fwd.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/nonmovable.hpp>

#ifdef SGE_RENDERER_HAVE_CG
#include <sge/renderer/cg/const_loaded_program_ref.hpp>
#include <sge/renderer/cg/const_loaded_texture_ref.hpp>
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#endif

namespace sge::renderer::context
{

/**
\brief Renders to a render target using core functionality

\ingroup sge_renderer

A renderer core context must be created by calling
sge::renderer::device::core::begin_rendering on a render target.
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL core
{
  FCPPT_NONMOVABLE(core);

protected:
  SGE_RENDERER_DETAIL_SYMBOL
  core();

public:
  SGE_RENDERER_DETAIL_SYMBOL
  virtual ~core();

  /**
	\brief The target that has been used to create this context
	*/
  virtual sge::renderer::target::base &target() = 0;

  /**
	\brief Clear various buffers

	Clears the buffers denoted by \a parameters, e.g. color buffer, depth
	or stencil buffer.
	*/
  virtual void clear(sge::renderer::clear::parameters const &parameters) = 0;

  /**
	\brief Allows temporary substitution of the current target

	\note Avoid using this function if you can and try to render everything
	to a target in one go. This function was introduced to support APIs
	that need to change render targets at any point.
	*/
  virtual void offscreen_target(sge::renderer::target::optional_offscreen_ref const &) = 0;

  /**
	\brief Renders indexed geometry

	Renders indexed geometry using \a index_buffer and the currently set
	vertex buffers.
	<code>sge::renderer::element_to_primitive_count(index_count)</code>
	primitives are rendered. The indices necessary for this are extracted
	from \a index_buffer from position \a first_index to \a first_index +
	\a index_count. The possible values for the indices range from \a
	first_vertex to \a first_vertex + \a vertex_count - 1. \a first_vertex
	and \a vertex_count should be considered as a possibility for
	optimization, in case only a portion of the vertex buffers is
	referenced by the call. The most conservative use is to pass 0 and
	vertex_buffer::size.

	\param index_buffer The index buffer to use

	\param first_vertex The minimum value for all used indices

	\param vertex_count The maximum value for all used indices

	\param primitive_type The type of primitive to render

	\param first_index The offset into the index buffer

	\param index_count The number of indices to use

	\see sge::renderer::device::activate_vertex_buffer

	\see sge::renderer::device::vertex_declaration

	\warning The behaviour is undefined if there is not exactly one
	activated vertex buffer per sge::renderer::vf::part.

	\warning The behaviour is undefined if extracted indices are out of
	bounds.

	\warning The behaviour is undefined if vertices are referenced that
	one of the vertex buffer doesn't have.

	\warning The behaviour is undefined if vertices are referenced that
	are outside of the constraints from \a first_vertex and \a
	vertex_count.
	*/
  virtual void render_indexed(
      sge::renderer::index::buffer const &index_buffer,
      sge::renderer::vertex::first first_vertex,
      sge::renderer::vertex::count vertex_count,
      sge::renderer::primitive_type primitive_type,
      sge::renderer::index::first first_index,
      sge::renderer::index::count index_count) = 0;

  /**
	\brief Renders non indexed geometry

	Renders non indexed geometry using the currently set vertex buffers.
	<code>sge::renderer::element_to_primitive_count(vertex_count)</code>
	primitives are rendered. The vertices necessary for this are extracted
	from position \a first_vertex to \a vertex_index + \a vertex_count.

	\param first_vertex The offset into the vertex buffer
	\param vertex_count The number of vertices to use
	\param primitive_type The type of primitive to render

	\see sge::renderer::device::activate_vertex_buffer
	\see sge::renderer::device::vertex_declaration

	\warning The behaviour is undefined if there is not exactly one
	activated vertex buffer per sge::renderer::vf::part.

	\warning The behaviour is undefined if one of the constraints for \a
	vertex_count is unmet.

	\warning The behaviour is undefined if vertices are referenced that
	 one of the vertex buffer doesn't have.
	*/
  virtual void render_nonindexed(
      sge::renderer::vertex::first first_vertex,
      sge::renderer::vertex::count vertex_count,
      sge::renderer::primitive_type primitive_type) = 0;

  /**
	\brief Activates a vertex buffer

	A vertex buffer is activated, which means that it will supply vertex
	data for the sge::renderer::vf::part it represents. It is important
	that the corresponding vertex declaration is already set! Initially, no
	vertex buffers are activated.

	\param vertex_buffer The vertex buffer to activate

	\see sge::renderer::device::vertex_declaration

	\see sge::renderer::vertex::scoped_declaration

	\warning The behaviour is undefined if the vertex declaration of \a
	vertex_buffer is not set.
	*/
  virtual void activate_vertex_buffer(sge::renderer::vertex::const_buffer_ref vertex_buffer) = 0;

  /**
	\brief Deactives a vertex buffer

	After activating a vertex buffer with
	sge::renderer::context::core::activate_vertex_buffer, it should be
	deactivated again when it is no longer needed.

	\param vertex_buffer The vertex buffer to deactivate

	\warning The behaviour is undefined if \a vertex_buffer isn't
	activated.
	*/
  virtual void deactivate_vertex_buffer(sge::renderer::vertex::buffer const &vertex_buffer) = 0;

  /**
	\brief Sets or unsets the current vertex declaration

	Sets or unsets the current vertex declaration depending on whether \a
	vertex_declaration is empty. Initially there is no vertex declaration
	set.

	\param vertex_declaration The vertex declaration to set or
	sge::renderer::vertex::const_optional_declaration()

	\see sge::renderer::vertex::scoped_declaration

	\warning The behaviour is undefined if vertex buffers are still active.
	*/
  virtual void vertex_declaration(
      sge::renderer::vertex::const_optional_declaration_ref const &vertex_declaration) = 0;

  /**
	\brief Sets a texture for a texture stage

	Sets the texture for \a stage to \a texture. Initially, the textures
	for every stage are none.

	\param texture The texture to set or
	sge::renderer::texture::const_optional_base_ref() to disable texturing.
	\param stage The stage to set the texture for

	\see sge::renderer::caps::object::texture_stages

	\warning The behaviour is undefined if \a stage is greater or equal
	to sge::renderer::caps::object::texture_stages
	*/
  virtual void texture(
      sge::renderer::texture::const_optional_base_ref const &texture,
      sge::renderer::texture::stage stage) = 0;

  /**
	\brief Sets or resets the blend state

	Sets the blend state to \a state. If \a state is nothing, the default
	blend state, sge::renderer::state::core::blend::default_, is restored.

	The blend state dictates how color and alpha values in the current
	render target are combined with color and values from rendered
	geometry.
	*/
  virtual void
  blend_state(sge::renderer::state::core::blend::const_optional_object_ref const &state) = 0;

  /**
	\brief Sets or resets the depth stencil state

	Sets the depth stencil state to \a state. If \a state is nothing, the
	default depth stencil state,
	sge::renderer::state::core::depth_stencil::default_, is restored.

	The depth stencil state dictates how the depth and stencil buffers are
	used to omit rendering of geometry and how they are updated.
	*/
  virtual void depth_stencil_state(
      sge::renderer::state::core::depth_stencil::const_optional_object_ref const &) = 0;

  /**
	\brief Sets or resets the rasterizer state

	Sets the rasterizer state to \a state. If \a state is nothing, the
	default rasterizer state,
	sge::renderer::state::core::rasterizer::default_, is restored.

	The rasterizer state dictates how polygons are clipped and filled.
	*/
  virtual void
  rasterizer_state(sge::renderer::state::core::rasterizer::const_optional_object_ref const &) = 0;

  /**
	\brief Sets or resets the sampler state

	Sets the sampler state to \a state. If \a state is nothing, the default
	sampler state, sge::renderer::state::core::sampler::default_, is
	restored.

	The sampler state dictates how texture coordinates are processed and
	textures are filtered.
	*/
  virtual void
  sampler_state(sge::renderer::state::core::sampler::const_optional_object_ref_map const &) = 0;

#ifdef SGE_RENDERER_HAVE_CG
  virtual void set_cg_program(sge::renderer::cg::const_loaded_program_ref) = 0;

  virtual void unset_cg_program(sge::renderer::cg::loaded_program const &) = 0;

  virtual sge::renderer::texture::stage
      set_cg_texture(sge::renderer::cg::const_loaded_texture_ref) = 0;

  virtual void unset_cg_texture(sge::renderer::cg::loaded_texture const &) = 0;
#endif
};

}

#endif
