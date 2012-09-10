#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_LIGHT_DIRECTIONAL_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_LIGHT_DIRECTIONAL_HPP_INCLUDED

#include <sge/renderer/ambient_color.hpp>
#include <sge/renderer/diffuse_color.hpp>
#include <sge/renderer/specular_color.hpp>
#include <sge/renderer/light/direction_fwd.hpp>
#include <sge/scenic/render_context/cg/light/index.hpp>
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
class directional
{
FCPPT_NONCOPYABLE(
	directional);
public:
	directional(
		sge::cg::program::object &,
		sge::scenic::render_context::cg::light::index const &);

	void
	diffuse_color(
		sge::renderer::diffuse_color const &);

	void
	specular_color(
		sge::renderer::specular_color const &);

	void
	ambient_color(
		sge::renderer::ambient_color const &);

	void
	camera_space_direction(
		sge::renderer::light::direction const &);

	~directional();
private:
	sge::shader::parameter::vector<sge::renderer::scalar,4> diffuse_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> specular_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> ambient_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,3> camera_space_direction_;
};
}
}
}
}
}

#endif
