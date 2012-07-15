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
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/glew/is_supported.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/cube.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/planar.hpp>
#include <sge/opengl/texture/convert/cube_side.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
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

sge::opengl::texture::cube::view const
sge::opengl::texture::cube::lock(
	sge::renderer::texture::cube_side::type const _side,
	sge::renderer::lock_rect const &_src,
	sge::renderer::lock_mode::type const _flags
)
{
	this->check_not_locked();

	locked_texture_ =
		&textures_[
			_side
		];

	return
		locked_texture_->lock(
			_src,
			_flags
		);
}

sge::opengl::texture::cube::const_view const
sge::opengl::texture::cube::lock(
	sge::renderer::texture::cube_side::type const _side,
	sge::renderer::lock_rect const &_src
) const
{
	this->check_not_locked();

	locked_texture_ =
		&textures_[
			_side
		];

	return
		locked_texture_->lock(
			_src
		);
}

void
sge::opengl::texture::cube::unlock() const
{
	this->check_locked();

	locked_texture_->unlock();

	locked_texture_ = fcppt::null_ptr();
}

sge::opengl::texture::cube::size_type
sge::opengl::texture::cube::border_size() const
{
	return size_;
}

sge::renderer::resource_flags_field const
sge::opengl::texture::cube::resource_flags() const
{
	return textures_[0].resource_flags();
}

sge::renderer::texture::capabilities_field const
sge::opengl::texture::cube::capabilities() const
{
	return textures_[0].capabilities();
}

sge::renderer::texture::mipmap::object const
sge::opengl::texture::cube::mipmap() const
{
	return textures_[0].mipmap();
}

void
sge::opengl::texture::cube::check_locked() const
{
	if(
		!locked_texture_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl::texture::cube: not locked!")
		);
}

void
sge::opengl::texture::cube::check_not_locked() const
{
	if(
		locked_texture_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl::texture::cube: already locked!")
		);
}
