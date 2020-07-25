//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/scenic/scene/identifier.hpp>
#include <sge/scenic/scene/material/ambient_color.hpp>
#include <sge/scenic/scene/material/diffuse_color.hpp>
#include <sge/scenic/scene/material/diffuse_texture_path.hpp>
#include <sge/scenic/scene/material/emissive_color.hpp>
#include <sge/scenic/scene/material/object.hpp>
#include <sge/scenic/scene/material/shininess.hpp>
#include <sge/scenic/scene/material/specular_color.hpp>
#include <sge/scenic/scene/material/specular_texture_path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::scenic::scene::material::object::object(
	sge::scenic::scene::identifier &&_identifier,
	sge::scenic::scene::material::diffuse_color _diffuse_color,
	sge::scenic::scene::material::ambient_color _ambient_color,
	sge::scenic::scene::material::specular_color _specular_color,
	sge::scenic::scene::material::emissive_color _emissive_color,
	sge::scenic::scene::material::shininess const &_shininess,
	sge::scenic::scene::material::diffuse_texture_path &&_diffuse_texture,
	sge::scenic::scene::material::specular_texture_path &&_specular_texture
)
:
	identifier_(
		std::move(
			_identifier
		)
	),
	diffuse_color_(
		std::move(
			_diffuse_color
		)
	),
	ambient_color_(
		std::move(
			_ambient_color
		)
	),
	specular_color_(
		std::move(
			_specular_color
		)
	),
	emissive_color_(
		std::move(
			_emissive_color
		)
	),
	shininess_(
		_shininess
	),
	diffuse_texture_(
		std::move(
			_diffuse_texture
		)
	),
	specular_texture_(
		std::move(
			_specular_texture
		)
	)
{
}

sge::scenic::scene::identifier const &
sge::scenic::scene::material::object::identifier() const
{
	return
		identifier_;
}

sge::scenic::scene::material::diffuse_color const &
sge::scenic::scene::material::object::diffuse_color() const
{
	return
		diffuse_color_;
}

sge::scenic::scene::material::ambient_color const &
sge::scenic::scene::material::object::ambient_color() const
{
	return
		ambient_color_;
}

sge::scenic::scene::material::specular_color const &
sge::scenic::scene::material::object::specular_color() const
{
	return
		specular_color_;
}

sge::scenic::scene::material::emissive_color const &
sge::scenic::scene::material::object::emissive_color() const
{
	return
		emissive_color_;
}

sge::scenic::scene::material::shininess const &
sge::scenic::scene::material::object::shininess() const
{
	return
		shininess_;
}

sge::scenic::scene::material::diffuse_texture_path const &
sge::scenic::scene::material::object::diffuse_texture() const
{
	return
		diffuse_texture_;
}

sge::scenic::scene::material::specular_texture_path const &
sge::scenic::scene::material::object::specular_texture() const
{
	return
		specular_texture_;
}
