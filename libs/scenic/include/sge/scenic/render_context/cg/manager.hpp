//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_MANAGER_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_MANAGER_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/manager_base.hpp>
#include <sge/scenic/render_context/cg/object_fwd.hpp>
#include <sge/scenic/render_context/cg/light/count.hpp>
#include <sge/scenic/render_context/cg/light/directional_fwd.hpp>
#include <sge/scenic/render_context/cg/light/point_fwd.hpp>
#include <sge/shader/context_fwd.hpp>
#include <sge/shader/pair.hpp>
#include <sge/shader/parameter/matrix.hpp>
#include <sge/shader/parameter/planar_texture.hpp>
#include <sge/shader/parameter/scalar.hpp>
#include <sge/shader/parameter/vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace cg
{
class manager
:
	public sge::scenic::render_context::manager_base
{
FCPPT_NONCOPYABLE(
	manager);
public:
	SGE_SCENIC_DETAIL_SYMBOL
	manager(
		sge::shader::context &,
		sge::renderer::vertex::declaration &);

	/* override */
	sge::scenic::render_context::base_unique_ptr
	create_context(
		sge::renderer::context::core &
	)
	override;

	SGE_SCENIC_DETAIL_SYMBOL
	~manager()
	override;
private:
	friend class sge::scenic::render_context::cg::object;

	typedef
	std::integral_constant
	<
		sge::scenic::render_context::cg::light::count,
		8u
	>
	max_point_lights;

	typedef
	std::integral_constant
	<
		sge::scenic::render_context::cg::light::count,
		4u
	>
	max_directional_lights;

	typedef
	std::array
	<
		fcppt::unique_ptr
		<
			sge::scenic::render_context::cg::light::point
		>,
		max_point_lights::value
	>
	point_light_array;

	typedef
	std::array
	<
		fcppt::unique_ptr
		<
			sge::scenic::render_context::cg::light::directional
		>,
		max_directional_lights::value
	>
	directional_light_array;

	sge::renderer::vertex::declaration &vertex_declaration_;
	sge::shader::pair shader_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_matrix_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_projection_matrix_;
	sge::shader::parameter::matrix<sge::renderer::scalar,4,4> world_inverse_transpose_matrix_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> material_diffuse_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> material_specular_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> material_ambient_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> material_emissive_color_;
	sge::shader::parameter::scalar<sge::renderer::scalar> material_shininess_;
	sge::shader::parameter::scalar<bool> use_diffuse_texture_;
	sge::shader::parameter::planar_texture diffuse_texture_;
	sge::shader::parameter::scalar<bool> use_specular_texture_;
	sge::shader::parameter::planar_texture specular_texture_;
	sge::shader::parameter::scalar<sge::scenic::render_context::cg::light::count> point_light_count_;
	sge::shader::parameter::scalar<sge::scenic::render_context::cg::light::count> directional_light_count_;
	sge::shader::parameter::scalar<bool> use_fog_;
	sge::shader::parameter::scalar<sge::renderer::scalar> fog_start_;
	sge::shader::parameter::scalar<sge::renderer::scalar> fog_end_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> fog_color_;
	point_light_array const point_lights_;
	directional_light_array const directional_lights_;
	sge::renderer::state::core::depth_stencil::object_unique_ptr const depth_stencil_state_;
	sge::renderer::state::core::blend::object_unique_ptr const blend_state_;
	sge::renderer::state::core::rasterizer::object_unique_ptr const rasterizer_state_;
	sge::renderer::state::core::sampler::object_unique_ptr const mipmap_sampler_state_;
};
}
}
}
}

#endif
