#include <sge/scenic/render_context/cg/manager.hpp>
#include <sge/scenic/render_context/cg/object.hpp>
#include <sge/shader/context.hpp>
#include <sge/config/media_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sge::scenic::render_context::cg::manager::manager(
	sge::shader::context &_shader_context,
	sge::renderer::vertex_declaration &_vertex_declaration)
:
	sge::scenic::render_context::manager_base(),
	shader_(
		_shader_context,
		_vertex_declaration,
		sge::shader::vertex_program_path(
			sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("ffp.cg")),
		sge::shader::pixel_program_path(
			sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("ffp.cg"))),
	world_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world"),
		sge::shader::parameter::is_projection_matrix(
			false),
		sge::renderer::matrix4()),
	world_projection_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world_projection"),
		sge::shader::parameter::is_projection_matrix(
			true),
		sge::renderer::matrix4()),
	world_inverse_transpose_matrix_(
		shader_.vertex_program(),
		sge::shader::parameter::name(
			"camera.world_it"),
		sge::shader::parameter::is_projection_matrix(
			false),
		sge::renderer::matrix4()),
	diffuse_texture_(
		shader_,
		shader_.context().renderer(),
		shader_.pixel_program(),
		sge::shader::parameter::name(
			"diffuse_texture"),
		sge::shader::parameter::planar_texture::optional_value())
{
}

sge::scenic::render_context::base_unique_ptr
sge::scenic::render_context::cg::manager::create_context(
	sge::renderer::context::object &_context)
{
	return
		sge::scenic::render_context::base_unique_ptr(
			fcppt::make_unique_ptr<sge::scenic::render_context::cg::object>(
				fcppt::ref(
					*this),
				fcppt::ref(
					_context)));
}

sge::scenic::render_context::cg::manager::~manager()
{
}
