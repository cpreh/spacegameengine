//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/bind_level.hpp>
#include <sge/opengl/texture/binding.hpp>
#include <sge/opengl/texture/get_stage_id.hpp>
#include <sge/opengl/texture/get_stage_type.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/const.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::opengl::texture::scoped_work_binding::scoped_work_binding(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::opengl::texture::type const _type,
	sge::opengl::texture::id const _id
)
:
	sge::opengl::texture::binding(),
	active_level_(
		_log,
		_context,
		scoped_work_binding::get_stage()
	),
	previous_id_(
		sge::opengl::texture::get_stage_id(
			_context,
			scoped_work_binding::get_stage()
		)
	),
	type_(
		_type
	),
	previous_type_(
		sge::opengl::texture::get_stage_type(
			_context,
			scoped_work_binding::get_stage()
		)
	)
{
	this->bind(
		sge::opengl::texture::optional_id(
			_id
		),
		type_
	);
}

FCPPT_PP_POP_WARNING

sge::opengl::texture::scoped_work_binding::~scoped_work_binding()
{
	this->bind(
		previous_id_,
		fcppt::optional::from(
			previous_type_,
			fcppt::const_(
				type_
			)
		)
	);
}

sge::renderer::texture::stage
sge::opengl::texture::scoped_work_binding::stage() const
{
	return
		scoped_work_binding::get_stage();
}

sge::renderer::texture::stage
sge::opengl::texture::scoped_work_binding::get_stage()
{
	return
		sge::renderer::texture::stage(
			0U
		);
}

sge::opengl::texture::type
sge::opengl::texture::scoped_work_binding::type() const
{
	return
		type_;
}

void
sge::opengl::texture::scoped_work_binding::bind(
	sge::opengl::texture::optional_id const _id,
	sge::opengl::texture::type const _type
)
{
	sge::opengl::texture::bind_level(
		active_level_,
		_type,
		_id
	);
}
