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


#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/opengl/cg/texture/assigned_stage.hpp>
#include <sge/opengl/cg/texture/disable_parameter.hpp>
#include <sge/opengl/cg/texture/enable_parameter.hpp>
#include <sge/opengl/cg/texture/loaded_object.hpp>
#include <sge/opengl/cg/texture/set_parameter.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/const_optional_base_ref.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/set_samplers.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/make_cref.hpp>


sge::opengl::cg::texture::loaded_object::loaded_object(
	sge::opengl::context::object &_context,
	sge::cg::parameter::object const &_parameter,
	sge::renderer::texture::base &_texture
)
:
	context_(
		_context
	),
	bind_context_(
		sge::opengl::context::use<
			sge::opengl::texture::bind_context
		>(
			_context
		)
	),
	parameter_(
		_parameter
	),
	texture_(
		dynamic_cast<
			sge::opengl::texture::base const &
		>(
			_texture
		)
	),
	stage_(
		sge::opengl::cg::texture::assigned_stage(
			_parameter
		)
	)
{
	sge::opengl::cg::texture::set_parameter(
		parameter_,
		sge::opengl::texture::optional_id(
			texture_.id()
		)
	);
}

sge::opengl::cg::texture::loaded_object::~loaded_object()
{
	sge::opengl::cg::texture::set_parameter(
		parameter_,
		sge::opengl::texture::optional_id()
	);
}

sge::renderer::texture::stage
sge::opengl::cg::texture::loaded_object::enable() const
{
	sge::opengl::cg::texture::enable_parameter(
		parameter_
	);

	bind_context_.stage(
		stage_,
		sge::opengl::texture::const_optional_base_ref(
			fcppt::make_cref(
				texture_
			)
		)
	);

	sge::opengl::texture::active_level const active_level(
		context_,
		stage_
	);

	sge::opengl::texture::render_binding const binding(
		active_level,
		texture_.type()
	);

	sge::opengl::texture::set_samplers(
		binding,
		context_
	);

	return
		stage_;
}

void
sge::opengl::cg::texture::loaded_object::disable() const
{
	sge::opengl::cg::texture::disable_parameter(
		parameter_
	);

	bind_context_.stage(
		stage_,
		sge::opengl::texture::const_optional_base_ref()
	);
}
