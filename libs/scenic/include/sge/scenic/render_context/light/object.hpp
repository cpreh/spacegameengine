//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_CONTEXT_LIGHT_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_LIGHT_OBJECT_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/ambient_color.hpp>
#include <sge/scenic/render_context/diffuse_color.hpp>
#include <sge/scenic/render_context/specular_color.hpp>
#include <sge/scenic/render_context/light/object_fwd.hpp>
#include <sge/scenic/render_context/light/variant.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace light
{
class object
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	object(
		sge::scenic::render_context::diffuse_color const &,
		sge::scenic::render_context::specular_color const &,
		sge::scenic::render_context::ambient_color const &,
		sge::scenic::render_context::light::variant const &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::diffuse_color const &
	diffuse_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::specular_color const &
	specular_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::ambient_color const &
	ambient_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::render_context::light::variant const &
	variant() const;
private:
	sge::scenic::render_context::diffuse_color diffuse_color_;
	sge::scenic::render_context::specular_color specular_color_;
	sge::scenic::render_context::ambient_color ambient_color_;
	sge::scenic::render_context::light::variant variant_;
};
}
}
}
}

#endif
