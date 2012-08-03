/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/camera/coordinate_system/object.hpp>
#include <sge/image/color/init.hpp>
#include <sge/scenic/exception.hpp>
#include <sge/image/color/rgb32f.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vector4.hpp>
#include <fcppt/math/vector/output.hpp>
#include <sge/scenic/mesh.hpp>
#include <sge/scenic/scene/from_blender_file.hpp>
#include <sge/scenic/scene/prototype.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/matrix/rotation_x.hpp>
#include <fcppt/math/matrix/rotation_y.hpp>
#include <fcppt/math/matrix/rotation_z.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/narrow_cast.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace
{
sge::renderer::vector3 const
from_blender_vector(
	sge::renderer::vector3 const &_v)
{
	return
		sge::renderer::vector3(
			_v.x(),
			_v.z(),
			_v.y());
}

sge::renderer::matrix4 const
rotation_from_angles_camera(
	sge::renderer::vector3 const &_angles)
{
	return
		fcppt::math::matrix::rotation_z(
			_angles.z()) *
		fcppt::math::matrix::rotation_y(
			-_angles.y()) *
		fcppt::math::matrix::rotation_x(
			-_angles.x());
}

sge::renderer::matrix4 const
rotation_from_angles_mesh(
	sge::renderer::vector3 const &_angles)
{
	return
		fcppt::math::matrix::rotation_y(
			-_angles.y()) *
		fcppt::math::matrix::rotation_z(
			-_angles.z()) *
		fcppt::math::matrix::rotation_x(
			-_angles.x());
}

sge::renderer::vector3 const
multiply_matrix4_vector3(
	sge::renderer::matrix4 const &_matrix,
	sge::renderer::vector3 const &_vector)
{
	return
		fcppt::math::vector::narrow_cast<sge::renderer::vector3>(
			_matrix *
			sge::renderer::vector4(
				_vector.x(),
				_vector.y(),
				_vector.z(),
				1.0f));
}

sge::scenic::camera_properties const
parse_camera_properties(
	sge::parse::json::object const &_json_camera)
{
	sge::renderer::matrix4 const camera_rotation(
		rotation_from_angles_camera(
			from_blender_vector(
				sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
					_json_camera,
					sge::parse::json::path(
						FCPPT_TEXT("rotation"))))));

	sge::renderer::vector3 const
		right(
			multiply_matrix4_vector3(
				camera_rotation,
				sge::renderer::vector3(1.0f,0.0f,0.0f))),
		up(
			multiply_matrix4_vector3(
				camera_rotation,
				sge::renderer::vector3(0.0f,0.0f,1.0f))),
		forward(
			multiply_matrix4_vector3(
				camera_rotation,
				sge::renderer::vector3(0.0f,-1.0f,0.0f)));

	return
		sge::scenic::camera_properties(
			sge::camera::coordinate_system::object(
				sge::camera::coordinate_system::right(
					right),
				sge::camera::coordinate_system::up(
					up),
				sge::camera::coordinate_system::forward(
					forward),
				sge::camera::coordinate_system::position(
					-from_blender_vector(
						sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
							_json_camera,
							sge::parse::json::path(
								FCPPT_TEXT("position")))))),
				sge::renderer::projection::fov(
					sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
						_json_camera,
						sge::parse::json::path(
							FCPPT_TEXT("fov")))),
				sge::renderer::projection::near(
					sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
						_json_camera,
						sge::parse::json::path(
							FCPPT_TEXT("near")))),
				sge::renderer::projection::far(
					sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
						_json_camera,
						sge::parse::json::path(
							FCPPT_TEXT("far")))));
}

sge::scenic::fog::properties const
parse_fog_properties(
	sge::parse::json::object const &_json_fog)
{
	sge::renderer::vector3 const fog_color(
		sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
			_json_fog,
			sge::parse::json::path(
				FCPPT_TEXT("fog-color"))));

	return
		sge::scenic::fog::properties(
			sge::scenic::fog::start(
				sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
					_json_fog,
					sge::parse::json::path(
						FCPPT_TEXT("fog-start")))),
			sge::scenic::fog::end(
				sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
					_json_fog,
					sge::parse::json::path(
						FCPPT_TEXT("fog-end")))),
			sge::scenic::fog::color(
				sge::image::color::any::object(
					sge::image::color::rgb32f(
						(sge::image::color::init::red() %= fog_color[0])
						(sge::image::color::init::green() %= fog_color[1])
						(sge::image::color::init::blue() %= fog_color[2])))));
}

sge::renderer::ambient_color const
parse_ambient_color(
	sge::parse::json::object const &_json_world)
{
	sge::renderer::vector3 const ambient_color(
		sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
			_json_world,
			sge::parse::json::path(
				FCPPT_TEXT("ambient-color"))));

	return
		sge::renderer::ambient_color(
			sge::image::color::any::object(
				sge::image::color::rgb32f(
					(sge::image::color::init::red() %= ambient_color[0])
					(sge::image::color::init::green() %= ambient_color[1])
					(sge::image::color::init::blue() %= ambient_color[2]))));
}

