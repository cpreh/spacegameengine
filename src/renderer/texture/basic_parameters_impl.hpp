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


#ifndef SGE_RENDERER_TEXTURE_BASIC_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASIC_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/renderer/texture/basic_parameters.hpp>

template<
	typename Dim,
	typename AddressMode,
	typename Format
>
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode,
	Format
>::basic_parameters(
	Dim const &_dim,
	Format const _format,
	texture::mipmap::object const &_mipmap,
	AddressMode const &_address_mode,
	renderer::resource_flags_field const &_resource_flags,
	texture::capabilities_field const &_capabilities
)
:
	dim_(_dim),
	format_(_format),
	mipmap_(_mipmap),
	address_mode_(_address_mode),
	resource_flags_(_resource_flags),
	capabilities_(_capabilities)
{
}

template<
	typename Dim,
	typename AddressMode,
	typename Format
>
Dim const &
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode,
	Format
>::size() const
{
	return dim_;
}

template<
	typename Dim,
	typename AddressMode,
	typename Format
>
Format
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode,
	Format
>::format() const
{
	return format_;
}

template<
	typename Dim,
	typename AddressMode,
	typename Format
>
sge::renderer::texture::mipmap::object const &
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode,
	Format
>::mipmap() const
{
	return mipmap_;
}

template<
	typename Dim,
	typename AddressMode,
	typename Format
>
AddressMode const &
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode,
	Format
>::address_mode() const
{
	return address_mode_;
}

template<
	typename Dim,
	typename AddressMode,
	typename Format
>
sge::renderer::resource_flags_field const &
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode,
	Format
>::resource_flags() const
{
	return resource_flags_;
}

template<
	typename Dim,
	typename AddressMode,
	typename Format
>
sge::renderer::texture::capabilities_field const &
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode,
	Format
>::capabilities() const
{
	return capabilities_;
}

#endif
