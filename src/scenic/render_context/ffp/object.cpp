#include <sge/image/colors.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/ffp/lighting/light/object.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/address/mode_all.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <sge/scenic/index_buffer_range.hpp>
#include <sge/renderer/state/core/sampler/filter/trilinear.hpp>
#include <sge/renderer/state/ffp/lighting/enabled.hpp>
#include <sge/renderer/state/ffp/lighting/object.hpp>
#include <sge/renderer/state/ffp/lighting/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/material/object.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/scenic/render_context/ffp/manager.hpp>
#include <sge/scenic/render_context/material/object.hpp>
#include <sge/scenic/render_context/ffp/object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assign/make_map.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>

namespace
{
struct light_visitor
{
	typedef
	sge::renderer::state::ffp::lighting::light::variant
	result_type;

	result_type
	operator()(
		sge::scenic::render_context::light::point const &p) const
	{
		return
			sge::renderer::state::ffp::lighting::light::point(
				sge::renderer::state::ffp::lighting::light::position(
					p.position().get()),
				sge::renderer::state::ffp::lighting::light::attenuation(
					sge::renderer::state::ffp::lighting::light::constant_attenuation(
						p.attenuation().constant_attenuation().get()),
					sge::renderer::state::ffp::lighting::light::linear_attenuation(
						p.attenuation().linear_attenuation().get()),
					sge::renderer::state::ffp::lighting::light::quadratic_attenuation(
						p.attenuation().quadratic_attenuation().get())));
	}

	result_type
	operator()(
		sge::scenic::render_context::light::directional const &p) const
	{
		return
			sge::renderer::state::ffp::lighting::light::directional(
				sge::renderer::state::ffp::lighting::light::direction(
					p.direction().get()));
	}
};

sge::renderer::state::ffp::lighting::light::parameters const
transform_light(
	sge::scenic::render_context::light::object const &_light)
{
	return
		sge::renderer::state::ffp::lighting::light::parameters(
			sge::renderer::state::ffp::lighting::diffuse_color(
				_light.diffuse_color().get()),
			sge::renderer::state::ffp::lighting::specular_color(
				_light.specular_color().get()),
			sge::renderer::state::ffp::lighting::ambient_color(
				_light.ambient_color().get()),
			fcppt::variant::apply_unary(
				light_visitor(),
				_light.variant()));
}
}

sge::scenic::render_context::ffp::object::object(
	sge::scenic::render_context::ffp::manager &_manager,
	sge::renderer::context::ffp &_context)
:
	manager_(
		_manager),
	context_(
		_context),
	scoped_vertex_declaration_(
		context_,
		manager_.vertex_declaration_),
	projection_transform_(),
	world_transform_(),
	current_vertex_buffer_size_(
		0u),
	current_vertex_buffer_(),
	current_material_(),
	diffuse_texture_sampler_(
		manager_.renderer_.create_sampler_state(
			sge::renderer::state::core::sampler::parameters(
				sge::renderer::state::core::sampler::address::parameters(
					sge::renderer::state::core::sampler::address::mode_all(
						sge::renderer::state::core::sampler::address::mode::repeat)),
				sge::renderer::state::core::sampler::filter::trilinear()))),
	scoped_sampler_(
		_context,
		fcppt::assign::make_map<sge::renderer::state::core::sampler::const_object_ref_map>
		(
			sge::renderer::texture::stage(
				0u),
			fcppt::cref(
				*diffuse_texture_sampler_))),
	current_lighting_(
		manager_.renderer_.create_lighting_state(
			sge::renderer::state::ffp::lighting::parameters(
				sge::renderer::state::ffp::lighting::enabled(
					sge::renderer::state::ffp::lighting::ambient_color(
						sge::image::colors::white()))))),
	depth_stencil_state_(
		manager_.renderer_.create_depth_stencil_state(
			sge::renderer::state::core::depth_stencil::parameters(
				sge::renderer::state::core::depth_stencil::depth::variant(
					sge::renderer::state::core::depth_stencil::depth::enabled(
						sge::renderer::state::core::depth_stencil::depth::func::less,
						sge::renderer::state::core::depth_stencil::depth::write_enable(
							true))),
				sge::renderer::state::core::depth_stencil::stencil::off()))),
	blend_state_(
		manager_.renderer_.create_blend_state(
			sge::renderer::state::core::blend::parameters(
				sge::renderer::state::core::blend::alpha_off(),
				sge::renderer::state::core::blend::write_mask_all()))),
	rasterizer_state_(
		manager_.renderer_.create_rasterizer_state(
			sge::renderer::state::core::rasterizer::parameters(
				sge::renderer::state::core::rasterizer::cull_mode::counter_clockwise,
				sge::renderer::state::core::rasterizer::fill_mode::solid,
				sge::renderer::state::core::rasterizer::enable_scissor_test(
					false)))),
	scoped_depth_stencil_state_(
		_context,
		*depth_stencil_state_),
	scoped_blend_state_(
		_context,
		*blend_state_),
	scoped_rasterizer_state_(
		_context,
		*rasterizer_state_)
{
	context_.lighting_state(
		sge::renderer::state::ffp::lighting::const_optional_object_ref(
			*current_lighting_));
}

