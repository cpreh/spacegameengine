/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../cube.hpp"
#include "../cube_context.hpp"
#include "../planar.hpp"
#include "../convert/cube_side.hpp"
#include "../../common.hpp"
#include "../../context/use.hpp"
#include "../../glew/is_supported.hpp"
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>

sge::opengl::texture::cube::cube(
	opengl::context::object &_context,
	renderer::texture::cube_parameters const &_param
)
:
	opengl::texture::base(
		opengl::context::use<
			texture::cube_context
		>(
			_context
		).cube_texture_type()
	),
	size_(
		_param.size()
	),
	locked_texture_(0)
{
	texture::cube_context &context(
		opengl::context::use<
			texture::cube_context
		>(
			_context
		)
	);

	if(
		!context.have_cube_texture()
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("cube texture"),
			FCPPT_TEXT("1.3"),
	       		FCPPT_TEXT("gl_arb_texture::cube")
		);

	sge::renderer::texture::planar_parameters const planar_param(
		texture::planar::dim(
			size_,
			size_
		),
		_param.format(),
		_param.mipmap(),
		_param.address_mode(),
		_param.resource_flags(),
		_param.capabilities()

	);

	FCPPT_FOREACH_ENUMERATOR(
		index,
		sge::renderer::texture::cube_side
	)
		fcppt::container::ptr::push_back_unique_ptr(
			textures_,
			fcppt::make_unique_ptr<
				texture::planar
			>(
				fcppt::ref(
					_context
				),
				planar_param,
				convert::cube_side(
					context.cube_sides(),
					index
				)
			)
		);
}

sge::opengl::texture::cube::~cube()
{
}

sge::opengl::texture::cube::view const
sge::opengl::texture::cube::lock(
	renderer::texture::cube_side::type const _side,
	renderer::lock_rect const &_src,
	renderer::lock_mode::type const _flags
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
	renderer::texture::cube_side::type const _side,
	renderer::lock_rect const &_src
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

	locked_texture_ = 0;
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
		throw renderer::exception(
			FCPPT_TEXT("ogl::texture::cube: not locked!")
		);
}

void
sge::opengl::texture::cube::check_not_locked() const
{
	if(
		locked_texture_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl::texture::cube: already locked!")
		);
}
