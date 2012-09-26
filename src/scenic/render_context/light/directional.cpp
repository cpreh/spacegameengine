#include <sge/scenic/render_context/light/directional.hpp>

sge::scenic::render_context::light::directional::directional(
	sge::scenic::render_context::light::direction const &_direction)
:
	direction_(
		_direction)
{
}

sge::scenic::render_context::light::direction const &
sge::scenic::render_context::light::directional::direction() const
{
	return
		direction_;
}
