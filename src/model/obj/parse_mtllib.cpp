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


#include <sge/image/color/init.hpp>
#include <sge/image/color/rgb32f.hpp>
#include <sge/log/global.hpp>
#include <sge/model/obj/exception.hpp>
#include <sge/model/obj/identifier.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <sstream>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::model::obj::material_map const
sge::model::obj::parse_mtllib(
	boost::filesystem::path const &_filename,
	sge::charconv::system &_charconv_system)
{
	boost::filesystem::ifstream stream(
		_filename);

	sge::model::obj::material_map result;

	if(!stream.is_open())
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Couldn't open file \"")+
				fcppt::filesystem::path_to_string(
					_filename)+
				FCPPT_TEXT("\""));

	typedef
	unsigned long
	line_count;

	line_count line_counter = 0u;
	sge::model::obj::identifier current_material((
		fcppt::string()));
	std::string line;

	fcppt::optional<sge::renderer::scalar> shininess;
	fcppt::optional<sge::renderer::vector3> ambient, diffuse, specular, emissive;
	fcppt::optional<boost::filesystem::path> texture;

	while(
		std::getline(
			stream,
			line))
	{
		++line_counter;

		if(line.empty() || line[0] == '#')
			continue;

		std::string::size_type const first_space_position =
			line.find(' ');

		if(first_space_position == std::string::npos)
			throw
				sge::model::obj::exception(
					FCPPT_TEXT("Error on line ")+
					fcppt::insert_to_fcppt_string(
						line_counter)+
					FCPPT_TEXT(": No prefix found."));

		std::string const prefix =
			line.substr(
				0,
				first_space_position);

		std::string const rest_of_line(
			line.substr(
				first_space_position+1u));

		if(prefix == "Ns")
		{
			std::istringstream ss(
				rest_of_line);

			sge::renderer::scalar new_shininess;

			if(!(ss >> new_shininess))
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid shininess."));

			shininess =
				new_shininess;
		}
		else if(prefix == "Ka")
		{
			std::istringstream ss(
				rest_of_line);

			sge::renderer::vector3 new_ambient;

			if(!(ss >> new_ambient[0] >> new_ambient[1] >> new_ambient[2]))
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid ambient."));

			ambient =
				new_ambient;
		}
		else if(prefix == "Ke")
		{
			std::istringstream ss(
				rest_of_line);

			sge::renderer::scalar new_emissive;

			if(!(ss >> new_emissive))
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid emissive."));

			emissive =
				sge::renderer::vector3(
					new_emissive,
					new_emissive,
					new_emissive);
		}
		else if(prefix == "Kd")
		{
			std::istringstream ss(
				rest_of_line);

			sge::renderer::vector3 new_diffuse;

			if(!(ss >> new_diffuse[0] >> new_diffuse[1] >> new_diffuse[2]))
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid diffuse."));

			diffuse =
				new_diffuse;
		}
		else if(prefix == "Ks")
		{
			std::istringstream ss(
				rest_of_line);

			sge::renderer::vector3 new_specular;

			if(!(ss >> new_specular[0] >> new_specular[1] >> new_specular[2]))
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid specular."));

			specular =
				new_specular;
		}
		else if(prefix == "Ni")
		{
			// Not usable
		}
		else if(prefix == "d")
		{
			std::istringstream ss(
				rest_of_line);

			sge::renderer::scalar dissolve;
			if(!(ss >> dissolve))
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid dissolve."));

			FCPPT_ASSERT_PRE(
				diffuse);

			(*diffuse)[3] =
				dissolve;
			/*
			if(std::abs(dissolve - 1.0f) > 0.0001f)
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid dissolve value (!= 1, not supported)."));
			*/
		}
		else if(prefix == "illum")
		{
			std::istringstream ss(
				rest_of_line);

			unsigned light_model;
			if(!(ss >> light_model))
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							line_counter)+
						FCPPT_TEXT(": Invalid light model."));

			switch(light_model)
			{
			case 0u:
				ambient =
					sge::renderer::vector3::null();
				break;
			case 1u:
				specular =
					sge::renderer::vector3::null();
				break;
			case 2u:
				break;
			default:
				FCPPT_LOG_WARNING(
					sge::log::global(),
					fcppt::log::_ << FCPPT_TEXT("obj (mtl): invalid light model: ") << light_model);
				break;
			}
		}
		else if(prefix == "map_Kd")
		{
			texture =
				boost::filesystem::path(
					rest_of_line);
		}
		else if (prefix == "newmtl")
		{
			// First material we see? Do nothing.
			if(!current_material.get().empty())
			{
				if(!ambient || !specular || !emissive || !diffuse || !shininess)
					throw
						sge::model::obj::exception(
							FCPPT_TEXT("Error on line ")+
							fcppt::insert_to_fcppt_string(
								line_counter)+
							FCPPT_TEXT(": Material without ambient/specular/emissive/diffuse/shininess."));

				result.insert(
					std::make_pair(
						current_material,
						sge::model::obj::material(
							current_material,
							sge::renderer::material(
								sge::renderer::diffuse_color(
									sge::image::color::any::object(
										sge::image::color::rgb32f(
											(sge::image::color::init::red() %= (*diffuse)[0])
											(sge::image::color::init::green() %= (*diffuse)[1])
											(sge::image::color::init::blue() %= (*diffuse)[2])))),
								sge::renderer::ambient_color(
									sge::image::color::any::object(
										sge::image::color::rgb32f(
											(sge::image::color::init::red() %= (*ambient)[0])
											(sge::image::color::init::green() %= (*ambient)[1])
											(sge::image::color::init::blue() %= (*ambient)[2])))),
								sge::renderer::specular_color(
									sge::image::color::any::object(
										sge::image::color::rgb32f(
											(sge::image::color::init::red() %= (*specular)[0])
											(sge::image::color::init::green() %= (*specular)[1])
											(sge::image::color::init::blue() %= (*specular)[2])))),
								sge::renderer::emissive_color(
									sge::image::color::any::object(
										sge::image::color::rgb32f(
											(sge::image::color::init::red() %= (*emissive)[0])
											(sge::image::color::init::green() %= (*emissive)[1])
											(sge::image::color::init::blue() %= (*emissive)[2])))),
								sge::renderer::shininess(
									*shininess)),
							sge::model::obj::texture_path(
								texture
								?
									*texture
								:
									boost::filesystem::path()))));
			}

			current_material =
				sge::model::obj::identifier(
					sge::charconv::utf8_string_to_fcppt(
						_charconv_system,
						sge::charconv::utf8_string(
							rest_of_line.begin(),
							rest_of_line.end())));
		}
		else
		{
			FCPPT_LOG_WARNING(
				sge::log::global(),
				fcppt::log::_ << FCPPT_TEXT("obj (mtl): invalid prefix"));
		}
	}

	if(!ambient || !specular || !emissive || !diffuse || !shininess)
		throw
			sge::model::obj::exception(
				FCPPT_TEXT("Error on line ")+
				fcppt::insert_to_fcppt_string(
					line_counter)+
				FCPPT_TEXT(": Material without ambient/specular/emissive/diffuse/shininess."));

	result.insert(
		std::make_pair(
			current_material,
			sge::model::obj::material(
				current_material,
				sge::renderer::material(
					sge::renderer::diffuse_color(
						sge::image::color::any::object(
							sge::image::color::rgb32f(
								(sge::image::color::init::red() %= (*diffuse)[0])
								(sge::image::color::init::green() %= (*diffuse)[1])
								(sge::image::color::init::blue() %= (*diffuse)[2])))),
					sge::renderer::ambient_color(
						sge::image::color::any::object(
							sge::image::color::rgb32f(
								(sge::image::color::init::red() %= (*ambient)[0])
								(sge::image::color::init::green() %= (*ambient)[1])
								(sge::image::color::init::blue() %= (*ambient)[2])))),
					sge::renderer::specular_color(
						sge::image::color::any::object(
							sge::image::color::rgb32f(
								(sge::image::color::init::red() %= (*specular)[0])
								(sge::image::color::init::green() %= (*specular)[1])
								(sge::image::color::init::blue() %= (*specular)[2])))),
					sge::renderer::emissive_color(
						sge::image::color::any::object(
							sge::image::color::rgb32f(
								(sge::image::color::init::red() %= (*emissive)[0])
								(sge::image::color::init::green() %= (*emissive)[1])
								(sge::image::color::init::blue() %= (*emissive)[2])))),
					sge::renderer::shininess(
						*shininess)),
				sge::model::obj::texture_path(
					texture
					?
						*texture
					:
						boost::filesystem::path()))));

	return
		result;
}
