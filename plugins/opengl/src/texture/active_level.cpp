//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::opengl::texture::active_level::active_level(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::renderer::texture::stage const _stage
)
:
	stage_(
		_stage
	)
{
	sge::opengl::texture::funcs::set_active_level(
		_log,
		_context,
		_stage
	);
}

sge::opengl::texture::active_level::~active_level()
{
}

sge::renderer::texture::stage
sge::opengl::texture::active_level::stage() const
{
	return
		stage_;
}
