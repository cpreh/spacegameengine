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
#include <sge/opengl/texture/cube.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/planar.hpp>
#include <sge/opengl/texture/convert/cube_side.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/dim/object_impl.hpp>


sge::opengl::texture::cube::cube(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::cube_parameters const &_parameters
)
:
	sge::opengl::texture::base(
		sge::opengl::context::use<
			sge::opengl::texture::cube_context
		>(
			_basic_parameters.system_context()
		).cube_texture_type()
	),
	size_(
		_parameters.size()
	),
	locked_texture_(
		fcppt::null_ptr()
	),
	textures_()
{
	sge::opengl::texture::cube_context &context(
		sge::opengl::context::use<
			sge::opengl::texture::cube_context
		>(
			_basic_parameters.system_context()
		)
	);

	sge::renderer::texture::planar_parameters const planar_param(
		sge::opengl::texture::planar::dim(
			size_,
			size_
		),
		_parameters.format(),
		_parameters.mipmap(),
		_parameters.resource_flags(),
		_parameters.capabilities()

	);

	FCPPT_FOREACH_ENUMERATOR(
		index,
		sge::renderer::texture::cube_side
	)
		fcppt::container::ptr::push_back_unique_ptr(
			textures_,
			fcppt::make_unique_ptr<
				sge::opengl::texture::planar
			>(
				fcppt::cref(
					_basic_parameters
				),
				planar_param,
				sge::opengl::texture::optional_type(
					sge::opengl::texture::convert::cube_side(
						context.cube_sides(),
						index
					)
				)
			)
		);
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
		textures_[
			_side
		].level(
			_level
		);

}

sge::renderer::texture::cube::color_buffer const &
sge::opengl::texture::cube::level(
	sge::renderer::texture::cube_side::type const _side,
	sge::renderer::texture::mipmap::level const _level
) const
{
	return
		textures_[
			_side
		].level(
			_level
		);
}

sge::renderer::texture::mipmap::level_count const
sge::opengl::texture::cube::levels() const
{
	return
		this->ref_texture().levels();
}

sge::renderer::resource_flags_field const
sge::opengl::texture::cube::resource_flags() const
{
	return
		this->ref_texture().resource_flags();
}

sge::renderer::texture::capabilities_field const
sge::opengl::texture::cube::capabilities() const
{
	return
		this->ref_texture().capabilities();
}

sge::renderer::texture::mipmap::object const
sge::opengl::texture::cube::mipmap() const
{
	return
		this->ref_texture().mipmap();
}

sge::renderer::texture::planar const &
sge::opengl::texture::cube::ref_texture() const
{
	return
		textures_[0];
}
