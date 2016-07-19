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


#ifndef SGE_OPENGL_TEXTURE_BASIC_IMPL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_IMPL_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/basic.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/mipmap/generate.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>


template<
	typename Types
>
sge::opengl::texture::basic<
	Types
>::basic(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::opengl::texture::type const _type,
	parameters_type const &_parameters
)
:
	Types::base(),
	sge::opengl::texture::base(
		_type
	),
	log_{
		_basic_parameters.log()
	},
	context_(
		_basic_parameters.context()
	),
	resource_flags_(
		_parameters.resource_flags()
	),
	capabilities_(
		_parameters.capabilities()
	),
	mipmap_(
		_parameters.mipmap()
	)
{
}

template<
	typename Types
>
sge::opengl::texture::basic<
	Types
>::~basic()
{
}

template<
	typename Types
>
sge::renderer::resource_flags_field
sge::opengl::texture::basic<
	Types
>::resource_flags() const
{
	return
		resource_flags_;
}

template<
	typename Types
>
sge::renderer::texture::capabilities_field
sge::opengl::texture::basic<
	Types
>::capabilities() const
{
	return
		capabilities_;
}

template<
	typename Types
>
sge::renderer::texture::mipmap::object
sge::opengl::texture::basic<
	Types
>::mipmap() const
{
	return
		mipmap_;
}

template<
	typename Types
>
sge::opengl::context::object &
sge::opengl::texture::basic<
	Types
>::context() const
{
	return
		context_;
}

template<
	typename Types
>
void
sge::opengl::texture::basic<
	Types
>::generate_mipmaps()
{
	sge::opengl::texture::scoped_work_binding const binding(
		log_,
		context_,
		this->type(),
		this->id()
	);

	sge::opengl::texture::mipmap::generate(
		binding,
		context_,
		this->type()
	);
}

#endif
