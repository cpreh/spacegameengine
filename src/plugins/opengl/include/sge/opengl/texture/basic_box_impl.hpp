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


#ifndef SGE_OPENGL_TEXTURE_BASIC_BOX_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BOX_IMPL_HPP_INCLUDED

#include <sge/opengl/texture/basic_box.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/init.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>


template<
	typename Types
>
sge::opengl::texture::basic_box<
	Types
>::basic_box(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::opengl::texture::type const _type,
	parameters_type const &_parameters
)
:
	base_type(
		_basic_parameters,
		_type,
		_parameters
	),
	size_(
		_parameters.size()
	),
	levels_()
{
	sge::opengl::texture::scoped_work_binding const binding(
		_basic_parameters.system_context(),
		_basic_parameters.device_context(),
		this->type(),
		this->id()
	);

	sge::opengl::texture::init<
		Types
	>(
		binding,
		levels_,
		_basic_parameters,
		_parameters,
		_type,
		sge::opengl::texture::buffer_type(
			_type.get()
		),
		this->id()
	);
}

template<
	typename Types
>
sge::opengl::texture::basic_box<
	Types
>::~basic_box()
{
}

template<
	typename Types
>
typename sge::opengl::texture::basic_box<
	Types
>::color_buffer &
sge::opengl::texture::basic_box<
	Types
>::level(
	sge::renderer::texture::mipmap::level const _level
)
{
	return
		levels_[
			_level.get()
		];
}

template<
	typename Types
>
typename sge::opengl::texture::basic_box<
	Types
>::color_buffer const &
sge::opengl::texture::basic_box<
	Types
>::level(
	sge::renderer::texture::mipmap::level const _level
) const
{
	return
		levels_[
			_level.get()
		];
}

template<
	typename Types
>
sge::renderer::texture::mipmap::level_count const
sge::opengl::texture::basic_box<
	Types
>::levels() const
{
	return
		fcppt::strong_typedef_construct_cast<
			sge::renderer::texture::mipmap::level_count
		>(
			levels_.size()
		);
}

#endif
