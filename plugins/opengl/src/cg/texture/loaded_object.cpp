//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/opengl/cg/texture/assigned_stage.hpp>
#include <sge/opengl/cg/texture/disable_parameter.hpp>
#include <sge/opengl/cg/texture/enable_parameter.hpp>
#include <sge/opengl/cg/texture/loaded_object.hpp>
#include <sge/opengl/cg/texture/set_parameter.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/const_optional_base_ref.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/set_samplers.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/log/object_reference.hpp>


sge::opengl::cg::texture::loaded_object::loaded_object(
	fcppt::log::object_reference const _log,
	sge::opengl::context::object_ref const _context,
	sge::cg::parameter::object const &_parameter,
	sge::renderer::texture::base_ref const _texture
)
:
	log_{
		_log
	},
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
			_texture.get()
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
			texture_.get().id()
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

	bind_context_.get().stage(
		stage_,
		sge::opengl::texture::const_optional_base_ref(
			texture_
		)
	);

	sge::opengl::texture::active_level const active_level(
		log_.get(),
		context_.get(),
		stage_
	);

	sge::opengl::texture::render_binding const binding(
		active_level,
		texture_.get().type()
	);

	sge::opengl::texture::set_samplers(
		binding,
		context_.get()
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

	bind_context_.get().stage(
		stage_,
		sge::opengl::texture::const_optional_base_ref()
	);
}
