/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/texture/basic_parameters_fwd.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>


namespace sge
{
namespace renderer
{
namespace texture
{

template<
	typename Dim,
	typename Format
>
class basic_parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	basic_parameters(
		Dim const &,
		Format const &,
		sge::renderer::texture::mipmap::object const &,
		sge::renderer::resource_flags_field const &,
		sge::renderer::texture::capabilities_field const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	Dim const &
	size() const;

	SGE_RENDERER_DETAIL_SYMBOL
	Format
	format() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::texture::mipmap::object const &
	mipmap() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::resource_flags_field const &
	resource_flags() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::texture::capabilities_field const &
	capabilities() const;
private:
	Dim dim_;

	Format format_;

	sge::renderer::texture::mipmap::object mipmap_;

	sge::renderer::resource_flags_field resource_flags_;

	sge::renderer::texture::capabilities_field capabilities_;
};

}
}
}

#endif
