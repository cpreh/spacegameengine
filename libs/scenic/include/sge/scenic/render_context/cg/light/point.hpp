//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_LIGHT_POINT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_LIGHT_POINT_HPP_INCLUDED

#include <sge/renderer/vector3.hpp>
#include <sge/scenic/render_context/ambient_color.hpp>
#include <sge/scenic/render_context/diffuse_color.hpp>
#include <sge/scenic/render_context/specular_color.hpp>
#include <sge/scenic/render_context/cg/light/index.hpp>
#include <sge/scenic/render_context/light/attenuation_fwd.hpp>
#include <sge/shader/parameter/vector.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace cg
{
namespace light
{
class point
{
FCPPT_NONCOPYABLE(
	point);
public:
	point(
		sge::cg::program::object &,
		sge::scenic::render_context::cg::light::index const &);

	void
	diffuse_color(
		sge::scenic::render_context::diffuse_color const &);

	void
	specular_color(
		sge::scenic::render_context::specular_color const &);

	void
	ambient_color(
		sge::scenic::render_context::ambient_color const &);

	void
	camera_space_position(
		sge::renderer::vector3 const &);

	void
	attenuation(
		sge::scenic::render_context::light::attenuation const &);

	~point();
private:
	sge::shader::parameter::vector<sge::renderer::scalar,4> diffuse_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> specular_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> ambient_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,3> camera_space_position_;
	sge::shader::parameter::vector<sge::renderer::scalar,3> attenuation_;
};
}
}
}
}
}

#endif