void
sge::scenic::render_context::ffp::object::transform(
	sge::scenic::render_context::transform_matrix_type::type const _type,
	sge::renderer::matrix4 const &_matrix)
{
	switch(_type)
	{
	case sge::scenic::render_context::transform_matrix_type::projection:
		projection_transform_.take(
			manager_.renderer_.create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					_matrix)));
		context_.transform(
			sge::renderer::state::ffp::transform::mode::projection,
			sge::renderer::state::ffp::transform::const_optional_object_ref(
				*projection_transform_));
		break;
	case sge::scenic::render_context::transform_matrix_type::world:
		world_transform_.take(
			manager_.renderer_.create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					_matrix)));
		context_.transform(
			sge::renderer::state::ffp::transform::mode::world,
			sge::renderer::state::ffp::transform::const_optional_object_ref(
				*world_transform_));
		break;
	}
}

void
sge::scenic::render_context::ffp::object::material(
	sge::scenic::render_context::material::object const &_material)
{
	current_material_.take(
		manager_.renderer_.create_material_state(
			sge::renderer::state::ffp::lighting::material::parameters(
				sge::renderer::state::ffp::lighting::diffuse_color(
					_material.diffuse_color().get()),
				sge::renderer::state::ffp::lighting::ambient_color(
					_material.ambient_color().get()),
				sge::renderer::state::ffp::lighting::specular_color(
					_material.specular_color().get()),
				sge::renderer::state::ffp::lighting::material::emissive_color(
					_material.emissive_color().get()),
				sge::renderer::state::ffp::lighting::material::shininess(
					_material.shininess().get()))));

	context_.material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref(
			*current_material_));

	context_.texture(
		_material.diffuse_texture()
		?
			sge::renderer::texture::const_optional_base_ref(
				*_material.diffuse_texture())
		:
			sge::renderer::texture::const_optional_base_ref(),
		sge::renderer::texture::stage(
			0u));
}

void
sge::scenic::render_context::ffp::object::lights(
	sge::scenic::render_context::light::sequence const &_lights)
{
	FCPPT_ASSERT_PRE(
		_lights.size() < manager_.renderer_.caps().light_indices().get());

	typedef
	boost::ptr_vector<sge::renderer::state::ffp::lighting::light::object>
	ffp_light_sequence;

	ffp_light_sequence ffp_lights;
	sge::renderer::state::ffp::lighting::light::const_object_ref_vector ffp_light_refs;

	for(
		sge::scenic::render_context::light::sequence::const_iterator current_light = _lights.begin();
		current_light != _lights.end();
		++current_light)
	{
		fcppt::container::ptr::push_back_unique_ptr(
			ffp_lights,
			manager_.renderer_.create_light_state(
				transform_light(
					*current_light)));
		ffp_light_refs.push_back(
			fcppt::cref(
				ffp_lights.back()));
	}

	context_.lights_state(
		ffp_light_refs);
}

void
sge::scenic::render_context::ffp::object::vertex_buffer(
	sge::renderer::vertex_buffer const &_vertex_buffer)
{
	current_vertex_buffer_.reset();

	current_vertex_buffer_.take(
		fcppt::make_unique_ptr<sge::renderer::scoped_vertex_buffer>(
			fcppt::ref(
				context_),
			fcppt::cref(
				_vertex_buffer)));

	current_vertex_buffer_size_ =
		_vertex_buffer.size();
}

void
sge::scenic::render_context::ffp::object::fog(
	sge::scenic::render_context::fog::optional_properties const &)
{
}

void
sge::scenic::render_context::ffp::object::render(
	sge::renderer::index_buffer const &_index_buffer,
	sge::scenic::index_buffer_range const &_index_buffer_range)
{
	context_.render_indexed(
		_index_buffer,
		sge::renderer::first_vertex(
			0u),
		current_vertex_buffer_size_,
		sge::renderer::primitive_type::triangle_list,
		_index_buffer_range.first_index(),
		_index_buffer_range.index_count());
}

sge::renderer::target::base &
sge::scenic::render_context::ffp::object::target()
{
	return
		context_.target();
}

sge::scenic::render_context::ffp::object::~object()
{
	context_.material_state(
		sge::renderer::state::ffp::lighting::material::const_optional_object_ref());

	context_.transform(
		sge::renderer::state::ffp::transform::mode::world,
		sge::renderer::state::ffp::transform::const_optional_object_ref());

	context_.transform(
		sge::renderer::state::ffp::transform::mode::projection,
		sge::renderer::state::ffp::transform::const_optional_object_ref());

	context_.texture(
		sge::renderer::texture::const_optional_base_ref(),
		sge::renderer::texture::stage(
			0u));

	context_.sampler_state(
		sge::renderer::state::core::sampler::const_optional_object_ref_map());

	context_.lights_state(
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector());

	context_.lighting_state(
		sge::renderer::state::ffp::lighting::const_optional_object_ref());
}
