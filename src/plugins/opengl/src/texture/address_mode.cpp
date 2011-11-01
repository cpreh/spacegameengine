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


#include <sge/opengl/texture/address_mode.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/convert/address_mode.hpp>
#include <sge/opengl/texture/convert/address_mode_type.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/address_mode3.hpp>


namespace
{

template<
	typename Mode
>
void
address_mode_one(
	sge::opengl::texture::scoped_work_bind const &_binding,
	sge::opengl::texture::type const _type,
	Mode const &_mode
)
{
	sge::opengl::texture::funcs::parameter_int(
		_binding,
		_type,
		sge::opengl::texture::convert::address_mode_type<
			Mode
		>::get(),
		static_cast<
			GLint
		>(
			sge::opengl::texture::convert::address_mode(
				_mode.get()
			)
		)
	);
}

void
address_mode_impl(
	sge::opengl::texture::scoped_work_bind const &_binding,
	sge::opengl::texture::type const _type,
	sge::renderer::texture::address_mode2 const &_mode
)
{
	address_mode_one(
		_binding,
		_type,
		_mode.address_mode_s()
	);

	address_mode_one(
		_binding,
		_type,
		_mode.address_mode_t()
	);
}

void
address_mode_impl(
	sge::opengl::texture::scoped_work_bind const &_binding,
	sge::opengl::texture::type const _type,
	sge::renderer::texture::address_mode3 const &_mode
)
{
	address_mode_impl(
		_binding,
		_type,
		sge::renderer::texture::address_mode2(
			_mode.address_mode_s(),
			_mode.address_mode_t()
		)
	);

	address_mode_one(
		_binding,
		_type,
		_mode.address_mode_u()
	);
}

}

template<
	typename Mode
>
void
sge::opengl::texture::address_mode(
	texture::scoped_work_bind const &_binding,
	texture::type const _type,
	Mode const &_mode
)
{
	::address_mode_impl(
		_binding,
		_type,
		_mode
	);
}

#define SGE_OPENGL_TEXTURE_INSTANTIATE_ADDRESS_MODE(\
	mode\
)\
template \
void \
sge::opengl::texture::address_mode<\
	mode \
>( \
	sge::opengl::texture::scoped_work_bind const &,\
	sge::opengl::texture::type, \
	mode const & \
)

SGE_OPENGL_TEXTURE_INSTANTIATE_ADDRESS_MODE(
	sge::renderer::texture::address_mode2
);

SGE_OPENGL_TEXTURE_INSTANTIATE_ADDRESS_MODE(
	sge::renderer::texture::address_mode3
);
