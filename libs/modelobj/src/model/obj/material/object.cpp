//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/model/obj/material/object.hpp>

sge::model::obj::material::object::object(
	sge::model::obj::identifier const &_identifier,
	sge::model::obj::material::diffuse_color const &_diffuse_color,
	sge::model::obj::material::ambient_color const &_ambient_color,
	sge::model::obj::material::specular_color const &_specular_color,
	sge::model::obj::material::emissive_color const &_emissive_color,
	sge::model::obj::material::shininess const &_shininess,
	sge::model::obj::material::diffuse_texture_path const &_diffuse_texture,
	sge::model::obj::material::specular_texture_path const &_specular_texture)
:
	identifier_(
		_identifier),
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

sge::model::obj::identifier const &
sge::model::obj::material::object::identifier() const
{
	return
		identifier_;
}

sge::model::obj::material::diffuse_color const &
sge::model::obj::material::object::diffuse_color() const
{
	return
		diffuse_color_;
}

sge::model::obj::material::ambient_color const &
sge::model::obj::material::object::ambient_color() const
{
	return
		ambient_color_;
}

sge::model::obj::material::specular_color const &
sge::model::obj::material::object::specular_color() const
{
	return
		specular_color_;
}

sge::model::obj::material::emissive_color const &
sge::model::obj::material::object::emissive_color() const
{
	return
		emissive_color_;
}

sge::model::obj::material::shininess const &
sge::model::obj::material::object::shininess() const
{
	return
		shininess_;
}

sge::model::obj::material::diffuse_texture_path const &
sge::model::obj::material::object::diffuse_texture() const
{
	return
		diffuse_texture_;
}

sge::model::obj::material::specular_texture_path const &
sge::model::obj::material::object::specular_texture() const
{
	return
		specular_texture_;
}
