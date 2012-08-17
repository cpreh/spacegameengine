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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/color_surface_types.hpp>
#include <sge/opengl/texture/cube.hpp>
#include <sge/opengl/texture/cube_basic.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/opengl/texture/cube_types.hpp>
#include <sge/opengl/texture/init.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/convert/cube_side.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>


sge::opengl::texture::cube::cube(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::cube_parameters const &_parameters
)
:
	sge::opengl::texture::cube_basic(
		_basic_parameters,
		*sge::opengl::context::use<
			sge::opengl::texture::cube_context
		>(
			_basic_parameters.system_context()
		).cube_texture_type(),
		_parameters
	),
	size_(
		_parameters.size()
	),
	sides_()
{
	sge::opengl::texture::cube_context &context(
		sge::opengl::context::use<
			sge::opengl::texture::cube_context
		>(
			_basic_parameters.system_context()
		)
	);

	sge::opengl::texture::scoped_work_binding const binding(
		_basic_parameters.system_context(),
		_basic_parameters.device_context(),
		this->type(),
		this->id()
	);

	FCPPT_FOREACH_ENUMERATOR(
		index,
		sge::renderer::texture::cube_side
	)
	{
		fcppt::container::ptr::push_back_unique_ptr(
			sides_,
			fcppt::make_unique_ptr<
				buffer_vector
			>()
		);

		sge::opengl::texture::init<
			sge::opengl::texture::cube_types
		>(
			binding,
			sides_.back(),
			_basic_parameters,
			_parameters,
			*context.cube_texture_type(),
			sge::opengl::texture::convert::cube_side(
				*context.cube_sides(),
				index
			),
			this->id()
		);
	}
}

sge::opengl::texture::cube::~cube()
{
}

sge::opengl::texture::cube::size_type
sge::opengl::texture::cube::border_size() const
{
	return size_;
}

sge::renderer::texture::cube::color_buffer &
sge::opengl::texture::cube::level(
	sge::renderer::texture::cube_side::type const _side,
	sge::renderer::texture::mipmap::level const _level
)
{
	return
		sides_[
			_side
		][
			_level.get()
		];
}

sge::renderer::texture::cube::color_buffer const &
sge::opengl::texture::cube::level(
	sge::renderer::texture::cube_side::type const _side,
	sge::renderer::texture::mipmap::level const _level
) const
{
	return
		sides_[
			_side
		][
			_level.get()
		];
}

sge::renderer::texture::mipmap::level_count const
sge::opengl::texture::cube::levels() const
{
	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::texture::mipmap::level_count
		>(
			sides_[
				sge::renderer::texture::cube_side::front
			].size()
		);
}
