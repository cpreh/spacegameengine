//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_SCENE_MATERIAL_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MATERIAL_OBJECT_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/scene/identifier.hpp>
#include <sge/scenic/scene/material/ambient_color.hpp>
#include <sge/scenic/scene/material/diffuse_color.hpp>
#include <sge/scenic/scene/material/diffuse_texture_path.hpp>
#include <sge/scenic/scene/material/emissive_color.hpp>
#include <sge/scenic/scene/material/shininess.hpp>
#include <sge/scenic/scene/material/specular_color.hpp>
#include <sge/scenic/scene/material/specular_texture_path.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
namespace material
{
class object
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	object(
		sge::scenic::scene::identifier const &,
		sge::scenic::scene::material::diffuse_color const &,
		sge::scenic::scene::material::ambient_color const &,
		sge::scenic::scene::material::specular_color const &,
		sge::scenic::scene::material::emissive_color const &,
		sge::scenic::scene::material::shininess const &,
		sge::scenic::scene::material::diffuse_texture_path const &,
		sge::scenic::scene::material::specular_texture_path const &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::identifier const &
	identifier() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::diffuse_color const &
	diffuse_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::ambient_color const &
	ambient_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::specular_color const &
	specular_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::emissive_color const &
	emissive_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::shininess const &
	shininess() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::diffuse_texture_path const &
	diffuse_texture() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::specular_texture_path const &
	specular_texture() const;
private:
	sge::scenic::scene::identifier identifier_;
	sge::scenic::scene::material::diffuse_color diffuse_color_;
	sge::scenic::scene::material::ambient_color ambient_color_;
	sge::scenic::scene::material::specular_color specular_color_;
	sge::scenic::scene::material::emissive_color emissive_color_;
	sge::scenic::scene::material::shininess shininess_;
	sge::scenic::scene::material::diffuse_texture_path diffuse_texture_;
	sge::scenic::scene::material::specular_texture_path specular_texture_;
};
}
}
}
}

#endif
