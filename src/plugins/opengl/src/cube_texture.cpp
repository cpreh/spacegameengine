/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../common.hpp"
#include "../cube_texture.hpp"
#include "../basic_texture_impl.hpp"
#include "../texture.hpp"
#include "../cube_texture_context.hpp"
#include "../context/use.hpp"
#include "../convert/cube_side.hpp"
#include "../glew/is_supported.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_unique_ptr.hpp>

template class sge::opengl::basic_texture<
	sge::renderer::cube_texture
>;

sge::opengl::cube_texture::cube_texture(
	context::object &_context,
	size_type const _size,
	image::color::format::type const _format,
	renderer::filter::texture const &_filter,
	renderer::resource_flags_field const &_flags
)
:
	detail::cube_texture_base(
		_context,
		_filter,
		_flags,
		context::use<
			cube_texture_context
		>(
			_context
		).cube_texture_type(),
		_format
	),
	size_(_size),
	locked_texture_(0)
{
	cube_texture_context &cube_texture_context_(
		context::use<
			cube_texture_context
		>(
			_context
		)
	);

	if(
		!cube_texture_context_.have_cube_texture()
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("cube texture"),
			FCPPT_TEXT("1.3"),
	       		FCPPT_TEXT("gl_arb_cube_texture")
		);

	FCPPT_FOREACH_ENUMERATOR(
		index,
		sge::renderer::cube_side
	)
		fcppt::container::ptr::push_back_unique_ptr(
			textures_,
			fcppt::make_unique_ptr<
				texture
			>(
				std::tr1::ref(
					_context
				),
				texture::dim_type(
					size_,
					size_
				),
				_format,
				_filter,
				_flags,
				convert::cube_side(
					cube_texture_context_.cube_sides(),
					index
				)
			)
		);
}

sge::opengl::cube_texture::~cube_texture()
{
}

sge::image2d::view::object const
sge::opengl::cube_texture::lock(
	renderer::cube_side::type const _side,
	renderer::lock_rect const &_src,
	renderer::lock_mode::type const _flags
)
{
	check_not_locked();

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

sge::image2d::view::const_object const
sge::opengl::cube_texture::lock(
	renderer::cube_side::type const _side,
	renderer::lock_rect const &_src
) const
{
	check_not_locked();

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
sge::opengl::cube_texture::unlock() const
{
	check_locked();

	locked_texture_->unlock();
	locked_texture_ = 0;
}

sge::opengl::cube_texture::size_type
sge::opengl::cube_texture::border_size() const
{
	return size_;
}

void
sge::opengl::cube_texture::check_locked() const
{
	if(
		!locked_texture_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl::cube_texture: not locked!")
		);
}

void
sge::opengl::cube_texture::check_not_locked() const
{
	if(
		locked_texture_
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl::cube_texture: already locked!")
		);
}
