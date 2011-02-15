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
	typename AddressMode
>
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode
>::basic_parameters(
	Dim const &_dim,
	sge::image::color::format::type const _color_format,
	texture::filter::object const &_filter,
	AddressMode const &_address_mode,
	renderer::resource_flags_field const &_resource_flags
)
:
	dim_(_dim),
	color_format_(_color_format),
	filter_(_filter),
	address_mode_(_address_mode),
	resource_flags_(_resource_flags)
{
}

template<
	typename Dim,
	typename AddressMode
>
Dim const &
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode
>::dim() const
{
	return dim_;
}

template<
	typename Dim,
	typename AddressMode
>
sge::image::color::format::type
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode
>::color_format() const
{
	return color_format_;
}

template<
	typename Dim,
	typename AddressMode
>
sge::renderer::texture::filter::object const &
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode
>::filter() const
{
	return filter_;
}

template<
	typename Dim,
	typename AddressMode
>
AddressMode const &
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode
>::address_mode() const
{
	return address_mode_;
}

template<
	typename Dim,
	typename AddressMode
>
sge::renderer::resource_flags_field const &
sge::renderer::texture::basic_parameters<
	Dim,
	AddressMode
>::resource_flags() const
{
	return resource_flags_;
}

#endif
