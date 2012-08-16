#include <sge/scenic/render_context/cg/object.hpp>
#include <sge/scenic/render_context/cg/manager.hpp>
#include <fcppt/math/matrix/inverse.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>

sge::scenic::render_context::cg::object::object(
	sge::scenic::render_context::cg::manager &_manager,
	sge::renderer::context::object &_context)
:
	sge::scenic::render_context::base(),
	manager_(
		_manager),
	context_(
		_context),
	current_world_(),
	current_projection_()
{
}

void
sge::scenic::render_context::cg::object::transform(
	sge::renderer::matrix_mode::type const _matrix_mode,
	sge::renderer::matrix4 const &_matrix)
{
	switch(_matrix_mode)
	{
	case sge::renderer::matrix_mode::world:
		current_world_ =
			_matrix;

		manager_.world_matrix_.set(
			current_world_);

		manager_.world_inverse_transpose_matrix_.set(
			fcppt::math::matrix::inverse(
				fcppt::math::matrix::transpose(
					current_world_)));

		manager_.world_projection_matrix_.set(
			current_projection_ * current_world_);
		break;
	case sge::renderer::matrix_mode::projection:
		current_projection_ =
			_matrix;

		manager_.world_projection_matrix_.set(
			current_projection_ * current_world_);
		break;
	case sge::renderer::matrix_mode::size:
		break;
	}
}

void
sge::scenic::render_context::cg::object::diffuse_texture(
	sge::scenic::render_context::optional_planar_texture const &_texture)
{
	manager_.diffuse_texture_.set(
		_texture
		?
			sge::shader::parameter::planar_texture::optional_value(
				*_texture)
		:
			sge::shader::parameter::planar_texture::optional_value());
}

void
sge::scenic::render_context::cg::object::lights(
	sge::scenic::light_sequence const &)
{

}

sge::scenic::render_context::cg::object::~object()
{
}
