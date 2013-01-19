/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/charconv/utf8_file_to_fcppt_string.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgb32f.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_string_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vector4.hpp>
#include <sge/scenic/exception.hpp>
#include <sge/scenic/scene/entity.hpp>
#include <sge/scenic/scene/from_blender_file.hpp>
#include <sge/scenic/scene/prototype.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/matrix/rotation_x.hpp>
#include <fcppt/math/matrix/rotation_y.hpp>
#include <fcppt/math/matrix/rotation_z.hpp>
#include <fcppt/math/matrix/transform_direction.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/narrow_cast.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{
// We need this a lot
sge::image::color::rgb32f const
vector3_to_rgb32f(
	sge::renderer::vector3 const &v)
{
	return
		sge::image::color::rgb32f(
			(sge::image::color::init::red() %= v[0])
			(sge::image::color::init::green() %= v[1])
			(sge::image::color::init::blue() %= v[2]));
}

// This just switches y and z
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

// Converts a blender euler angle vector to a rotation matrix.
// This _seems_ to be different for the camera. For everything else,
// see "rotation_from_angles_entity" below
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

// Converts a blender euler angle vector to a rotation matrix. This
// was created using Trial & Error (tm)
sge::renderer::matrix4 const
rotation_from_angles_entity(
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

sge::scenic::scene::camera_properties const
parse_camera_properties(
	sge::parse::json::object const &_json_camera)
{
	// Here, we use rotation_from_angles_camera to determine the
	// rotation matrix. See above.
	sge::renderer::matrix4 const camera_rotation(
		rotation_from_angles_camera(
			from_blender_vector(
				sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
					_json_camera,
					sge::parse::json::path(
						FCPPT_TEXT("rotation"))))));

	// We start with blender's default camera coordinate system, which
	// has some funky values for the different axes.
	// We multiply each vector with the camera rotation matrix,
	// resulting in a new orthogonal coordinate system.
	sge::renderer::vector3 const
		right(
			fcppt::math::matrix::transform_direction(
				camera_rotation,
				sge::renderer::vector3(1.0f,0.0f,0.0f))),
		up(
			fcppt::math::matrix::transform_direction(
				camera_rotation,
				sge::renderer::vector3(0.0f,0.0f,1.0f))),
		forward(
			fcppt::math::matrix::transform_direction(
				camera_rotation,
				sge::renderer::vector3(0.0f,-1.0f,0.0f)));

	// The rest of the properties are simple to extract from the json,
	// so it's done inline here.
	return
		sge::scenic::scene::camera_properties(
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

sge::scenic::render_context::fog::optional_properties const
parse_fog_properties(
	sge::parse::json::object const &_json_fog)
{
	return
		sge::parse::json::find_and_convert_member<bool>(
			_json_fog,
			sge::parse::json::path(
				FCPPT_TEXT("enabled")))
		?
			sge::scenic::render_context::fog::optional_properties(
				sge::scenic::render_context::fog::properties(
					sge::scenic::render_context::fog::start(
						sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
							_json_fog,
							sge::parse::json::path(
								FCPPT_TEXT("start")))),
					sge::scenic::render_context::fog::end(
						sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
							_json_fog,
							sge::parse::json::path(
								FCPPT_TEXT("end")))),
					sge::scenic::render_context::fog::color(
						sge::image::color::any::object(
							vector3_to_rgb32f(
								sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
									_json_fog,
									sge::parse::json::path(
										FCPPT_TEXT("color"))))))))
		:
			sge::scenic::render_context::fog::optional_properties();
}

sge::scenic::render_context::ambient_color const
parse_ambient_color(
	sge::parse::json::object const &_json_world)
{
	return
		sge::scenic::render_context::ambient_color(
			sge::image::color::any::object(
				vector3_to_rgb32f(
					sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
						_json_world,
						sge::parse::json::path(
							FCPPT_TEXT("ambient-color"))))));
}

// Loads a single entity. Is called for every entity.
void
load_entity(
	boost::filesystem::path const &_base_path,
	sge::scenic::scene::prototype &_scene,
	sge::parse::json::object const &_json_entity)
{
	_scene.entities().push_back(
		sge::scenic::scene::entity(
			sge::scenic::scene::mesh_path(
				_base_path /
				(sge::parse::json::find_and_convert_member<fcppt::string>(
					_json_entity,
					sge::parse::json::path(
						FCPPT_TEXT("name")))+FCPPT_TEXT(".obj"))),
			sge::scenic::scene::position(
				from_blender_vector(
					sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
						_json_entity,
						sge::parse::json::path(
							FCPPT_TEXT("position"))))),
			sge::scenic::scene::rotation(
				rotation_from_angles_entity(
					from_blender_vector(
						sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
							_json_entity,
							sge::parse::json::path(
								FCPPT_TEXT("rotation")))))),
			sge::scenic::scene::scale(
				from_blender_vector(
					sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
						_json_entity,
						sge::parse::json::path(
							FCPPT_TEXT("scale")))))));
}

