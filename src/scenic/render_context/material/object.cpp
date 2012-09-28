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


#include <sge/scenic/render_context/material/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


namespace
{
template<typename T>
bool
compare_optional_ref_identity(
	fcppt::optional<T &> const &_left,
	fcppt::optional<T &> const &_right)
{
	return
		_left.has_value() == _right.has_value() &&
		(
			!_left.has_value() ||
			&(*_left) == &(*_right)
		);
}
}

sge::scenic::render_context::material::object::object(
	sge::scenic::render_context::diffuse_color const &_diffuse_color,
	sge::scenic::render_context::ambient_color const &_ambient_color,
	sge::scenic::render_context::specular_color const &_specular_color,
	sge::scenic::render_context::emissive_color const &_emissive_color,
	sge::scenic::render_context::material::shininess const &_shininess,
	sge::scenic::render_context::material::diffuse_texture const &_diffuse_texture,
	sge::scenic::render_context::material::specular_texture const &_specular_texture)
:
	diffuse_color_(
		_diffuse_color),
	ambient_color_(
		_ambient_color),
	specular_color_(
		_specular_color),
	emissive_color_(
		_emissive_color),
	shininess_(
		_shininess),
	diffuse_texture_(
		_diffuse_texture),
	specular_texture_(
		_specular_texture)
{
}

sge::scenic::render_context::diffuse_color const &
sge::scenic::render_context::material::object::diffuse_color() const
{
	return
		diffuse_color_;
}

sge::scenic::render_context::ambient_color const &
sge::scenic::render_context::material::object::ambient_color() const
{
	return
		ambient_color_;
}

sge::scenic::render_context::specular_color const &
sge::scenic::render_context::material::object::specular_color() const
{
	return
		specular_color_;
}

sge::scenic::render_context::emissive_color const &
sge::scenic::render_context::material::object::emissive_color() const
{
	return
		emissive_color_;
}

sge::scenic::render_context::material::shininess const &
sge::scenic::render_context::material::object::shininess() const
{
	return
		shininess_;
}

sge::scenic::render_context::material::diffuse_texture const &
sge::scenic::render_context::material::object::diffuse_texture() const
{
	return
		diffuse_texture_;
}

sge::scenic::render_context::material::specular_texture const &
sge::scenic::render_context::material::object::specular_texture() const
{
	return
		specular_texture_;
}

bool
sge::scenic::render_context::material::object::operator==(
	sge::scenic::render_context::material::object const &_right) const
{
	return
		diffuse_color_ == _right.diffuse_color_ &&
		ambient_color_ == _right.ambient_color_ &&
		specular_color_ == _right.specular_color_ &&
		emissive_color_ == _right.emissive_color_ &&
		(std::abs(shininess_.get() - _right.shininess_.get()) < 0.001f) &&
		compare_optional_ref_identity(
			diffuse_texture_,
			_right.diffuse_texture_) &&
		compare_optional_ref_identity(
			specular_texture_,
			_right.specular_texture_);
}
