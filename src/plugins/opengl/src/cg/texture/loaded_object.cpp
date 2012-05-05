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


#include <sge/cg/check_state.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/opengl/cg/texture/loaded_object.hpp>
#include <sge/opengl/cg/texture/set_parameter.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/base.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::cg::texture::loaded_object::loaded_object(
	sge::cg::parameter::object const &_parameter,
	sge::renderer::texture::base &_texture
)
:
	parameter_(
		_parameter
	)
{
	sge::opengl::cg::texture::set_parameter(
		parameter_,
		sge::opengl::texture::optional_id(
			dynamic_cast<
				sge::opengl::texture::base const &
			>(
				_texture
			).id()
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

void
sge::opengl::cg::texture::loaded_object::enable() const
{
	::cgGLEnableTextureParameter(
		parameter_.get()
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgEnableTextureParameter failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::cg::texture::loaded_object::disable() const
{
	::cgGLDisableTextureParameter(
		parameter_.get()
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgDisableTextureParameter failed"),
		sge::renderer::exception
	)
}
