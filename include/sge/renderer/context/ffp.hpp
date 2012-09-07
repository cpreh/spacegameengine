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


#ifndef SGE_RENDERER_CONTEXT_FFP_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_FFP_HPP_INCLUDED

//#include <sge/renderer/clip_plane.hpp>
//#include <sge/renderer/clip_plane_index.hpp>
//#include <sge/renderer/material_fwd.hpp>
//#include <sge/renderer/matrix4_fwd.hpp>
//#include <sge/renderer/matrix_mode.hpp>
//#include <sge/renderer/texture/stage_arg.hpp>
//#include <sge/renderer/texture/stage_arg_value.hpp>
//#include <sge/renderer/texture/stage_op.hpp>
//#include <sge/renderer/texture/stage_op_value.hpp>
//#include <sge/renderer/texture/filter/object_fwd.hpp>
#include <sge/class_symbol.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/state/ffp/transform/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace context
{

class SGE_CLASS_SYMBOL ffp
:
	public sge::renderer::context::core
{
	FCPPT_NONCOPYABLE(
		ffp
	);
protected:
	SGE_RENDERER_SYMBOL
	ffp();
public:
	SGE_RENDERER_SYMBOL
	virtual
	~ffp() = 0;

	virtual
	void
	transform(
		sge::renderer::state::ffp::transform::parameters const &
	) = 0;

#if 0
	virtual
	void
	texture_stage_op(
		sge::renderer::texture::stage stage,
		sge::renderer::texture::stage_op::type what,
		sge::renderer::texture::stage_op_value::type value
	) = 0;

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
#endif

};

}
}
}

#endif
