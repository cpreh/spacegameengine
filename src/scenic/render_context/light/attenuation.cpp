#include <sge/scenic/render_context/light/attenuation.hpp>

sge::scenic::render_context::light::attenuation::attenuation(
	sge::scenic::render_context::light::constant_attenuation const &_constant_attenuation,
	sge::scenic::render_context::light::linear_attenuation const &_linear_attenuation,
	sge::scenic::render_context::light::quadratic_attenuation const &_quadratic_attenuation)
:
	constant_attenuation_(
		_constant_attenuation),
	linear_attenuation_(
		_linear_attenuation),
	quadratic_attenuation_(
		_quadratic_attenuation)
{
}

sge::scenic::render_context::light::constant_attenuation const
sge::scenic::render_context::light::attenuation::constant_attenuation() const
{
	return
		constant_attenuation_;
}

sge::scenic::render_context::light::linear_attenuation const
sge::scenic::render_context::light::attenuation::linear_attenuation() const
{
	return
		linear_attenuation_;
}

sge::scenic::render_context::light::quadratic_attenuation const
sge::scenic::render_context::light::attenuation::quadratic_attenuation() const
{
	return
		quadratic_attenuation_;
}
