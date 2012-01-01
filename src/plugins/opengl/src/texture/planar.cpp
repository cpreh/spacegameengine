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


#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/basic_impl.hpp>
#include <sge/opengl/texture/planar.hpp>
#include <sge/opengl/texture/planar_types.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/surface.hpp>
#include <sge/opengl/texture/funcs/get_parameter_int.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>


template class
sge::opengl::texture::basic<
	sge::opengl::texture::planar_types
>;

sge::opengl::texture::planar::planar(
	context::object &_context,
	renderer::texture::planar_parameters const &_param,
	optional_type const &_type
)
:
	texture::planar_basic(
		_context,
		_type
		?
			*_type
		:
			opengl::texture::type(
				GL_TEXTURE_2D
			)
		,
		_param
	)
{
}

sge::opengl::texture::planar::~planar()
{
}

sge::renderer::color_surface_ptr const
sge::opengl::texture::planar::surface(
	renderer::texture::stage const _stage
)
{
	opengl::texture::scoped_work_binding const binding(
		this->context(),
		this->type(),
		this->id(),
		renderer::texture::stage(0u)
	);

	return
		fcppt::make_shared_ptr<
			opengl::texture::surface
		>(
			fcppt::cref(
				binding
			),
			fcppt::ref(
				this->context()
			),
			this->type(),
			this->id(),
			_stage,
			this->resource_flags(),
			this->format(),
			this->format_type(),
			this->capabilities()
			& sge::renderer::texture::capabilities::render_target
		);
}

sge::renderer::texture::stage const
sge::opengl::texture::planar::stages() const
{
	opengl::texture::scoped_work_binding const binding(
		this->context(),
		this->type(),
		this->id(),
		renderer::texture::stage(
			0u
		)
	);

	return
		renderer::texture::stage(
			funcs::get_parameter_int(
				binding,
				this->type(),
				GL_TEXTURE_BASE_LEVEL
			)
		);
}
