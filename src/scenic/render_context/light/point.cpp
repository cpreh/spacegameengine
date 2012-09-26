#include <sge/scenic/render_context/light/point.hpp>

sge::scenic::render_context::light::point::point(
	sge::scenic::render_context::light::position const &_position,
	sge::scenic::render_context::light::attenuation const &_attenuation)
:
	position_(
		_position),
	attenuation_(
		_attenuation)
{
}

sge::scenic::render_context::light::position const &
sge::scenic::render_context::light::point::position() const
{
	return
		position_;
}

sge::scenic::render_context::light::attenuation const &
sge::scenic::render_context::light::point::attenuation() const
{
	return
		attenuation_;
}
