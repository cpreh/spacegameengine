#include <sge/model/obj/material.hpp>

sge::model::obj::material::material(
	sge::model::obj::identifier const &_identifier,
	sge::renderer::material const &_renderer_material,
	sge::model::obj::texture_path const &_texture)
:
	identifier_(
		_identifier),
	renderer_material_(
		_renderer_material),
	texture_(
		_texture)
{
}

sge::model::obj::identifier const &
sge::model::obj::material::identifier() const
{
	return
		identifier_;
}

sge::renderer::material const &
sge::model::obj::material::renderer_material() const
{
	return
		renderer_material_;
}

sge::model::obj::texture_path const &
sge::model::obj::material::texture() const
{
	return
		texture_;
}