// This is just a wrapper calling load_entity on every entity.
void
load_entities(
	boost::filesystem::path const &_base_path,
	sge::scenic::scene::prototype &_scene,
	sge::parse::json::array const &_json_entities)
{
	for(
		sge::parse::json::element_vector::const_iterator current_entity =
			_json_entities.elements.begin();
		current_entity != _json_entities.elements.end();
		++current_entity)
		load_entity(
			_base_path,
			_scene,
			sge::parse::json::get<sge::parse::json::object const>(
				*current_entity));
}

sge::scenic::render_context::light::attenuation const
parse_light_attenuation(
	sge::parse::json::object const &_json_attenuation)
{
	return
		sge::scenic::render_context::light::attenuation(
			sge::scenic::render_context::light::constant_attenuation(
				sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
					_json_attenuation,
					sge::parse::json::path(
						FCPPT_TEXT("constant-falloff")))),
			sge::scenic::render_context::light::linear_attenuation(
				sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
					_json_attenuation,
					sge::parse::json::path(
						FCPPT_TEXT("linear-falloff")))),
			sge::scenic::render_context::light::quadratic_attenuation(
				sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
					_json_attenuation,
					sge::parse::json::path(
						FCPPT_TEXT("quadratic-falloff")))));
}

sge::scenic::render_context::light::direction const
parse_light_direction(
	sge::parse::json::object const &_json_parent)
{
	return
		sge::scenic::render_context::light::direction(
			fcppt::math::matrix::transform_direction(
				rotation_from_angles_entity(
					from_blender_vector(
						sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
							_json_parent,
							sge::parse::json::path(
								FCPPT_TEXT("rotation"))))),
				sge::renderer::vector3(
					0.0f,
					1.0f,
					0.0f)));
}

sge::scenic::render_context::light::position const
parse_light_position(
	sge::parse::json::object const &_json_parent)
{
	return
		sge::scenic::render_context::light::position(
			from_blender_vector(
				sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
					_json_parent,
					sge::parse::json::path(
						FCPPT_TEXT("position")))));
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

	sge::image::color::any::object const converted_color(
		vector3_to_rgb32f(
			sge::parse::json::find_and_convert_member<sge::renderer::vector3>(
				_json_light,
				sge::parse::json::path(
					FCPPT_TEXT("color")))));

	sge::scenic::render_context::diffuse_color const diffuse_color(
		converted_color);

	sge::scenic::render_context::specular_color const specular_color(
		converted_color);

	sge::scenic::render_context::ambient_color ambient_color(
		sge::image::color::predef::black());

	if(light_type == FCPPT_TEXT("directional"))
	{
		_scene.lights().push_back(
			sge::scenic::render_context::light::object(
				diffuse_color,
				specular_color,
				ambient_color,
				sge::scenic::render_context::light::directional(
					parse_light_direction(
						_json_light))));
	}
	else if(light_type == FCPPT_TEXT("point"))
	{
		_scene.lights().push_back(
			sge::scenic::render_context::light::object(
				diffuse_color,
				specular_color,
				ambient_color,
				sge::scenic::render_context::light::point(
					parse_light_position(
						_json_light),
					parse_light_attenuation(
						_json_light))));
	}
	else if(light_type == FCPPT_TEXT("spot"))
	{
		/*
		_scene.lights().push_back(
			sge::scenic::render_context::light::object(
				diffuse_color,
				specular_color,
				ambient_color,
				sge::scenic::render_context::light::spot(
					parse_light_position(
						_json_light),
					parse_light_direction(
						_json_light),
					sge::scenic::render_context::light::cutoff_angle(
						sge::parse::json::find_and_convert_member<sge::renderer::scalar>(
							_json_light,
							sge::parse::json::path(
								FCPPT_TEXT("spot_cutoff")))),
					parse_light_attenuation(
						_json_light))));
		*/
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
	boost::filesystem::path const &_path,
	sge::charconv::system &_charconv_system)
{
	sge::parse::json::object const json_file(
		sge::parse::json::parse_string_exn(
			sge::charconv::utf8_file_to_fcppt_string(
				_charconv_system,
				_path)).object());

	// The prototype is created with the world properties in the
	// ctor. Entities and lights are added below.
	sge::scenic::scene::prototype_unique_ptr result(
		fcppt::make_unique_ptr<sge::scenic::scene::prototype>(
			parse_camera_properties(
				sge::parse::json::find_and_convert_member<sge::parse::json::object>(
					json_file,
					sge::parse::json::path(
						FCPPT_TEXT("camera")))),
			parse_fog_properties(
				sge::parse::json::find_and_convert_member<sge::parse::json::object>(
					json_file,
					sge::parse::json::path(
						FCPPT_TEXT("world")) / FCPPT_TEXT("fog"))),
			parse_ambient_color(
				sge::parse::json::find_and_convert_member<sge::parse::json::object>(
					json_file,
					sge::parse::json::path(
						FCPPT_TEXT("world"))))));

	load_entities(
		_path.parent_path(),
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
		std::move(
			result);
}
