#include <sge/scenic/cg_context/manager.hpp>
#include <sge/shader/context.hpp>
#include <sge/config/media_path.hpp>
#include <fcppt/text.hpp>

sge::scenic::cg_context::manager::manager(
	sge::shader::context &_shader_context,
	sge::renderer::vertex_declaration &_vertex_declaration)
:
	shader_(
		_shader_context,
		_vertex_declaration,
		sge::shader::vertex_program_path(
			sge::config::media_path() / FCPPT_TEXT("ffp_vertex_shader.cg")),
		sge::shader::pixel_program_path(
			sge::config::media_path() / FCPPT_TEXT("ffp_pixel_shader.cg"))),
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

sge::scenic::cg_context::manager::~manager()
{
}
