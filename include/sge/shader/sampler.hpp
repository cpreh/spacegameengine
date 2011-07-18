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


#ifndef SGE_SHADER_SAMPLER_HPP_INCLUDED
#define SGE_SHADER_SAMPLER_HPP_INCLUDED

#include <sge/shader/symbol.hpp>
#include <sge/shader/texture_variant.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/base_ptr.hpp>

namespace sge
{
namespace shader
{
class sampler
{
public:
	typedef
	int
	texture_unit_type;

	// Initializing with an empty texture is ok
	SGE_SHADER_SYMBOL explicit
	sampler(
		renderer::glsl::string const &name,
		shader::texture_variant const &);

	SGE_SHADER_SYMBOL renderer::glsl::string const
	name() const;

	SGE_SHADER_SYMBOL renderer::glsl::string const
	declaration() const;

	// The shader sets this
	SGE_SHADER_SYMBOL void
	texture_unit(
		texture_unit_type);

	// This is needed on shader activation
	SGE_SHADER_SYMBOL texture_unit_type
	texture_unit() const;

	// This is needed on shader activation
	SGE_SHADER_SYMBOL renderer::texture::base_ptr const
	texture() const;

	// In insula, we need to update the reflection texture, so we need
	// this
	SGE_SHADER_SYMBOL void
	texture(
		shader::texture_variant const &);
	
	SGE_SHADER_SYMBOL ~sampler();
private:
	renderer::glsl::string name_,declaration_;
	shader::texture_variant texture_;
	texture_unit_type texture_unit_;
};
}
}

#endif
