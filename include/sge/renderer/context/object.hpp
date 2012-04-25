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


#ifndef SGE_RENDERER_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/clip_plane.hpp>
#include <sge/renderer/clip_plane_index.hpp>
#include <sge/renderer/const_optional_vertex_declaration_ref_fwd.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/renderer/glsl/const_optional_program_ref_fwd.hpp>
#include <sge/renderer/light/index.hpp>
#include <sge/renderer/light/object_fwd.hpp>
#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/stage_arg.hpp>
#include <sge/renderer/texture/stage_arg_value.hpp>
#include <sge/renderer/texture/stage_op.hpp>
#include <sge/renderer/texture/stage_op_value.hpp>
#include <sge/renderer/texture/filter/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace context
{

class SGE_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(
		object
	);
protected:
	SGE_RENDERER_SYMBOL
	object();
public:
	SGE_RENDERER_SYMBOL
	virtual
	~object() = 0;

	virtual
	sge::renderer::target::base &
	target() = 0;

	virtual
	void
	clear(
		sge::renderer::clear::parameters const &
	) = 0;

	/**
	 * \brief Renders indexed geometry
	 *
	 * Renders indexed geometry using \a index_buffer and the currently set
	 * vertex buffers. \a primitive_count primitives are rendered. The
	 * indices necessary for this are extracted from \a index_buffer from
	 * position \a first_index to \a first_index +
	 * renderer::indices_per_primitive(primitive_type) * primitive_count.
	 * The possible values for the indices range from \a first_vertex to \a
	 * first_vertex + \a vertex_count - 1. \a first_vertex and \a
	 * vertex_count should be considered as a possibility for optimization,
	 * in case only a portion of the vertex buffers is referenced by the
	 * call. The most conservative use is to pass 0 and
	 * vertex_buffer::size.
	 *
	 * \param index_buffer The index buffer to use
	 * \param first_vertex The minimum value for all used indices
	 * \param vertex_count The maximum value for all used indices
	 * \param primitive_type The type of primitive to render
	 * \param primitive_count The number of primitives to render
	 * \param first_index The offset into the index buffer
	 *
	 * \see sge::renderer::device::activate_vertex_buffer
	 * \see sge::renderer::device::vertex_declaration
	 *
	 * \warning The behaviour is undefined if there is not exactly one
	 * activated vertex buffer per sge::renderer::vf::part.
	 * \warning The behaviour is undefined if extracted indices are out of
	 * bounds.
	 * \warning The behaviour is undefined if vertices are referenced that
	 * one of the vertex buffer doesn't have.
	 * \warning The behaviour is undefined if vertices are referenced that
	 * are outside of the constraints from \a first_vertex and \a
	 * vertex_count.
	 */
	virtual
	void
	render_indexed(
		sge::renderer::index_buffer const &index_buffer,
		sge::renderer::first_vertex first_vertex,
		sge::renderer::vertex_count vertex_count,
		sge::renderer::indexed_primitive_type::type primitive_type,
		sge::renderer::primitive_count primitive_count,
		sge::renderer::first_index first_index
	) = 0;

	/**
	 * \brief Renders non indexed geometry
	 *
	 * Renders non indexed geometry using the currently set vertex buffers.
	 * It uses renderer::nonindexed_primitive_count(\a vertex_count, \a
	 * primitive_type) vertices starting at \a first_vertex. For lines or
	 * a line strip, \a vertex_count must be at least 2, for triangles, a
	 * triangle strip or a triangle, \a vertex_count must be at least 3.
	 * For lines, vertex_count must be a multiple of 2, for triangles,
	 * vertex_count must be a multiple of 3.
	 *
	 * \param first_vertex The offset into the vertex buffer
	 * \param vertex_count The number of vertices to use
	 * \param primitive_type The type of primitive to render
	 *
	 * \see sge::renderer::device::activate_vertex_buffer
	 * \see sge::renderer::device::vertex_declaration
	 *
	 * \warning The behaviour is undefined if there is not exactly one
	 * activated vertex buffer per sge::renderer::vf::part.
	 * \warning The behaviour is undefined if one of the constraints for \a
	 * vertex_count is unmet.
	 * \warning The behaviour is undefined if vertices are referenced that
	 * one of the vertex buffer doesn't have.
	*/
	virtual
	void
	render_nonindexed(
		sge::renderer::first_vertex first_vertex,
		sge::renderer::vertex_count vertex_count,
		sge::renderer::nonindexed_primitive_type::type primitive_type
	) = 0;

	/**
	 * \brief Activates a vertex buffer
	 *
	 * A vertex buffer is activated, which means that it will supply vertex
	 * data for the renderer::vf::part it represents. It is important that
	 * the corresponding vertex declaration is already set! Initially, no
	 * vertex buffers are activated.
	 *
	 * \param vertex_buffer The vertex buffer to activate
	 *
	 * \see sge::renderer::device::vertex_declaration
	 * \see sge::renderer::scoped_vertex_declaration
	 *
	 * \warning The behaviour is undefined if the vertex declaration of \a
	 * vertex_buffer is not set.
	*/
	virtual
	void
	activate_vertex_buffer(
		sge::renderer::vertex_buffer const &vertex_buffer
	) = 0;

	/**
	 * \brief Deactives a vertex buffer
	 *
	 * After activating a vertex buffer with device::activate_vertex_buffer,
	 * it should be deactivated again when it is no longer needed.
	 *
	 * \param vertex_buffer The vertex buffer to deactivate
	 *
	 * \warning The behaviour is undefined if \a vertex_buffer isn't
	 * activated.
	*/
	virtual
	void
	deactivate_vertex_buffer(
		sge::renderer::vertex_buffer const &vertex_buffer
	) = 0;

	/**
	 * \brief Sets or unsets the current vertex declaration
	 *
	 * Sets or unsets the current vertex declaration depending on whether
	 * \a vertex_declaration is empty. Initially there is no vertex
	 * declaration set.
	 *
	 * \param vertex_declaration The vertex declaration to set or
	 * renderer::const_optional_vertex_declaration()
	 *
	 * \see sge::renderer::device::deactivate_vertex_buffer
	 * \see sge::renderer::scoped_vertex_declaration
	 *
	 * \warning The behaviour is undefined if vertex buffers are still
	 * active.
	 */
	virtual
	void
	vertex_declaration(
		sge::renderer::const_optional_vertex_declaration_ref const &vertex_declaration
	) = 0;

	/**
	 * \brief Sets the current state
	 *
	 * Overwrites a portion of the current state with whatever is present
	 * in \a list. Initially, the state is sge::renderer::state::default_()
	 *
	 * \param list The part of the current state to replace
	 * \see sge::renderer::state::default_
	*/
	virtual
	void
	state(
		sge::renderer::state::list const &list
	) = 0;

	/**
	 * \brief Pushes the current state on a stack and activates a new portion of state
	 *
	 * Pushes the current state on a stack which can later be restored with
	 * device::pop_state. The current state is then updated with the portion of state
	 * from \a list. Initially, nothing is on the state stack.
	 *
	 * \param list The part of the current state to replace
	 * \see sge::renderer::device::state
	 * \see sge::renderer::state::scoped
	*/
	virtual
	void
	push_state(
		sge::renderer::state::list const &list
	) = 0;

	/**
	 * \brief Restores previously pushed state
	 *
	 * Takes the previously pushed state and makes it the new active state.
	 * Then the previously pushed state is removed from the stack.
	 * Initially, nothing is on the state stack.
	 *
	 * \warning The behaviour is undefined if nothing is on the stack.
	*/
	virtual
	void
	pop_state() = 0;

	/**
	 * \brief Sets the current material
	 *
	 * Sets the current material to \a material. Initially, the material
	 * is unspecified. It will only come into play if
	 * renderer::state::bool_::enable_lighting is activated and the fixed
	 * function pipeline is used.
	 *
	 * \param material The material to set
	*/
	virtual
	void
	material(
		sge::renderer::material const &material
	) = 0;

	/**
	 * \brief Enables or disables a light
	 *
	 * Enables or disables a light given by \a index, depending on whether
	 * \a enabled is true or false. Initially, all lights are disabled.
	 *
	 * \param index The index of the light to enable or disable
	 * \param enable Enable or disable the light
	 *
	 * \see sge::renderer::caps::object::light_indices
	 *
	 * \warning The behaviour is undefined if \a index is greater or equal
	 * to sge::renderer::caps::object::light_indices
	 */
	virtual
	void
	enable_light(
		sge::renderer::light::index index,
		bool enable
	) = 0;

	/**
	 * \brief Sets a light
	 *
	 * Sets the light given by \a index to \a light. Initially, the lights
	 * are unspecified. It will only come into play if
	 * renderer::state::bool_::enable_lighting is activated and the fixed
	 * function pipeline is used.
	 *
	 * \param index The index of the light to set
	 * \param light Description of the light
	 *
	 * \see sge::renderer::caps::object::light_indices
	 *
	 * \warning The behaviour is undefined if \a index is greater or equal
	 * to sge::renderer::caps::object::light_indices
	*/
	virtual
	void
	light(
		sge::renderer::light::index index,
		sge::renderer::light::object const &light
	) = 0;

	/**
	 * \brief Enables or disables a clip plane
	 *
	 * Enables or disables a clip plane given by \a index, depending on
	 * whether \a enabled is true or false. Initially, all clip planes are
	 * disabled.
	 *
	 * \param index The index of the clip plane to enable or disable
	 * \param enable Enable or disable the clip plane
	 *
	 * \see sge::renderer::caps::object::clip_plane_indices
	 *
	 * \warning The behaviour is undefined if \a index is greater or equal
	 * to sge::renderer::caps::object::clip_plane_indices
	*/
	virtual
	void
	enable_clip_plane(
		sge::renderer::clip_plane_index index,
		bool enable
	) = 0;

	/**
	 * \brief Sets a clip plane
	 *
	 * Sets the clip plane given by \a index to \a plane. Initially, the
	 * clip planes are unspecified.
	 *
	 * \param index The index of the clip plane to set
	 * \param plane The clip plane
	 *
	 * \see sge::renderer::caps::object::clip_plane_indices
	 *
	 * \warning The behaviour is undefined if \a index is greater or equal
	 * to sge::renderer::caps::object::clip_plane_indices
	*/
	virtual
	void
	clip_plane(
		sge::renderer::clip_plane_index index,
		sge::renderer::clip_plane const &plane
	) = 0;

	/**
	 * \brief Sets a texture operation for a texture stage
	 *
	 * Sets the texture operation for \a stage and \a what to \a value.  \a
	 * what specifies if the operation should be changed for color values
	 * or for alpha values. Initially, the values of the 0th stage are
	 * sge::renderer::texture::stage_op_value::arg0. For all other stages
	 * they are unspecified.
	 *
	 * \param stage The texture stage to set the value for
	 * \param what Set the color or alpha operation
	 * \param value The value to set
	 *
	 * \see sge::renderer::caps::object::texture_stages
	 *
	 * \warning The behaviour is undefined if \a stage is greater or equal
	 * to sge::renderer::caps::object::texture_stages
	*/
	virtual
	void
	texture_stage_op(
		sge::renderer::texture::stage stage,
		sge::renderer::texture::stage_op::type what,
		sge::renderer::texture::stage_op_value::type value
	) = 0;

	/**
	 * \brief Sets which texture argument to use for a texture stage
	 *
	 * Sets the texture argument to use for \a stage and \a what to \a
	 * value. \a what specifies which argument to change. There are three
	 * different arguments in total. It depends on the
	 * sge::renderer::texture::stage_op_value being active how many
	 * arguments are needed. Arguments for color and alpha can be changed
	 * separately. Initially, the values for
	 * sge::renderer::texture::stage_arg::color0 and
	 * sge::renderer::texture::stage_arg::alpha0 for the 0th stage are
	 * sge::renderer::texture::stage_arg_value::texture, all other values
	 * are unspecified.
	 *
	 * \param stage The texture stage to set the value for
	 * \param what Set the color or alpha operation for argument 0, 1 or 2
	 * \param value The value to set
	 *
	 * \see sge::renderer::caps::object::texture_stages
	 *
	 * \warning The behaviour is undefined if \a stage is greater or equal
	 * to sge::renderer::caps::object::texture_stages
	 */
	virtual
	void
	texture_stage_arg(
		sge::renderer::texture::stage stage,
		sge::renderer::texture::stage_arg::type what,
		sge::renderer::texture::stage_arg_value::type value
	) = 0;

	/**
	 * \brief Sets the texture filter for a texture stage
	 *
	 * Sets the texture filter for \a stage to \a filter. There are two
	 * different texture filters: normal and anisotropic. Initially, the
	 * filters for every texture stage are the same as
	 * \link sge::renderer::texture::filter::default_ \endlink
	 *
	 * \param filter The filter to set
	 * \param stage The texture stage to set the filter for
	 *
	 * \see sge::renderer::caps::object::texture_stages
	 *
	 * \warning The behaviour is undefined if \a stage is greater or equal
	 * to sge::renderer::caps::object::texture_stages
	 */
	virtual
	void
	texture_filter(
		sge::renderer::texture::filter::object const &filter,
		sge::renderer::texture::stage stage
	) = 0;

	/**
	 * \brief Sets the texture address mode for horizontal borders
	 *
	 * Sets the horizontal texture address mode for \a stage to \a mode.
	 * Initially, the address modes for every texture stage are the same as
	 * \link sge::renderer::texture::address_mode_default \endlink
	 *
	 * \param mode The horizontal address mode to set
	 * \param stage The texture stage to set the address mode for
	 *
	 * \warning The behaviour is undefined if \a stage is greater or equal
	 * to sge::renderer::caps::object::texture_stages
	*/
	virtual
	void
	texture_address_mode_s(
		sge::renderer::texture::address_mode_s mode,
		sge::renderer::texture::stage stage
	) = 0;

	/**
	 * \brief Sets the texture address mode for vertical borders
	 *
	 * Sets the vertical texture address mode for \a stage to \a mode.
	 * Initially, the address modes for every texture stage are the same as
	 * \link sge::renderer::texture::address_mode_default \endlink
	 *
	 * \param mode The vertical address mode to set
	 * \param stage The texture stage to set the address mode for
	 *
	 * \warning The behaviour is undefined if \a stage is greater or equal
	 * to sge::renderer::caps::object::texture_stages
	*/
	virtual
	void
	texture_address_mode_t(
		sge::renderer::texture::address_mode_t mode,
		sge::renderer::texture::stage stage
	) = 0;

	/**
	 * \brief Sets the texture address mode for depth borders
	 *
	 * Sets the depth texture address mode for \a stage to \a mode.
	 * Initially, the address modes for every texture stage are the same as
	 * \link sge::renderer::texture::address_mode_default \endlink
	 *
	 * \param mode The depth address mode to set
	 * \param stage The texture stage to set the address mode for
	 *
	 * \warning The behaviour is undefined if \a stage is greater or equal
	 * to sge::renderer::caps::object::texture_stages
	*/
	virtual
	void
	texture_address_mode_u(
		sge::renderer::texture::address_mode_u mode,
		sge::renderer::texture::stage stage
	) = 0;

	/**
	 * \brief Sets a texture for a texture stage
	 *
	 * Sets the texture for \a stage to \a texture.
	 * Initially, the textures for every stage are none.
	 *
	 * \param texture The texture to set or
	 * sge::renderer::texture::const_optional_base_ref() to disable
	 * texturing. \param stage The stage to set the texture for
	 *
	 * \see sge::renderer::caps::object::texture_stages
	 *
	 * \warning The behaviour is undefined if \a stage is greater or equal
	 * to sge::renderer::caps::object::texture_stages
	 */
	virtual
	void
	texture(
		sge::renderer::texture::const_optional_base_ref const &texture,
		sge::renderer::texture::stage stage
	) = 0;

	/**
	 * \brief Sets the matrix for a matrix mode
	 *
	 * Sets the matrix mode of \a mode to \a matrix. Initially, the matrix
	 * for every matrix mode is the identity.
	*/
	virtual
	void
	transform(
		sge::renderer::matrix_mode::type mode,
		sge::renderer::matrix4 const &matrix
	) = 0;

	/**
	 * \brief Sets the current glsl program
	 *
	 * Sets the current glsl program to \a program or deactivates glsl if
	 * \a program is sge::renderer::glsl::const_optional_program_ref().  If a
	 * glsl program is set, the fixed function pipeline is mostly disabled.
	 * This includes lights, materials, texture stage states, fog states.
	 * Initially, the glsl program is disabled.
	 *
	 * \param program The program to set or
	 * sge::renderer::glsl::const_optional_program_ref() to disable glsl.
	 *
	 * \see sge::renderer::caps::object::glsl_supported
	 *
	 * \warning The behaviour is undefined if
	 * sge::renderer::caps::object::glsl_supported is false
	 */
	virtual
	void
	glsl_program(
		sge::renderer::glsl::const_optional_program_ref const &program
	) = 0;
};

}
}
}

#endif
