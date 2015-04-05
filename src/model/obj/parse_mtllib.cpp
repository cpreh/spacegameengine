/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/image/color/rgb32f.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/model/obj/exception.hpp>
#include <sge/model/obj/identifier.hpp>
#include <sge/model/obj/parse_mtllib.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/src/model/obj/logger.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <sstream>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{
class parser
{
FCPPT_NONASSIGNABLE(
	parser);
public:
	explicit
	parser(
		boost::filesystem::path const &_filename
	)
	:
		parent_path_(
			_filename.parent_path()),
		result_(),
		current_line_(
			0u),
		current_material_(
			fcppt::string()),
		shininess_(),
		ambient_(),
		diffuse_(),
		specular_(),
		emissive_(),
		diffuse_texture_(),
		specular_texture_()
	{
		boost::filesystem::ifstream stream(
			_filename);

		if(!stream.is_open())
			throw
				sge::model::obj::exception(
					FCPPT_TEXT("Couldn't open file \"")+
					fcppt::filesystem::path_to_string(
						_filename)+
					FCPPT_TEXT("\""));

		std::string line;

		while(
			std::getline(
				stream,
				line))
		{
			++current_line_;

			if(line.empty() || line[0] == '#')
				continue;

			std::string::size_type const first_space_position =
				line.find(' ');

			this->throw_error_if(
				first_space_position == std::string::npos,
				FCPPT_TEXT("No prefix found"));

			std::string const prefix =
				line.substr(
					0,
					first_space_position);

			std::string const rest_of_line(
				line.substr(
					first_space_position+1u));

			this->parse_line(
				prefix,
				rest_of_line);
		}

		this->push_material();
	}

	sge::model::obj::material_map const &
	result() const
	{
		return
			result_;
	}

	void
	throw_error_if(
		bool const _condition,
		fcppt::string const &_error_message)
	{
		if(_condition)
			throw
				sge::model::obj::exception(
					FCPPT_TEXT("Error on line ")+
					fcppt::insert_to_fcppt_string(
						current_line_)+
					FCPPT_TEXT(": ")+
					_error_message);
	}

	void
	parse_line(
		std::string const &_prefix,
		std::string const &_rest_of_line)
	{
		if(_prefix == "Ns")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::scalar new_shininess;

			this->throw_error_if(
				!(ss >> new_shininess),
				FCPPT_TEXT("Invalid shininess."));

			shininess_ =
				new_shininess;
		}
		else if(_prefix == "Ka")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::vector3 new_ambient{
				fcppt::no_init()
			};

			this->throw_error_if(
				!(ss >> new_ambient[0] >> new_ambient[1] >> new_ambient[2]),
				FCPPT_TEXT("Invalid ambient"));

