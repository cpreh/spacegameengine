#include <sge/scenic/render_context/light/object.hpp>

sge::scenic::render_context::light::object::object(
	sge::scenic::render_context::diffuse_color const &_diffuse_color,
	sge::scenic::render_context::specular_color const &_specular_color,
	sge::scenic::render_context::ambient_color const &_ambient_color,
	sge::scenic::render_context::light::variant const &_variant)
:
	diffuse_color_(
		_diffuse_color),
	specular_color_(
		_specular_color),
	ambient_color_(
		_ambient_color),
	variant_(
		_variant)
{
}

sge::scenic::render_context::diffuse_color const &
sge::scenic::render_context::light::object::diffuse_color() const
{
	return
		diffuse_color_;
}

sge::scenic::render_context::specular_color const &
sge::scenic::render_context::light::object::specular_color() const
{
	return
		specular_color_;
}

sge::scenic::render_context::ambient_color const &
sge::scenic::render_context::light::object::ambient_color() const
{
	return
		ambient_color_;
}

sge::scenic::render_context::light::variant const &
sge::scenic::render_context::light::object::variant() const
{
	return
		variant_;
}
