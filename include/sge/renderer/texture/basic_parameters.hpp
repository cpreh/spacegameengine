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


#ifndef SGE_RENDERER_TEXTURE_BASIC_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_BASIC_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/texture/basic_parameters_fwd.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>

namespace sge
{
namespace renderer
{
namespace texture
{

template<
	typename Dim,
	typename AddressMode
>
class basic_parameters
{
public:
	SGE_RENDERER_SYMBOL
	basic_parameters(
		Dim const &,
		sge::image::color::format::type,
		texture::mipmap::object const &,
		AddressMode const &,
		renderer::resource_flags_field const &,
		texture::capabilities_field const &
	);

	SGE_RENDERER_SYMBOL
	Dim const &
	size() const;

	SGE_RENDERER_SYMBOL
	sge::image::color::format::type
	color_format() const;

	SGE_RENDERER_SYMBOL
	texture::mipmap::object const &
	mipmap() const;

	SGE_RENDERER_SYMBOL
	AddressMode const &
	address_mode() const;

	SGE_RENDERER_SYMBOL
	renderer::resource_flags_field const &
	resource_flags() const;

	SGE_RENDERER_SYMBOL
	texture::capabilities_field const &
	capabilities() const;
private:
	Dim dim_;

	sge::image::color::format::type color_format_;

	texture::mipmap::object mipmap_;

	AddressMode address_mode_;

	renderer::resource_flags_field resource_flags_;

	texture::capabilities_field capabilities_;
};

}
}
}

#endif
