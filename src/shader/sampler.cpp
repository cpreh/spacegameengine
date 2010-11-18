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


#include <sge/shader/sampler.hpp>
#include <fcppt/text.hpp>
#include <limits>

sge::shader::sampler::sampler(
	sge::renderer::glsl::string const &_name,
	sge::renderer::texture_base_ptr const _texture)
:
	name_(
		_name),
	declaration_(
		FCPPT_TEXT("uniform sampler2D ")+_name+FCPPT_TEXT(";")),
	texture_(
		_texture),
	texture_unit_(
		std::numeric_limits<texture_unit_type>::max())
{
}

sge::renderer::glsl::string const
sge::shader::sampler::name() const
{
	return name_;
}

sge::renderer::glsl::string const
sge::shader::sampler::declaration() const
{
	return declaration_;
}

void
sge::shader::sampler::texture_unit(
	texture_unit_type const _texture_unit)
{
	texture_unit_ = _texture_unit;
}

// This is needed on shader activation
sge::shader::sampler::texture_unit_type
sge::shader::sampler::texture_unit() const
{
	return texture_unit_;
}

// This is needed on shader activation
sge::renderer::texture_base_ptr const
sge::shader::sampler::texture() const
{
	return texture_;
}

void
sge::shader::sampler::texture(
	sge::renderer::texture_base_ptr const _texture)
{
	texture_ = _texture;
}

sge::shader::sampler::~sampler()
{
}