			ambient_ =
				new_ambient;
		}
		else if(_prefix == "Ke")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::scalar new_emissive;

			this->throw_error_if(
				!(ss >> new_emissive),
				FCPPT_TEXT("Invalid emissive"));

			emissive_ =
				sge::renderer::vector3(
					new_emissive,
					new_emissive,
					new_emissive);
		}
		else if(_prefix == "Kd")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::vector3 new_diffuse{
				fcppt::no_init()
			};

			this->throw_error_if(
				!(ss >> new_diffuse[0] >> new_diffuse[1] >> new_diffuse[2]),
				FCPPT_TEXT("Invalid diffuse"));

			diffuse_ =
				new_diffuse;
		}
		else if(_prefix == "Ks")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::vector3 new_specular{
				fcppt::no_init()
			};

			this->throw_error_if(
				!(ss >> new_specular[0] >> new_specular[1] >> new_specular[2]),
				FCPPT_TEXT("Invalid specular"));

			specular_ =
				new_specular;
		}
		else if(_prefix == "Ni")
		{
			// Not usable
		}
		else if(_prefix == "d")
		{
			std::istringstream ss(
				_rest_of_line);

			sge::renderer::scalar dissolve;

			this->throw_error_if(
				!(ss >> dissolve),
				FCPPT_TEXT("Invalid dissolve"));

			FCPPT_ASSERT_PRE(
				diffuse_);

			FCPPT_LOG_WARNING(
				sge::model::obj::logger(),
				fcppt::log::_ << FCPPT_TEXT("obj (mtl): dissolve currently not supported"));
			/*
			(*diffuse_)[3] =
				dissolve;
			if(std::abs(dissolve - 1.0f) > 0.0001f)
				throw
					sge::model::obj::exception(
						FCPPT_TEXT("Error on line ")+
						fcppt::insert_to_fcppt_string(
							current_line_)+
						FCPPT_TEXT(": Invalid dissolve value (!= 1, not supported)."));
			*/
		}
		else if(_prefix == "illum")
		{
			std::istringstream ss(
				_rest_of_line);

			unsigned light_model;
			this->throw_error_if(
				!(ss >> light_model),
				FCPPT_TEXT("Invalid light model"));

			switch(light_model)
			{
			case 0u:
				ambient_ =
					sge::renderer::vector3::null();
				break;
			case 1u:
				specular_ =
					sge::renderer::vector3::null();
				break;
			case 2u:
				break;
			default:
				FCPPT_LOG_WARNING(
					sge::model::obj::logger(),
					fcppt::log::_ << FCPPT_TEXT("obj (mtl): invalid light model: ") << light_model);
				break;
			}
		}
		else if(_prefix == "map_Kd")
		{
			diffuse_texture_ =
				parent_path_ /
				boost::filesystem::path(
					_rest_of_line);
		}
		else if(_prefix == "map_Ks")
		{
			specular_texture_ =
				parent_path_ /
				boost::filesystem::path(
					_rest_of_line);
		}
		else if (_prefix == "newmtl")
		{
			// First material we see? Do nothing.
			if(!current_material_.get().empty())
				this->push_material();

			current_material_ =
				sge::model::obj::identifier(
					sge::charconv::utf8_string_to_fcppt(
						sge::charconv::utf8_string(
							_rest_of_line.begin(),
							_rest_of_line.end())));
		}
		else
		{
			FCPPT_LOG_WARNING(
				sge::model::obj::logger(),
				fcppt::log::_ << FCPPT_TEXT("obj (mtl): invalid prefix"));
		}
	}

	void
	push_material()
	{
		auto const make_exception(
			[
				this
			]{
				return
					sge::model::obj::exception{
						FCPPT_TEXT("Error on line ")
						+
						fcppt::insert_to_fcppt_string(
							current_line_
						)
						+
						FCPPT_TEXT(": Material without ambient/specular/emissive/diffuse/shininess.")
					};
			}
		);

		auto const make_color(
			[](
				sge::renderer::vector3 const _vec
			)
			{
				return
					sge::image::color::any::object{
						sge::image::color::rgb32f{
							(sge::image::color::init::red() %= (_vec)[0])
							(sge::image::color::init::green() %= (_vec)[1])
							(sge::image::color::init::blue() %= (_vec)[2])
						}
					};
			}
		);

		result_.insert(
			std::make_pair(
				current_material_,
				sge::model::obj::material::object(
					current_material_,
					sge::model::obj::material::diffuse_color(
						make_color(
							fcppt::optional_to_exception(
								diffuse_,
								make_exception
							)
						)
					),
					sge::model::obj::material::ambient_color(
						make_color(
							fcppt::optional_to_exception(
								ambient_,
								make_exception
							)
						)
					),
					sge::model::obj::material::specular_color(
						make_color(
							fcppt::optional_to_exception(
								specular_,
								make_exception
							)
						)
					),
					sge::model::obj::material::emissive_color(
						make_color(
							fcppt::optional_to_exception(
								emissive_,
								make_exception
							)
						)
					),
					sge::model::obj::material::shininess(
						fcppt::optional_to_exception(
							shininess_,
							make_exception
						)
					),
					sge::model::obj::material::diffuse_texture_path(
						fcppt::from_optional(
							diffuse_texture_,
							[]{
								return
									boost::filesystem::path();
							}
						)
					),
					sge::model::obj::material::specular_texture_path(
						fcppt::from_optional(
							specular_texture_,
							[]{
								return
									boost::filesystem::path();
							}
						)
					)
				)
			)
		);
	}
private:
	boost::filesystem::path const parent_path_;
	sge::model::obj::material_map result_;
	unsigned current_line_;
	sge::model::obj::identifier current_material_;
	fcppt::optional<sge::renderer::scalar> shininess_;
	fcppt::optional<sge::renderer::vector3> ambient_, diffuse_, specular_, emissive_;
	fcppt::optional<boost::filesystem::path> diffuse_texture_;
	fcppt::optional<boost::filesystem::path> specular_texture_;
};
}

sge::model::obj::material_map const
sge::model::obj::parse_mtllib(
	boost::filesystem::path const &_filename
)
{
	parser p(
		_filename
	);

	return
		p.result();
}
