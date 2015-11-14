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
#include <fcppt/from_optional.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::opengl::texture::scoped_work_binding::scoped_work_binding(
	sge::opengl::context::object &_context,
	sge::opengl::texture::type const _type,
	sge::opengl::texture::id const _id
)
:
	sge::opengl::texture::binding(),
	active_level_(
		_context,
		this->stage()
	),
	previous_id_(
		sge::opengl::texture::get_stage_id(
			_context,
			this->stage()
		)
	),
	type_(
		_type
	),
	previous_type_(
		sge::opengl::texture::get_stage_type(
			_context,
			this->stage()
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
		fcppt::from_optional(
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
		sge::renderer::texture::stage(
			0u
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
