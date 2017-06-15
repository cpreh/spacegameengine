/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image2d/traits/dimension.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_lockable_buffer.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/buffer_surface_types.hpp>
#include <sge/opengl/texture/color_format_types.hpp>
#include <sge/opengl/texture/color_surface.hpp>
#include <sge/opengl/texture/cube.hpp>
#include <sge/opengl/texture/cube_basic.hpp>
#include <sge/opengl/texture/cube_config.hpp>
#include <sge/opengl/texture/cube_types.hpp>
#include <sge/opengl/texture/init.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/surface_config_fwd.hpp>
#include <sge/opengl/texture/surface_context.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/enum/array_impl.hpp>
#include <fcppt/enum/array_init.hpp>


sge::opengl::texture::cube::cube(
	sge::opengl::texture::cube_config const &_config,
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::cube_parameters const &_parameters
)
:
	sge::opengl::texture::cube_basic(
		_basic_parameters,
		_config.cube_texture_type(),
		_parameters
	),
	size_(
		_parameters.size()
	),
	sides_(
		[
			&_config,
			&_basic_parameters,
			&_parameters,
			this
		]{
			sge::opengl::texture::scoped_work_binding const binding(
				_basic_parameters.log(),
				_basic_parameters.context(),
				this->type(),
				this->id()
			);

			sge::opengl::texture::surface_config const &surface_config{
				sge::opengl::context::use<
					sge::opengl::texture::surface_context
				>(
					_basic_parameters.context()
				).config()
			};

			return
				fcppt::enum_::array_init<
					side_array
				>(
					[
						&binding,
						&surface_config,
						&_config,
						&_basic_parameters,
						&_parameters,
						this
					](
						sge::renderer::texture::cube_side const _side
					)
					{
						return
							sge::opengl::texture::init<
								sge::opengl::texture::cube_types
							>(
								binding,
								_basic_parameters,
								_parameters,
								surface_config,
								_config.cube_texture_type(),
								_config.cube_sides()[
									_side
								],
								this->id()
							);
					}
				);
		}()
	)
{
}

sge::opengl::texture::cube::~cube()
{
}

sge::renderer::size_type
sge::opengl::texture::cube::border_size() const
{
	return
		size_;
}

sge::renderer::texture::cube::nonconst_buffer &
sge::opengl::texture::cube::level(
	sge::renderer::texture::cube_side const _side,
	sge::renderer::texture::mipmap::level const _level
)
{
	return
		*sides_[
			_side
		][
			_level.get()
		];
}

sge::renderer::texture::cube::const_buffer const &
sge::opengl::texture::cube::level(
	sge::renderer::texture::cube_side const _side,
	sge::renderer::texture::mipmap::level const _level
) const
{
	return
		*sides_[
			_side
		][
			_level.get()
		];
}

sge::renderer::texture::mipmap::level_count
sge::opengl::texture::cube::levels() const
{
	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::texture::mipmap::level_count,
			fcppt::cast::size_fun
		>(
			sides_[
				sge::renderer::texture::cube_side::front
			].size()
		);
}