void
load_mesh(
	sge::scenic::scene::prototype &_scene,
	sge::parse::json::object const &_json_mesh)
{
	fcppt::container::ptr::push_back_unique_ptr(
		_scene.meshes(),
		fcppt::make_unique_ptr<sge::scenic::mesh>(
			sge::scenic::identifier(
				sge::parse::json::find_and_convert_member<fcppt::string>(
					_json_mesh,
					sge::parse::json::path(
						FCPPT_TEXT("name")))),
			sge::scenic::position(
				from_blender_vector(
					sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
						_json_mesh,
						sge::parse::json::path(
							FCPPT_TEXT("position"))))),
			sge::scenic::rotation(
				rotation_from_angles_mesh(
					from_blender_vector(
						sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
							_json_mesh,
							sge::parse::json::path(
								FCPPT_TEXT("rotation")))))),
			sge::scenic::scale(
				from_blender_vector(
					sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
						_json_mesh,
						sge::parse::json::path(
							FCPPT_TEXT("scale")))))));
}

void
load_meshes(
	sge::scenic::scene::prototype &_scene,
	sge::parse::json::array const &_json_meshes)
{
	for(
		sge::parse::json::element_vector::const_iterator current_mesh =
			_json_meshes.elements.begin();
		current_mesh != _json_meshes.elements.end();
		++current_mesh)
		load_mesh(
			_scene,
			sge::parse::json::get<sge::parse::json::object const>(
				*current_mesh));
}

void
load_light(
	sge::scenic::scene::prototype &_scene,
	sge::parse::json::object const &_json_light)
{
	fcppt::string const light_type(
		sge::parse::json::find_and_convert_member<fcppt::string>(
			_json_light,
			sge::parse::json::path(
				FCPPT_TEXT("light-type"))));

	sge::renderer::vector3 const color(
		sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
			_json_light,
			sge::parse::json::path(
				FCPPT_TEXT("color"))));

	sge::image::color::any::object const converted_color(
		sge::image::color::rgb32f(
			(sge::image::color::init::red() %= color[0])
			(sge::image::color::init::green() %= color[1])
			(sge::image::color::init::blue() %= color[2])));

	sge::renderer::diffuse_color const diffuse_color(
		converted_color);

	sge::renderer::specular_color const specular_color(
		converted_color);

	sge::renderer::ambient_color ambient_color(
		sge::image::colors::black());

	if(light_type == FCPPT_TEXT("directional"))
	{
		_scene.lights().push_back(
			sge::renderer::light::object(
				diffuse_color,
				specular_color,
				ambient_color,
				sge::renderer::light::directional(
					sge::renderer::light::direction(
					    multiply_matrix4_vector3(
							rotation_from_angles_mesh(
								from_blender_vector(
									sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
										_json_light,
										sge::parse::json::path(
											FCPPT_TEXT("rotation"))))),
							sge::renderer::vector3(
								0.0f,
								1.0f,
								0.0f))))));
	}
	else if(light_type == "point")
	{
		_scene.lights().push_back(
			sge::renderer::light::object(
				diffuse_color,
				specular_color,
				ambient_color,
				sge::renderer::light::point(
					sge::renderer::light::position(
						from_blender_vector(
							sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
								_json_light,
								sge::parse::json::path(
									FCPPT_TEXT("position"))))),
					sge::renderer::light::attenuation(
						sge::renderer::light::constant_attenuation(
							sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
								_json_light,
								sge::parse::json::path(
									FCPPT_TEXT("constant-falloff")))),
						sge::renderer::light::linear_attenuation(
							sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
								_json_light,
								sge::parse::json::path(
									FCPPT_TEXT("linear-falloff")))),
						sge::renderer::light::quadratic_attenuation(
							sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
								_json_light,
								sge::parse::json::path(
									FCPPT_TEXT("quadratic-falloff"))))))));
	}
	else
	{
		throw
			sge::scenic::exception(
				FCPPT_TEXT("Invalid light type \"")+
				light_type+
				FCPPT_TEXT("\""));
	}
}

void
load_lights(
	sge::scenic::scene::prototype &_scene,
	sge::parse::json::array const &_json_lights)
{
	for(
		sge::parse::json::element_vector::const_iterator current_light =
			_json_lights.elements.begin();
		current_light != _json_lights.elements.end();
		++current_light)
		load_light(
			_scene,
			sge::parse::json::get<sge::parse::json::object const>(
				*current_light));
}
}

sge::scenic::scene::prototype_unique_ptr
sge::scenic::scene::from_blender_file(
	boost::filesystem::path const &_path)
{
	sge::parse::json::object const json_file(
		sge::parse::json::parse_file_exn(
			_path));

	sge::scenic::scene::prototype_unique_ptr result(
		fcppt::make_unique_ptr<sge::scenic::scene::prototype>(
			fcppt::cref(
				parse_camera_properties(
					sge::parse::json::find_and_convert_member<sge::parse::json::object>(
						json_file,
						sge::parse::json::path(
							FCPPT_TEXT("camera"))))),
			fcppt::cref(
				parse_fog_properties(
					sge::parse::json::find_and_convert_member<sge::parse::json::object>(
						json_file,
						sge::parse::json::path(
							FCPPT_TEXT("world"))))),
			fcppt::cref(
				parse_ambient_color(
					sge::parse::json::find_and_convert_member<sge::parse::json::object>(
						json_file,
						sge::parse::json::path(
							FCPPT_TEXT("world")))))));

	load_meshes(
		*result,
		sge::parse::json::find_and_convert_member<sge::parse::json::array>(
			json_file,
			sge::parse::json::path(
				FCPPT_TEXT("meshes"))));

	load_lights(
		*result,
		sge::parse::json::find_and_convert_member<sge::parse::json::array>(
			json_file,
			sge::parse::json::path(
				FCPPT_TEXT("lights"))));

	return
		fcppt::move(
			result);
}
