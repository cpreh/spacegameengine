//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_CONTEXT_MATERIAL_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_MATERIAL_OBJECT_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/ambient_color.hpp>
#include <sge/scenic/render_context/diffuse_color.hpp>
#include <sge/scenic/render_context/emissive_color.hpp>
#include <sge/scenic/render_context/specular_color.hpp>
#include <sge/scenic/render_context/material/diffuse_texture.hpp>
#include <sge/scenic/render_context/material/shininess.hpp>
#include <sge/scenic/render_context/material/specular_texture.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace material
{
class object
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	object(
		sge::scenic::render_context::diffuse_color,
		sge::scenic::render_context::ambient_color,
		sge::scenic::render_context::specular_color,
		sge::scenic::render_context::emissive_color,
		sge::scenic::render_context::material::shininess const &,
		sge::scenic::render_context::material::diffuse_texture const &,
		sge::scenic::render_context::material::specular_texture const &
	);

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::diffuse_color const &
	diffuse_color() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::ambient_color const &
	ambient_color() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::specular_color const &
	specular_color() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::emissive_color const &
	emissive_color() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::material::shininess const &
	shininess() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::material::diffuse_texture const &
	diffuse_texture() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::material::specular_texture const &
	specular_texture() const;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	bool
	operator==(
		sge::scenic::render_context::material::object const &) const;
private:
	sge::scenic::render_context::diffuse_color diffuse_color_;
	sge::scenic::render_context::ambient_color ambient_color_;
	sge::scenic::render_context::specular_color specular_color_;
	sge::scenic::render_context::emissive_color emissive_color_;
	sge::scenic::render_context::material::shininess shininess_;
	sge::scenic::render_context::material::diffuse_texture diffuse_texture_;
	sge::scenic::render_context::material::specular_texture specular_texture_;
};
}
}
}
}

#endif
