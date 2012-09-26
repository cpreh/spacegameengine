#include <sge/scenic/scene/material/from_obj_material.hpp>

sge::scenic::scene::material::object const
sge::scenic::scene::material::from_obj_material(
	sge::model::obj::material::object const &_material)
{
	return
		sge::scenic::scene::material::object(
			sge::scenic::scene::identifier(
				_material.identifier().get()),
			sge::scenic::scene::material::diffuse_color(
				_material.diffuse_color().get()),
			sge::scenic::scene::material::ambient_color(
				_material.ambient_color().get()),
			sge::scenic::scene::material::specular_color(
				_material.specular_color().get()),
			sge::scenic::scene::material::emissive_color(
				_material.emissive_color().get()),
			sge::scenic::scene::material::shininess(
				_material.shininess().get()),
			sge::scenic::scene::material::diffuse_texture_path(
				_material.diffuse_texture().get()),
			sge::scenic::scene::material::specular_texture_path(
				_material.specular_texture().get()));
}
